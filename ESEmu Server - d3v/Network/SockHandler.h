#pragma once
#ifndef _SOCKHANDLER_H_
#define _SOCKHANDLER_H_

#include "..\Common\Credits.h"

#ifndef BOOST_NETWORK

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <winsock.h>
#include <string>
#include <vector>
#include "..\ConfManager\ConfigReader.h"
#include "..\Crypto\Crypto.h"
#include "Packet Handler\Packet Handler.h"

class Server;
extern Server LoginServer;

class SockHandler
{
public:
	SockHandler();
	~SockHandler();

	int packetlength;
	SOCKET socket;
	SOCKADDR_IN clientaddr;
	Crypto *Crypt;
	Packet *P;
	bool ExchangedKeys;
	unsigned long Sequence;


	void Init();
	void StartLoginRecv();
	bool Send(PacketBuilder& packet, bool DHPacket);
	void Disconnect();
	bool Send(char* packet, int Size, bool DHPacket);
	bool Send(PacketBuilder& packet, bool DHPacket, SockHandler* dis);
};

class Server
{
public:
	ConfigManager* CM;
	FD_SET fd;
	SOCKET acceptsocket;
	SOCKADDR_IN sockaddr;
	SockHandler *Client;

	bool Initialize(char* IP, u_short Port, ConfigManager* CMInstance);
	void End();
	void AcceptConnections();
};

#else

#include <boost\asio.hpp>
#include <boost\shared_ptr.hpp>
#include <boost\enable_shared_from_this.hpp>
#include <boost\shared_array.hpp>
#include <boost\bind.hpp>

#include <string>
#include <vector>
#include "..\ConfManager\ConfigReader.h"
#include "..\Crypto\Crypto.h"
#include "Packet Handler\Packet Handler.h"
#include "..\AntiDDoS\AntiDDoS.h"

#include "..\Game\Player\Player.h"

//class Server;
//extern Server LoginServer;

class SockHandler: public boost::enable_shared_from_this<SockHandler>
{

private:
	unsigned int		m_sequence;
	std::string			m_accName;
	unsigned long long	m_accID;
	Crypto*				m_crypto;
	DATABASE*			m_dbHandler;
	ConfigManager*		m_cfgHandler;
	AntiDDOS*			m_ADDoS;
	Packet*				Ph;

	boost::shared_array<unsigned char> m_recvBuffer;
	boost::asio::ip::tcp::socket tcpSocket;
	short				SType;
public:

	void Init(short Type);
	SockHandler(boost::asio::io_service& IOService): tcpSocket(IOService) { m_sequence = 1; }
	boost::asio::ip::tcp::socket& getSocket();
	void Start();
	void StartHeaderReading();
	void StartBodyReading(const boost::system::error_code& error);
	void ReadHandler(int Size, const boost::system::error_code& error);
	void Send(unsigned char* Packet, unsigned int Size);
	void Send(std::vector<unsigned char> Packet);
	void WriteHandler(const boost::system::error_code& error, size_t bytes_transferred);
	std::string getAccName();
	int getAccID();
	void setAccName(std::string name);
	void setAccID(unsigned long long ID);
	ConfigManager* GetCFG();
	std::string GetIP();
};

class Server: boost::noncopyable
{
private:

	ConfigManager* CManager;
	short		   Port;
	short		   SType;

public:

	typedef boost::shared_ptr<SockHandler> Session;

	boost::asio::io_service IOService;
	boost::asio::ip::tcp::acceptor Acceptor;
	Server() : Acceptor(IOService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 9400)) {}
	Server(short Port) : Acceptor(IOService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), Port)) {}
	~Server();
	void Start();
	void AcceptanceHandler(Session pSession, const boost::system::error_code& error);
	bool Initialize(const char* IP, short Port, ConfigManager* CMHandler, short Type);

};

#endif


#endif _SOCKHANDLER_H_