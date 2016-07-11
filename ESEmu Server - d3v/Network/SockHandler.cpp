#include "SockHandler.h"
#include "OPCodes.h"
#include "..\DBHandler\DBHandler.h"

#ifndef BOOST_NETWORK

Server LoginServer;

#define c  this->Crypt
#define pr this->P->GetPR()
#define pb this->P->GetPB()
#define GO(p, s) {DeterminatePacket(p, s);}

bool Server::Initialize(char* IP, u_short Port, ConfigManager* CMInstance)
{
	WSADATA wsa;
	int result;
	const char *option;
	u_long argp = 1;
	CM = CMInstance;

	if (CM->getNumber(CM->MAX_CLIENTS) > 150)
		return false;

	this->Client = (SockHandler*)malloc(CM->getNumber(CM->MAX_CLIENTS) * sizeof(SockHandler));

	result = WSAStartup(MAKEWORD(2, 0), &wsa);

	if (result == SOCKET_ERROR)
	{
		printf("[!] WSAStartup failed (%ld).\n", WSAGetLastError());
		return false;
	}

	this->acceptsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (this->acceptsocket == SOCKET_ERROR)
	{
		printf("[!] Socket failed (%ld).\n", WSAGetLastError());
		return false;
	}

	setsockopt(this->acceptsocket, SOL_SOCKET, SO_REUSEADDR, (char*)&option, sizeof(option));

	this->sockaddr.sin_addr.s_addr = inet_addr(IP);
	this->sockaddr.sin_family = AF_INET;
	this->sockaddr.sin_port = htons(Port);

	result = ::bind(this->acceptsocket, (SOCKADDR*)&sockaddr, sizeof(sockaddr));

	if (result == SOCKET_ERROR)
	{
		printf("[!] Binding failed (%ld).\n", WSAGetLastError());
		return false;
	}

	result = listen(acceptsocket, CM->getNumber(CM->MAX_CLIENTS));

	if (result == SOCKET_ERROR)
	{
		printf("[!] Listening failed (%ld).\n", WSAGetLastError());
		return false;
	}

	int Err = ioctlsocket(this->acceptsocket, FIONBIO, &argp);
	if (Err != NO_ERROR)
	{
		printf("[!] IOCTLSocket failed (%ld)", Err);
	}

	for (auto i = 0; i < CM->getNumber(CM->MAX_CLIENTS); i++)
	{
		this->Client[i].Init();
		this->Client[i].socket = INVALID_SOCKET;
		this->Client[i].ExchangedKeys = false;
	}

	return true;
}

//------------------------------------------------------------

void Server::End()
{
	closesocket(this->acceptsocket);
	WSACleanup();
}

//------------------------------------------------------------

void Server::AcceptConnections()
{
	FD_ZERO(&this->fd);

	FD_SET(this->acceptsocket, &this->fd);

	for (auto i = 0; i < CM->getNumber(CM->MAX_CLIENTS); i++)
	{
		if (this->Client[i].socket != INVALID_SOCKET)
		{
			FD_SET(this->Client[i].socket, &this->fd);
		}
	}

	select(NULL, &this->fd, NULL, NULL, NULL);

	if (FD_ISSET(this->acceptsocket, &this->fd))
	{
		for (auto i = 0; i < CM->getNumber(CM->MAX_CLIENTS); i++)
		{
			if (this->Client[i].socket == INVALID_SOCKET)
			{
				this->Client[i].packetlength = sizeof(SOCKADDR);
				this->Client[i].socket = accept(this->acceptsocket, (SOCKADDR*)&this->Client[i].clientaddr, &this->Client[i].packetlength);
				printf("-> Client (%s) connected.\n", inet_ntoa(this->Client[i].clientaddr.sin_addr));
				
				if (!this->Client[i].ExchangedKeys)
				{
					char* Buffer = (char*)malloc(72);
					memset(Buffer, 0x00, 72);
					DHPacket(Buffer);
					this->Client[i].Send(Buffer, 72, true);
					this->Client[i].ExchangedKeys = true;
				}
				break;
			}
		}
	}

	for (auto i = 0; i < CM->getNumber(CM->MAX_CLIENTS); i++)
	{
		if (this->Client[i].socket == INVALID_SOCKET)
		{
			continue;
		} else {
			if (FD_ISSET(this->Client[i].socket, &this->fd))
			{
				this->Client[i].StartLoginRecv();
			}
		}
	}
	
}

SockHandler::SockHandler()
{
	
}

SockHandler::~SockHandler()
{

}


//------------------------------------------------------------

void SockHandler::Init()
{
	this->P = new(Packet);
	this->P->Init();
	c = new(Crypto);
	c->Init();
	this->Sequence = 1;
}

template <typename T>
void SwapEnd(T& var)
{
	T varSwapped;
	for (long i = 0; i < static_cast<long>(sizeof(var)); i++)
		((char*)(&varSwapped))[sizeof(var) - 1 - i] = ((char*)(&var))[i];
	for (long i = 0; i < static_cast<long>(sizeof(var)); i++)
		((char*)(&var))[i] = ((char*)(&varSwapped))[i];
}



void SockHandler::StartLoginRecv()
{
	char packetbuffer[1024 * 64] = { 0 };
	memset(packetbuffer, 0x00, sizeof(packetbuffer));
	char* FinalPacket = nullptr;

	this->packetlength = recv(this->socket, packetbuffer, 1024 * 64, 0);

	short PacketSize = ((packetbuffer[1] << 8) | packetbuffer[0]) - 2;
	//printf("Packet size: %d.\n", PacketSize);

	for (auto i = 0; i < this->packetlength; i++)
		printf("0x%02X ", packetbuffer[i]);

	if (this->packetlength == NULL || this->packetlength >= (1024 * 64))
	{
		printf("[>] Invalid packet.\n");
		printf("%ld", WSAGetLastError());
		this->Disconnect();
		return;
	}

	if (this->packetlength > 0)
	{
		printf("Got a packet!\n");
		FinalPacket = (char*)malloc(this->packetlength);
		memset(FinalPacket, 0x00, this->packetlength);

		char IV[8] = { 0 };
		memset(IV, packetbuffer[6], sizeof(IV));

		c->Decrypt((unsigned char*)FinalPacket + 14, (unsigned char*)IV, (unsigned char*)packetbuffer, (unsigned char*)"AAAAAAAA", (this->packetlength - 24));

		pr->Init(FinalPacket, (this->packetlength - 24));
		GO(this->P, this);
	}
}

//------------------------------------------------------------

bool SockHandler::Send(PacketBuilder& packet, bool DHPacket, SockHandler* dis)
{
	unsigned char* sendingpck = (unsigned char*)malloc(packet.GetSize() + 26);
	memset(sendingpck, 0x00, (packet.GetSize() + 26));

	packet.CopyBuffer((char*)sendingpck);

	printf("Sending a packet (PBSend).\n");

	if (DHPacket)
		c->Encrypt(sendingpck, sendingpck, packet.GetSize() + 26, (unsigned char*)"\xC7\xD8\xC4\xBF\xB5\xE9\xC0", this->Sequence);
	else
		c->Encrypt(sendingpck, sendingpck, packet.GetSize() + 26, (unsigned char*)"AAAAAAAA", this->Sequence);

	this->packetlength = send(this->socket, (const char*)sendingpck, packet.GetSize(), 0);
	this->Sequence++;

	if (this->packetlength == SOCKET_ERROR)
	{
		this->Disconnect();
		return 1;
	}

	return 0;
}

bool SockHandler::Send(PacketBuilder& packet, bool DHPacket)
{
	unsigned char* sendingpck = (unsigned char*)malloc(packet.GetSize() + 26);
	memset(sendingpck, 0x00, (packet.GetSize() + 26));

	packet.CopyBuffer((char*)sendingpck);

	printf("Sending a packet (PBSend).\n");

	if (DHPacket)
		c->Encrypt(sendingpck, sendingpck, packet.GetSize() + 26, (unsigned char*)"\xC7\xD8\xC4\xBF\xB5\xE9\xC0", this->Sequence);
	else
		c->Encrypt(sendingpck, sendingpck, packet.GetSize() + 26, (unsigned char*)"AAAAAAAA", this->Sequence);

	this->packetlength = send(this->socket, (const char*)sendingpck, packet.GetSize(), 0);
	this->Sequence++;

	if (this->packetlength == SOCKET_ERROR)
	{
		this->Disconnect();
		return 1;
	}

	return 0;
}

bool SockHandler::Send(char* packet, int Size, bool DHPacket)
{
	byte key[CryptoPP::AES::DEFAULT_KEYLENGTH] = { 0xC7, 0xD8, 0xC4, 0xBF, 0xB5, 0xE9, 0xC0 };
	unsigned char* sendingpck = (unsigned char*)malloc(Size + 26);
	memset(sendingpck, 0x00, Size + 26);
	printf("Sending a packet (RawSend).\n");
	if (DHPacket)
	{
		c->Encrypt(sendingpck, (unsigned char*)packet, Size, (unsigned char*)key, this->Sequence);
	}
	else
		c->Encrypt(sendingpck, (unsigned char*)packet, Size, (unsigned char*)"AAAAAAAA", this->Sequence);

	this->packetlength = send(this->socket, (const char*)sendingpck, Size, 0);
	this->Sequence++;

	if (this->packetlength == SOCKET_ERROR)
	{
		printf("[!] Error sending a packet (%ld).\n", WSAGetLastError());
		this->Disconnect();
		return 1;
	}

	return 0;
}

//------------------------------------------------------------

void SockHandler::Disconnect()
{
	printf("-> Client (%s) disconnected.\n", inet_ntoa(this->clientaddr.sin_addr));

	closesocket(this->socket);
	this->packetlength = 0;
	this->socket = INVALID_SOCKET;
}

//------------------------------------------------------------

#else

#include "OPCodes.h"

#define REMOTE_IP							this->tcpSocket.remote_endpoint().address().to_string().c_str()
#define HUNT_OPCODE(PacketH, SockHandlerH)	{ if (this->SType == 1) \
													DeterminatePacket(PacketH, SockHandlerH); \
											  else if (this->SType == 2) \
                                                    DeterminateGPacket(PacketH, SockHandlerH); \
											}

#define HUNT_TEST_OPCODE(PacketH, SockHandlerH) TESTDeterminatePacket(PacketH, SockHandlerH)

boost::asio::ip::tcp::socket& SockHandler::getSocket() 
{
	return this->tcpSocket;
}

std::string SockHandler::GetIP()
{
	return this->tcpSocket.remote_endpoint().address().to_string();
}

void SockHandler::Start() 
{	
	//if (this->m_ADDoS->CheckBan(REMOTE_IP))
	//	this->getSocket().close();
	//else 
	//{
		//this->m_ADDoS->SetActive(REMOTE_IP);
		unsigned char* Buffer = (unsigned char*)malloc(72);
		memset(Buffer, 0x00, 72);
		DHPacket(Buffer);
		this->Send((unsigned char*)Buffer, 72);
		this->m_sequence++;

		if (this->SType == 1)
			printf("[+] Client (%s) successfully connected.\n", REMOTE_IP);
		else
			printf("[+] Game Session (%s) successfully connected.\n", REMOTE_IP);

		this->StartHeaderReading();
	//}
		if (this->SType == 2)
		{
			// New Player instance.
		}
}

void SockHandler::StartHeaderReading()
{
	this->m_recvBuffer.reset(new unsigned char[2]);
	boost::asio::async_read(this->tcpSocket, boost::asio::buffer(this->m_recvBuffer.get(), 2), boost::asio::transfer_at_least(2), boost::bind(&SockHandler::StartBodyReading, shared_from_this(), boost::asio::placeholders::error));
}

void SockHandler::StartBodyReading(const boost::system::error_code& error) 
{
	if (!error) 
	{
		unsigned short packetLen = ((m_recvBuffer[1] << 8) | m_recvBuffer[0]) - 2;
		this->m_recvBuffer.reset(new unsigned char[packetLen]);
		boost::asio::async_read(this->tcpSocket, boost::asio::buffer(this->m_recvBuffer.get(), packetLen), boost::bind(&SockHandler::ReadHandler, shared_from_this(), packetLen, boost::asio::placeholders::error));
	} else {
		printf("[+] Client disconnected (%s).\n", REMOTE_IP);
		//this->m_ADDoS->SetInactive(REMOTE_IP);
	}
}

void SockHandler::Send(std::vector<unsigned char> Packet) 
{
	unsigned char* encrypted = (unsigned char*)malloc((int)Packet.size() + 26);
	memset(encrypted, 0x00, Packet.size() + 26);
	this->m_crypto->Encrypt(encrypted, &Packet[0], Packet.size(), (unsigned char*)"\xC7\xD8\xC4\xBF\xB5\xE9\xC0\xFD", this->m_sequence);
	this->m_sequence++;
	boost::asio::async_write(this->tcpSocket, boost::asio::buffer(encrypted, Packet.size() + 26), boost::bind(&SockHandler::WriteHandler, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void SockHandler::Send(unsigned char* Packet, unsigned int Size) 
{
	printf("Sending packet (%d)\n", Size);
	
	unsigned char* encrypted = nullptr;
	encrypted = (unsigned char*)malloc(Size + 26);
	memset(encrypted, 0x00, Size + 26);

	this->m_crypto->Encrypt(encrypted, Packet, Size, (unsigned char*)"\xC7\xD8\xC4\xBF\xB5\xE9\xC0\xFD", this->m_sequence);
	this->m_sequence++;

	boost::asio::async_write(this->tcpSocket, boost::asio::buffer(encrypted, Size + 26), boost::bind(&SockHandler::WriteHandler, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void SockHandler::WriteHandler(const boost::system::error_code&, size_t)
{
	//free(this->Ph);
}

void SockHandler::ReadHandler(int Size, const boost::system::error_code& error) 
{
	if (error) 
	{
		printf("[!] ReadHandler Error: %s.\n", error.message().c_str());
		//this->m_ADDoS->SetInactive(REMOTE_IP);
		return;
	}
	unsigned char iv[8];
	memset(iv, this->m_recvBuffer[7], sizeof(iv));
	unsigned char* decrypted = (unsigned char*)malloc(Size - 24);
	memset(decrypted, 0x00, Size - 24);

	this->m_crypto->Decrypt(decrypted, iv, this->m_recvBuffer.get() + 14, (unsigned char*)"\xC7\xD8\xC4\xBF\xB5\xE9\xC0\xFD", Size - 24);
	//printf("Dumping decrypted packet:\n");
	//PDUMP(decrypted, Size - 24);

	this->Ph = new Packet();
	this->Ph->Init(this->m_dbHandler);
	this->Ph->GetPR()->Init((unsigned char*)decrypted, Size - 24);
#ifndef IS_DEVELOPMENT
	HUNT_OPCODE(Ph, this);
#else
	HUNT_TEST_OPCODE(Ph, this);
#endif

	if (!error) 
	{
		this->StartHeaderReading();
	}
}

std::string SockHandler::getAccName() 
{
	return this->m_accName;
}

int SockHandler::getAccID() 
{
	return this->m_accID;
}

void SockHandler::setAccName(std::string name) 
{
	this->m_accName = name;
}

void SockHandler::setAccID(unsigned long long ID) 
{
	this->m_accID = ID;
}

void SockHandler::Init(short Type)
{
	//this->m_ADDoS = new AntiDDOS();
	//this->m_ADDoS->Init();
	//printf("[+] ADDoS: System Initialized.\n");
	this->SType = Type;
	this->m_cfgHandler	= new ConfigManager();
	this->m_cfgHandler->load(Type);
	this->m_dbHandler	= new DATABASE(this->m_cfgHandler);
	if (this->m_dbHandler->IsError())
	{
		printf("[!] Can't connect to the database.\n");
		ExitThread(0);
	}
	this->m_crypto		= new (Crypto);
	this->m_crypto->Init();
	this->m_accID		= NULL;
	this->m_sequence	= 1;
}

ConfigManager* SockHandler::GetCFG()
{
	return this->m_cfgHandler;
}

// ----------------------------------------------------------------------------------------
Server::~Server()
{
	printf("[!] --- Called Server Destructor, WHAT THE FUCK.\n");
}

void Server::Start()
{
	Session tSession(new SockHandler(this->IOService));
	if (!tSession)
		printf("[!] Invalid session class (not initialized).\n");
	this->Acceptor.async_accept(tSession->getSocket(), boost::bind(&Server::AcceptanceHandler, this, tSession, boost::asio::placeholders::error));
}

void Server::AcceptanceHandler(Session pSession, const boost::system::error_code& error) 
{
	if (!error) 
	{
		pSession->Init(this->SType);
		pSession->Start();
		this->Start();
	} else {
		printf("[!] AcceptanceHandler Error: %s.\n", error.message().c_str());
	}
}

bool Server::Initialize(const char* IP, short Port, ConfigManager* CMHandler, short Type) 
{
	boost::system::error_code EC;
	this->CManager = CMHandler;
	this->SType = Type;
	this->Start();
	this->IOService.run(EC);
	if (EC)
		printf("IOService error: %s.\n", EC.message().c_str());
	return true;
}

#endif