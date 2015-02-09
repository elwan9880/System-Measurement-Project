#include "main.h"

using namespace std;

#define loop 1

void ProcessCreation();
void ThreadCreation();
int main(int argc, const char * argv[])
{
	ProcessCreation();
	ThreadCreation();
	
	system("pause");
	return 0;
}

void ProcessCreation(){
	PROCESS_INFORMATION ProcessInfo; //This is what we get as an [out] parameter
	STARTUPINFO StartupInfo; //This is an [in] parameter
	ZeroMemory(&StartupInfo, sizeof(StartupInfo));
	StartupInfo.cb = sizeof StartupInfo; //Only compulsory field
	__int64 tsc1, tsc2;
	double time = 0;
	double emptytime = 0;
	tsc1 = __rdtsc();
	tsc2 = __rdtsc();
	tsc1 = __rdtsc();
	for (int i = 0; i < loop; i++){
		
	}
	tsc2 = __rdtsc();
	emptytime += (double)(tsc2 - tsc1);
	
	for (int i = 0; i < loop; i++){		
		tsc1 = __rdtsc();
		if (CreateProcess("../Debug/nullexe.exe", NULL,
			NULL, NULL, FALSE, 0, NULL,
			NULL, &StartupInfo, &ProcessInfo))
		{
			tsc2 = __rdtsc();
			time += (double)(tsc2 - tsc1);
			WaitForSingleObject(ProcessInfo.hProcess, INFINITE);
			CloseHandle(ProcessInfo.hThread);
			CloseHandle(ProcessInfo.hProcess);
		}
		else
		{
			printf("The process could not be started...\n");
		}
	}
	cout << "Process creation time: " << (time - emptytime) / loop << " cycles." << endl;

}

void ThreadCreation(){
	DWORD ThreadId;
	__int64 tsc1, tsc2;
	double time = 0;
	double emptytime = 0;
	int i;
	tsc1 = __rdtsc();
	tsc2 = __rdtsc();
	tsc1 = __rdtsc();
	for (i = 0; i < loop; i++){		
		emptytime += 0;
	}
	tsc2 = __rdtsc();
	emptytime += (double)(tsc2 - tsc1);
	
	for ( i = 0; i < loop; i++){
		tsc1 = __rdtsc();
		HANDLE h = CreateThread(NULL, 0, NullThread, &tsc2, 0, &ThreadId);
		WaitForSingleObject(h, INFINITE);
		CloseHandle(h);		
		time += (double)(tsc2 - tsc1);
	}
	//tsc2 = __rdtsc();
	//time = (double)(tsc2 - tsc1);
	cout << "Thread creation time: " << (time - emptytime) / loop << " cycles." << endl;
	return;
}


DWORD WINAPI NullThread(LPVOID lpParam) {
	*((__int64*)lpParam) = __rdtsc();
	ExitThread(0);
}