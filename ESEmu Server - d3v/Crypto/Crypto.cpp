#include "Crypto.h"
using namespace CryptoPP;
#pragma warning (disable: 4996)
#include <climits>

template <typename T>
T EndianSwapper(T u)
{
	static_assert (CHAR_BIT == 8, "CHAR_BIT != 8");

	union
	{
		T u;
		unsigned char u8[sizeof(T)];
	} source, dest;

	source.u = u;

	for (size_t k = 0; k < sizeof(T); k++)
		dest.u8[k] = source.u8[sizeof(T) - k - 1];

	return dest.u;
}

void Crypto::Init()
{
	this->Def_DESKey[0] = 0xC7;
	this->Def_DESKey[1] = 0xD8;
	this->Def_DESKey[2] = 0xC4;
	this->Def_DESKey[3] = 0xBF;
	this->Def_DESKey[4] = 0xB5;
	this->Def_DESKey[5] = 0xE9;
	this->Def_DESKey[6] = 0xC0;
	this->Def_DESKey[7] = 0xFD;

	this->Def_HMACKey[0] = 0xC0;
	this->Def_HMACKey[1] = 0xD3;
	this->Def_HMACKey[2] = 0xBD;
	this->Def_HMACKey[3] = 0xC3;
	this->Def_HMACKey[4] = 0xB7;
	this->Def_HMACKey[5] = 0xCE;
	this->Def_HMACKey[6] = 0xB8;
	this->Def_HMACKey[7] = 0xB8;

	memcpy(this->DESKey, this->Def_DESKey, 8);
	memcpy(this->HMACKey, this->Def_HMACKey, 8);
}

void Crypto::SetKey(char Type, char Key[8])
{
	switch (Type)
	{
	case TYPE_HMAC:

		for (auto i = 0; i < sizeof(Key); i++)
			this->HMACKey[i] = Key[i];

		break;
	case TYPE_DES:

		for (auto i = 0; i < sizeof(Key); i++)
			this->DESKey[i] = Key[i];

		break;
	}
}

void Raw_Encrypt(unsigned char* EncryptedBlock, unsigned char* Input, unsigned int Size, unsigned char* Key, unsigned char* IV)
{
	CryptoPP::CBC_Mode<CryptoPP::DES>::Encryption Encryptor(Key, CryptoPP::DES::DEFAULT_KEYLENGTH, IV);
	Encryptor.ProcessData(EncryptedBlock, Input, Size);
}

void Raw_Decrypt(unsigned char* DecryptedBlock, unsigned char* Input, unsigned int Size, unsigned char* Key, unsigned char* IV)
{
	CryptoPP::CBC_Mode<CryptoPP::DES>::Decryption Decryptor(Key, CryptoPP::DES::DEFAULT_KEYLENGTH, IV);
	Decryptor.ProcessData(DecryptedBlock, Input, Size);
}

void Crypto::Encrypt(unsigned char* EncryptedBlock, unsigned char* Input, unsigned int Size, unsigned char *Key, unsigned int Seq)
{
	std::uniform_int_distribution<unsigned int> IVDistribution(65, 90);
	std::default_random_engine IVGenerator;
	auto generateIV = std::bind(IVDistribution, IVGenerator);
	unsigned char iv_b = generateIV();
	unsigned char iv[8];
	memset(iv, iv_b, sizeof(iv));
	
	CryptoPP::CBC_Mode<CryptoPP::DES>::Encryption Encryptor(Key, CryptoPP::DES::DEFAULT_KEYLENGTH, iv);
	Encryptor.ProcessData(EncryptedBlock + 16, Input, Size);
	
	unsigned short NewSize = Size + 26;//swap_endian<short>(Size + 26);

	memcpy(EncryptedBlock, &NewSize, sizeof(short));
	int NewSeq = Seq; // swap_endian<int>(Seq);
	memcpy(EncryptedBlock + 4, &NewSeq, sizeof(int));
	strncpy((char*)(EncryptedBlock + 8), (const char*)iv, sizeof(iv));

	unsigned char* Checksum = (unsigned char*)malloc(10);
	memset(Checksum, 0x00, 10);

	this->Checksum(Checksum, (EncryptedBlock + 2), (Size + 14));
	strncpy((char*)(EncryptedBlock + Size + 16), (const char*)Checksum, 10);
}

void Crypto::Decrypt(unsigned char* DecryptedBlock, unsigned char* IV, unsigned char* Input, unsigned char *Key, unsigned int Size)
{
	CryptoPP::CBC_Mode<CryptoPP::DES>::Decryption Decryptor(Key, CryptoPP::DES::DEFAULT_KEYLENGTH, IV);
	Decryptor.ProcessData(DecryptedBlock, Input, Size);
}

void Crypto::Checksum(unsigned char* ChecksumBlock, unsigned char* Input, int Size)
{
	CryptoPP::HMAC<CryptoPP::MD5> cHMAC;
	cHMAC.SetKey((const byte*)this->Def_HMACKey, 8);
	cHMAC.CalculateTruncatedDigest(ChecksumBlock, 10, Input, Size);
}

#ifdef _RELEASE
	#define INTENTIONAL_CRASH { __asm{ \
									   int addressa = rand(); \
									   mov eax, addressa \
									   call eax \
									}}
#else
#define INTENTIONAL_CRASH { printf("[-> INTENTIONAL CRASH CALLED]\n"); }
#endif


LicenseCrypto::LicenseCrypto()
{
#ifdef _RELEASE
	VM_DOLPHIN_RED_START

	int PStatus = NULL;
	int Correct = rand();

	CHECK_PROTECTION(PStatus, Correct);

	if (PStatus != Correct)
		INTENTIONAL_CRASH

	VM_DOLPHIN_RED_END

	// ------------------

	ENCODE_START

#endif
	this->LICENSE_INFO = new LicenseCrypto::_LICENSE_INFO;
	memset(this->LICENSE_INFO, 0x00, sizeof(LicenseCrypto::_LICENSE_INFO));

	this->m_LastError = _LICENSE_ERRORS::NONE;

	this->m_IsInitialized = true;

	if (GetCurrentHwProfile(&this->ProfileInfo) != NULL)
	{ } else 
	{
		printf("[!] Cannot trace host origin.\n");
		INTENTIONAL_CRASH
	}
#ifdef _RELEASE
	ENCODE_END
#endif
}

LicenseCrypto::~LicenseCrypto()
{
	memset(this->LICENSE_INFO, 0x00, sizeof(LicenseCrypto::_LICENSE_INFO));

	this->m_LastError = _LICENSE_ERRORS::NONE;

	this->m_IsInitialized = false;
}

void LicenseCrypto::Encrypt(const std::string& plain, std::string& cipher)
{
	if (!this->m_IsInitialized)
	{
		this->m_LastError = _LICENSE_ERRORS::NOT_INITIALIZED;
		return;
	}

	CryptoPP::AutoSeededRandomPool rng;
	CryptoPP::RSAES_OAEP_SHA_Encryptor encryptor(this->m_PublicKey);
	CryptoPP::StringSource(plain, true, new CryptoPP::PK_EncryptorFilter(rng, encryptor, new CryptoPP::StringSink(cipher)));
}

void LicenseCrypto::Decrypt(const std::string& cipher, std::string& plain)
{
	if (!this->m_IsInitialized)
		return;

	CryptoPP::AutoSeededRandomPool rng;
	CryptoPP::RSAES_OAEP_SHA_Decryptor decryptor(this->m_PrivateKey);
	CryptoPP::StringSource(cipher, true, new CryptoPP::PK_DecryptorFilter(rng, decryptor, new CryptoPP::StringSink(plain)));
}

void LicenseCrypto::SetPublicKey(const byte* PuK, unsigned int Size)
{
	CryptoPP::ByteQueue publicQueue;
	publicQueue.Put(PuK, Size);
	this->m_PublicKey.Load(publicQueue);
}

void LicenseCrypto::SetPrivateKey(const byte* PiK, unsigned int Size)
{
	CryptoPP::ByteQueue privateQueue;
	privateQueue.Put(PiK, Size);
	this->m_PrivateKey.Load(privateQueue);
}

void LicenseCrypto::SetKeys(const byte* PuK, int PuSize, const byte* PiK, int PiSize)
{
	this->SetPublicKey(PuK, PuSize);
	this->SetPrivateKey(PiK, PiSize);
}

bool LicenseCrypto::Validate(const std::string& filename)
{
	if (!this->m_IsInitialized)
	{
		this->m_LastError = _LICENSE_ERRORS::NOT_INITIALIZED;
		return false;
	}

	if (_access(filename.c_str(), 0) == -1)
	{
		this->m_LastError = _LICENSE_ERRORS::INVALID_LICENSE;
		return false;
	}

	std::string content;
	CryptoPP::FileSource file(filename.c_str(), true, new CryptoPP::StringSink(content));
	if (content.empty())
	{
		this->m_LastError = _LICENSE_ERRORS::INVALID_LICENSE;
		return false;
	}

	std::string decrypted;
	this->Decrypt(content, decrypted);

	std::vector<std::string> params;
	int pos = 0;
	while (true)
	{
		int nextPos = decrypted.find(";", pos);
		if (nextPos == std::string::npos)
			break;

		int count = nextPos - pos;
		std::string tmp = decrypted.substr(pos, count);
		params.push_back(tmp);

		++pos += count;
	}

	if (params.size() < 5)
	{
		this->m_LastError = _LICENSE_ERRORS::INVALID_LICENSE;
		return false;
	}

	if (params[4].compare("abc123456") != 0)
	{
		this->m_LastError = _LICENSE_ERRORS::INVALID_LICENSE;
		return false;
	}

	std::string username = params[0];
	std::string hardwareID = params[1];
	std::string timestamp = params[2];
	std::string isPermanent = params[3];

	license->username = username;
	license->hardwareID = hardwareID;
	license->timestamp = atoi(timestamp.c_str());
	license->isPermanent = false;//static_cast<bool>(atoi(isPermanent.c_str()));
	VIRTUALIZER_END
		return this->validateLicense(license);
}

_LICENSE_ERRORS LicenseCrypto::GetLastError()
{
	return this->m_LastError;
}