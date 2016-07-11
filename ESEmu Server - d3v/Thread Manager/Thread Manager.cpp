#include "Thread Manager.h"

#ifdef IS_DEVELOPMENT

CRITICAL_SECTION wCriticalSection;

void WorkerThread(_WORKER_INFO *WInfo)
{
	InitializeCriticalSection(&wCriticalSection);
	printf("[+] Worker %d started.\n", WInfo->ID);
	while (true)
	{
		try
		{
			if (!WInfo->SHandler->Initialize(WInfo->IP, WInfo->Port, WInfo->CMHandler, WInfo->SType))
				printf("[W.%d] [!] Initialize error.\n", WInfo->ID);
			else
				WInfo->SHandler->Start();
			break;
		} catch (std::exception & ex) {
			printf("[W.%d] [!] Initialize trial error (%s).\n", WInfo->ID, ex.what());
		}
		WorkerThread(WInfo);
	}
	printf("[!] A thread shutted down!\n");
	LeaveCriticalSection(&wCriticalSection);
}

#define EXISTING_THREADS this->Workers != nullptr

bool ThreadManager::Initialize(short MaxWorkers, ConfigManager* CMHandler)
{
	if (MaxWorkers <= 50 && !(MaxWorkers < 1))
	{
		this->Workers = reinterpret_cast<HANDLE*>(malloc(MaxWorkers * sizeof(HANDLE)));
		memset(this->Workers, 0x00, (MaxWorkers * sizeof(HANDLE)));
		
		this->CM = CMHandler;
		return true;
	}
	return false;
}

bool ThreadManager::Spawn(short ID, short Type)
{
	Server* cServer = nullptr;
	if (Type == 1)
		cServer = new Server(9400);
	else
		cServer = new Server(9300);
	_WORKER_INFO* WorkerInfo = new (_WORKER_INFO);
	
	if (Type == 1)
	{
		//printf("[+] Spawning Worker %d.\n", ID);
		WorkerInfo->ID = ID;
		WorkerInfo->CMHandler = new(ConfigManager);
		WorkerInfo->CMHandler->load(1);
		WorkerInfo->SHandler = cServer;
		WorkerInfo->IP = this->CM->getString(this->CM->SERVER_IP).c_str();
		WorkerInfo->Port = this->CM->getNumber(this->CM->SERVER_PORT);
		//WorkerInfo->DBHandle = new DATABASE(this->CM);
		WorkerInfo->SType = Type;

		//this->Workers[ID] = CreateThread(NULL, 65535, (LPTHREAD_START_ROUTINE)WorkerThread, WorkerInfo, NULL, (LPDWORD)&WorkerInfo->ThreadHandle);
		boost::thread w(WorkerThread, WorkerInfo);
		w.join();

		if (!this->Workers[ID])
		{
			//printf("Worker %d has not been created (%ld).\n", ID, GetLastError());
			//return false;
		}
	} else if (Type == 2) {
		//printf("[+] Spawning Worker %d.\n", ID);
		WorkerInfo->ID = ID;
		WorkerInfo->CMHandler = new(ConfigManager);
		WorkerInfo->CMHandler->load(2);
		WorkerInfo->SHandler = cServer;
		WorkerInfo->IP = this->CM->getString(this->CM->SERVER_IP).c_str();
		WorkerInfo->Port = this->CM->getNumber(this->CM->SERVER_PORT);
		//WorkerInfo->DBHandle = new DATABASE(this->CM);
		WorkerInfo->SType = Type;

		//this->Workers[ID] = CreateThread(NULL, 65535, (LPTHREAD_START_ROUTINE)WorkerThread, WorkerInfo, NULL, (LPDWORD)&WorkerInfo->ThreadHandle);
		boost::thread w(WorkerThread, WorkerInfo);
		w.join();
		if (!this->Workers[ID])
		{
			//printf("Worker %d has not been created (%ld).\n", ID, GetLastError());
			//return false;
		}
	}
	
	
	return true;
}

void ThreadManager::Resume(short ID)
{
	if (EXISTING_THREADS)
		ResumeThread(this->Workers[ID]);
}

void ThreadManager::Pause(short ID)
{
	if (EXISTING_THREADS)
		SuspendThread(this->Workers[ID]);
}

void ThreadManager::Shutdown(short ID)
{
	if (EXISTING_THREADS)
		CloseHandle(this->Workers[ID]);
}

#define LEVEL_LOW		1
#define LEVEL_MEDIUM	2
#define LEVEL_HIGH		3
#define LEVEL_CRITICAL	4
#define LEVEL_DEAD		-1

void ThreadManager::UpdatePriorityEngine(short ID, unsigned long long Players)
{
	switch (_PriorityEngine::GetPriorityLevel(Players, this->CM))
	{
	case LEVEL_LOW:
		SetThreadPriority(this->Workers[ID], THREAD_PRIORITY_ABOVE_NORMAL);
		break;
	case LEVEL_MEDIUM:
		SetThreadPriority(this->Workers[ID], THREAD_PRIORITY_NORMAL);
		break;
	case LEVEL_HIGH:
		SetThreadPriority(this->Workers[ID], THREAD_PRIORITY_HIGHEST);
		break;
	case LEVEL_CRITICAL:
		SetThreadPriority(this->Workers[ID], THREAD_PRIORITY_TIME_CRITICAL);
		break;
	case LEVEL_DEAD:
		SetThreadPriority(this->Workers[ID], THREAD_PRIORITY_TIME_CRITICAL);
		break;
	}
}

#endif