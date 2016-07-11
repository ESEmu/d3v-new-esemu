#pragma once
#ifndef _PACKETHANDLERXXX_H_
#define _PACKETHANDLERXXX_H_
#pragma warning (disable: 4996)

#include <vector>
#include <string>
#include <sstream>
#include "..\..\DBHandler\DBHandler.h"
// #define SEND { sk->Send(*pr->GetPB(), false, sk); }
#define SEND { sk->Send(pck->GetPB()->GetBuffer(), pck->GetPB()->GetSize()); }

template <typename T>

static void SwapEnd(T& var)
{
	T varSwapped;

	for (long i = 0; i < static_cast<long>(sizeof(var)); i++)
		((char*)(&varSwapped))[sizeof(var)-1 - i] = ((char*)(&var))[i];

	for (long i = 0; i < static_cast<long>(sizeof(var)); i++)
		((char*)(&var))[i] = ((char*)(&varSwapped))[i];

}

class PacketBuilder
{
	unsigned int				m_Index;
	unsigned char*				m_Buffer;
	unsigned int				m_BufferSize;

public:

	#define SECURE_BUFFER this->m_Buffer != nullptr

	void Init(unsigned int Size)
	{
		this->m_Index = NULL;
		this->m_BufferSize = Size;
		this->m_Buffer = (unsigned char*)malloc(Size);
		memset(this->m_Buffer, 0x00, Size);
	}
	
	void ExtendBufferBy(unsigned int AddingBytes)
	{
		unsigned char* OldBuffer = (unsigned char*)malloc(this->m_BufferSize);
		memset(OldBuffer, 0x00, this->m_BufferSize);

		memcpy(OldBuffer, this->m_Buffer, this->m_BufferSize);

		free(this->m_Buffer);
		this->m_Buffer = (unsigned char*)malloc(this->m_BufferSize + AddingBytes);
		memset(this->m_Buffer, 0x00, this->m_BufferSize + AddingBytes);
		this->m_BufferSize += AddingBytes;

		memcpy(this->m_Buffer, OldBuffer, this->m_BufferSize);
	}

	std::vector<unsigned char> ToVector()
	{
		std::vector<unsigned char> finalBuffer(this->m_Index);
		for (auto i = 0; i < this->m_Index; i++)
			finalBuffer.push_back(this->m_Buffer[i]);
		return finalBuffer;
	}

	void WriteOPCode(unsigned char UpperOPC, unsigned char LowerOPC)
	{
		if (SECURE_BUFFER)
		{
			memcpy((this->m_Buffer) + this->m_Index, (const void*)&UpperOPC, sizeof(unsigned char));
			this->m_Index += sizeof(unsigned char);

			memcpy((this->m_Buffer) + this->m_Index, (const void*)&LowerOPC, sizeof(unsigned char));
			this->m_Index += sizeof(unsigned char);
		}
	}

	template <class T>
	void Append(const T value)
	{
		if (SECURE_BUFFER)
		{
			SwapEnd<T>((T)value);
			memcpy((this->m_Buffer) + this->m_Index, &value, sizeof(T));
			this->m_Index += sizeof(T);
		}
	}

	void WriteString(char* String, unsigned int Size)
	{
		if (SECURE_BUFFER)
		{
			strncpy(((char*)this->m_Buffer + this->m_Index), (const char*)String, Size);
			this->m_Index += Size;
		}
	}

	void WriteUniString(char* String, unsigned int Size)
	{
		if (SECURE_BUFFER)
		{
			if (Size > 0)
			{
				this->Append<unsigned int>((Size * 2));
				std::vector<unsigned char> finalized(0);

				for (auto i = 0; i <= Size; i++)
				{
					finalized.push_back(String[i]);
					if (i != Size)
						finalized.push_back(0x00);
				}

				for (int k = 0; k < (Size * 2); k++)
					memcpy((this->m_Buffer + this->m_Index) + k, (const unsigned char*)&finalized[k], sizeof(unsigned char));

				this->m_Index += Size * 2;
			}
		}
	}

	void WriteBuffer(char* Buffer, unsigned int Size)
	{
		if (SECURE_BUFFER)
		{
			if (Size > 0)
			{
				memcpy(((unsigned char*)this->m_Buffer) + this->m_Index, Buffer, Size);
				this->m_Index += Size;
			}
		}
	}

	void WriteHeader(unsigned char UpperOPC, unsigned char LowerOPC) {
		WriteBuffer("\x00\x00\x01\x01\x00\x00\x00\x01\x40\x00\x00\x9D\xC9\x86\x9F\x67\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF", 32);
		WriteOPCode(UpperOPC, LowerOPC);
		WriteBuffer("\x00\x00\x00\x00\x00", 5);
	}

	void WriteEmptyHeader(unsigned char UpperOPC, unsigned char LowerOPC) {
		WriteBuffer("\x00\x00\x01\x01\x00\x00\x00\x01\x40\x00\x00\x9D\xC9\x86\x9F\x67\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF", 32);
		WriteOPCode(UpperOPC, LowerOPC);
		WriteBuffer("\x00\x00\x00\x00", 4);
	}

	void WriteEnd() {
		this->m_Buffer[34] = ((this->m_Index-39) >> 24) & 0xFF;
		this->m_Buffer[35] = ((this->m_Index-39) >> 16) & 0xFF;
		this->m_Buffer[36] = ((this->m_Index-39) >> 8) & 0xFF;
		this->m_Buffer[37] = (this->m_Index-39) & 0xff;

		int length = 8 - (this->m_Index % 8) - 1;
		if (length == 0) length = 8;
		int i;
		for (i = 1; i <= length; i++) {
			this->m_Buffer[this->m_Index] = i;
			this->m_Index++;
		}
		this->m_Buffer[this->m_Index] = length;
		this->m_Index++;
	}

	unsigned char* GetBuffer()
	{
		return this->m_Buffer;
	}

	void CopyBuffer(unsigned char* Location)
	{
		memcpy(Location, this->m_Buffer, this->m_Index);
	}

	unsigned int GetSize()
	{
		return this->m_Index;
	}
};

class PacketReader
{
	unsigned int m_Index;
	unsigned char* m_Buffer;
	unsigned int m_OriginalSize;
public:

	void Init(unsigned char* Buffer, unsigned int Size)
	{
		this->m_Index = NULL;
		this->m_Buffer = (unsigned char*)malloc(Size);
		this->m_OriginalSize = Size;
		memset(this->m_Buffer, 0x00, Size);

		memcpy(this->m_Buffer, Buffer, Size);
	}

	void ReadByte(unsigned char& PlaceHolder)
	{
		this->m_Index += sizeof(unsigned char);
		PlaceHolder = this->m_Buffer[this->m_Index - 1];
	}

	void ReadShort(unsigned short& PlaceHolder)
	{
		this->m_Index += sizeof(unsigned short);
		PlaceHolder = ((this->m_Buffer[this->m_Index - 2] << 8) | this->m_Buffer[this->m_Index - 1]);
	}

	void ReadInt(unsigned int& PlaceHolder)
	{
		this->m_Index += sizeof(unsigned int);
		PlaceHolder = ((this->m_Buffer[this->m_Index - 4] << 24) | (this->m_Buffer[this->m_Index - 3] << 16) | (this->m_Buffer[this->m_Index - 2] << 8) | this->m_Buffer[this->m_Index - 1]);
	}

	template <class T>
	void Read(T& PlaceHolder)
	{
		if (SECURE_BUFFER)
		{
			PlaceHolder = (T)(&this->m_Buffer + this->m_Index);
			this->m_Index += sizeof(T);
			return;
		}
		return;
	}

	char* ReadString(int Size)
	{
		if (SECURE_BUFFER)
		{
			if (Size > 0)
			{
				char* String = (char*)malloc(Size);
				memset(String, 0x00, Size);

				strncpy(String, (const char *)*(&this->m_Buffer + this->m_Index), Size);
				this->m_Index += Size;
				return String;
			}
		}
	}

	void Skip(int Amount)
	{
		if (SECURE_BUFFER)
		{
			this->m_Index += Amount;
		}
	}

	std::string ReadUniString(unsigned int Size)
	{
		if (SECURE_BUFFER)
		{
			if (Size > 1)
			{
				std::string str;

				for (auto i = this->m_Index; i < this->m_Index + Size; i += 2)
					str += static_cast<char>(this->m_Buffer[i]);
				str += '\0';

				this->m_Index += Size;

				return str;
			}
		}
		return "";
	}

	unsigned int GetSize()
	{
		return this->m_OriginalSize;
	}

	unsigned char* GetBuffer()
	{
		return this->m_Buffer;
	}
};

class Packet
{
	PacketReader*  pr;
	PacketBuilder* pb;
	DATABASE*	   db;

public:
	Packet() {}
	~Packet() {}

	void Init(DATABASE* DBH)
	{
		this->pr = new(PacketReader);
		this->pb = new(PacketBuilder);
		this->db = DBH;
	}

	PacketReader* GetPR()
	{
		return this->pr;
	}

	PacketBuilder* GetPB()
	{
		return this->pb;
	}

	DATABASE* GetDB()
	{
		return this->db;
	}
};

#endif _PACKETHANDLER_H_