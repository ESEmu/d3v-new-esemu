#pragma once
#include "..\..\Packet Handler\Packet Handler.h"
#include "..\..\SockHandler.h"
#include "..\Server\AK_CHECKCHARNAME.h"
#include <boost\bind.hpp>
#include <functional>

static void removeCharsFromString(string &str, char* charsToRemove)
{
	for (unsigned int i = 0; i < strlen(charsToRemove); ++i)
		str.erase(remove(str.begin(), str.end(), charsToRemove[i]), str.end());
}

static bool string_is_valid(const std::string &str)
{
	return find_if(str.begin(), str.end(),
		[](char c) { return !(isalnum(c) || (c == ' ')); }) == str.end();
}

void REQ_CHECKCHARNAME(Packet* pr, SockHandler* sk)
{
	unsigned int NameSize = NULL;
	pr->GetPR()->Skip(9);

	pr->GetPR()->ReadInt(NameSize);
	std::string Name = pr->GetPR()->ReadUniString(NameSize);

	removeCharsFromString(Name, "\|!\"?$%&/()=?'^¦Ì¦Ø¡ì¦È¦É+*[]¦Ç?@?¡ã#,;.:");
	if (!string_is_valid(Name))
		AK_CHECKCHARNAME(pr, sk, false, Name);
	else
		AK_CHECKCHARNAME(pr, sk, true, Name);
}