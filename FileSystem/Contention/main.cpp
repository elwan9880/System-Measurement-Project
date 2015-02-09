#include <iostream>
#include <intrin.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
using namespace std;
#define PageSize 32677
#define MEGA 1000
#define CLOCKS_PER_SEC 3292140000



void Contention(){

	__int64 tsc1, tsc2;
	double avg = 0;

	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	char fn[6] = "a.tmp";
	char my_fn[7] = "my.tmp";
	char cmd[40] = "../Debug/contention-proccess.exe a.tmp";
	for (int j = 1; j<20; j++){
		for (int i = 0; i<j; i++){
			CreateProcess(NULL, cmd, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
			cmd[33]++;
		}
		HANDLE my_h = CreateFile(my_fn, GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_FLAG_NO_BUFFERING, NULL);
		char buffer[512];
		int bytes;
		for (int i = 0; i<100; i++){
			tsc1 = __rdtsc();
			ReadFile(my_h, buffer, 512, (LPDWORD)&bytes, NULL);
			tsc2 = __rdtsc();
			avg += (double)tsc2 - tsc1;
		}
		cout << "Among " << j << " contention processes, avg disk read time per block: " << avg / 100 << " cycles." << endl;
		Sleep(2000);
	}
	return;
}

int main() {
	Contention();
	system("pause");
}