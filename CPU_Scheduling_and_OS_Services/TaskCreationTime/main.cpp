#include <windows.h> 
#include "main.h" 
using namespace std;
#define loop 10
void ThreadContextSwitch();
void ProcesContextSwitch();
DWORD WINAPI NewThread(LPVOID );

int main(){
	ThreadContextSwitch();
	cout << endl;
	for (int i = 0; i < loop; i++){
		ProcesContextSwitch();
	}
	cout << endl;
	system("pause");
	return 0;
}

void ThreadContextSwitch(){
	DWORD Id;
	__int64 tsc1, tsc2;
	double time = 0;
	double emptytime = 0;
	tsc1 = __rdtsc();
	for (int i = 0; i < loop; i++){
		time += 0;
	}
	tsc2 = __rdtsc();
	emptytime = (double)(tsc2 - tsc1);

	for (int i = 0; i < loop; i++){
		tsc1 = 0;
		HANDLE h = CreateThread(NULL, 0, NewThread, &tsc1, 0, &Id);
		while (tsc1 == 0){}
		TerminateThread(h, 0);
		tsc2 = __rdtsc();
		time += (tsc2 - tsc1);
		CloseHandle(h);
	}
	cout << "Thread context switch time: " << (time-emptytime) / loop << " cycles." << endl;
	return;
}

void ProcesContextSwitch(){
	__int64 tsc1, tsc2;
	double avg = 0;
	HANDLE inRead = NULL;
	HANDLE inWrite = NULL;
	HANDLE outRead = NULL;
	HANDLE outWrite = NULL;

	SECURITY_ATTRIBUTES sattr;
	sattr.nLength = sizeof(SECURITY_ATTRIBUTES);
	sattr.bInheritHandle = TRUE;
	sattr.lpSecurityDescriptor = NULL;
	CreatePipe(&outRead, &outWrite, &sattr, 0);
	SetHandleInformation(outRead, HANDLE_FLAG_INHERIT, 0);
	CreatePipe(&inRead, &inWrite, &sattr, 0);
	SetHandleInformation(inWrite, HANDLE_FLAG_INHERIT, 0);

	PROCESS_INFORMATION pInfo;
	STARTUPINFO sInfo;
	ZeroMemory(&pInfo, sizeof(PROCESS_INFORMATION));
	ZeroMemory(&sInfo, sizeof(STARTUPINFO));
	sInfo.cb = sizeof(STARTUPINFO);
	sInfo.hStdError = outWrite;
	sInfo.hStdOutput = outWrite;
	sInfo.hStdInput = inRead;
	sInfo.dwFlags |= STARTF_USESTDHANDLES;

	CreateProcess(NULL, "../Debug/simple exe.exe", NULL, NULL, TRUE, 0, NULL, NULL, &sInfo, &pInfo);
	char buf = { 'a' };
	int bytes;
	Sleep(1000);
	tsc1 = __rdtsc();
	WriteFile(inWrite, &buf, 1, (LPDWORD)&bytes, NULL);
	ReadFile(outRead, &buf, 1, (LPDWORD)&bytes, NULL);
	tsc2 = __rdtsc();
	avg = (double)tsc2 - tsc1;
	cout << "Process context switch time: " << avg / 2 << " cycles." << endl;
}

DWORD WINAPI NewThread(LPVOID lpParam) {
	while (1){
		*((__int64*)lpParam) = __rdtsc();
	}
	return 0;
}