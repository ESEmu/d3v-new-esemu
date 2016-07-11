#pragma once
#ifndef _THREADMANAGER_H_
#define _THREADMANAGER_H_
#include "..\Common\Credits.h"
#ifdef IS_DEVELOPMENT

#include <iostream>
#include "..\Network\SockHandler.h"
#include "..\DBHandler\DBHandler.h"
#include "_PriorityEngine.h"
#include <boost\thread.hpp>

struct _WORKER_INFO
{
	unsigned long long	ID;
	Server*				SHandler;
	ConfigManager*		CMHandler;
	DATABASE*			DBHandle;
	const char*			IP;
	short				Port;
	HANDLE				ThreadHandle;
	boost::thread		BThreadHandle;
	short				SType;
};

class ThreadManager:public _PriorityEngine
{
private:

	LPVOID*			Workers;
	ConfigManager*  CM;

public:

	bool Initialize(short MaxWorkers, ConfigManager* CMHandler);
	bool Spawn(short ID, short Type);
	void Pause(short ID);
	void Resume(short ID);
	void Shutdown(short ID);
	void UpdatePriorityEngine(short ID, unsigned long long Players);
};

#endif
#endif