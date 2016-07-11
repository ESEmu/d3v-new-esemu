#pragma once
//#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#ifndef CRYPTOPP_DLL_ONLY
	#define CRYPTOPP_DEFAULT_NO_DLL
#endif
#include "dll.h"
#include <md5.h>
#include <cstring>
#include <cstdio>
#include <random>
#include <functional>
#include <rsa.h>
#include <osrng.h>
#include <files.h>
#include <base64.h>
#include <aes.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <sstream>
#include <time.h>
#include <string>
#include <ThemidaSDK.h>
using namespace std;

#ifdef _DEBUG
	#pragma comment(lib, "cryptlibd.lib")
	#pragma comment(lib, "cryptopp.lib")
#else
	#pragma comment(lib, "cryptlib.lib")
	//#pragma comment(lib, "cryptopp.lib")
#endif

#define TYPE_DES	1
#define TYPE_HMAC	2

class Crypto
{
public:
	unsigned char DESKey[8];
	unsigned char HMACKey[8];
	unsigned char Def_DESKey[8];
	unsigned char Def_HMACKey[8];

	void Init();
	void SetKey(char Type, char Key[8]);
	void Encrypt(unsigned char* EncryptedBlock, unsigned char* Input, unsigned int Size, unsigned char *Key, unsigned int Seq);
	void Decrypt(unsigned char* DecryptedBlock, unsigned char* IV, unsigned char* Input, unsigned char *Key, unsigned int Size);
	void Checksum(unsigned char* ChecksumBlock, unsigned char* Input, int Size);
	void Raw_Encrypt(unsigned char* EncryptedBlock, unsigned char* Input, unsigned int Size, unsigned char* Key, unsigned char* IV);
	void Raw_Decrypt(unsigned char* DecryptedBlock, unsigned char* Input, unsigned int Size, unsigned char* Key, unsigned char* IV);
	
};

enum _LICENSE_ERRORS
{
	NONE,
	NOT_INITIALIZED,
	INVALID_KEY,
	INVALID_LICENSE
};

class LicenseCrypto
{
private:

	struct _LICENSE_INFO
	{
		string Username;
		string GUID;
		string ProfileID;
	} *LICENSE_INFO;

	HW_PROFILE_INFO ProfileInfo;
	CryptoPP::RSA::PublicKey  m_PublicKey;
	CryptoPP::RSA::PrivateKey m_PrivateKey;

	bool m_IsInitialized;

	_LICENSE_ERRORS m_LastError;

	void Encrypt(const std::string& plain, std::string& cipher);
	void Decrypt(const std::string& cipher, std::string& plain);


public:

	LicenseCrypto();
	~LicenseCrypto();

	void SetPublicKey(const byte* PuK, unsigned int Size);
	void SetPrivateKey(const byte* PiK, unsigned int Size);
	void SetKeys(const byte* PuK, int PuSize, const byte* PiK, int PiSize);

	bool Validate(const std::string& filename);

	_LICENSE_ERRORS GetLastError();
};