#include <iostream>
#include <intrin.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
using namespace std;
#define PageSize 32677
#define MEGA 1000
#define CLOCKS_PER_SEC 3292140000

char* RandChar(const unsigned long long bytelength) {
	srand((unsigned int)time(NULL));
	unsigned long long size = bytelength * sizeof(char);
	char* cArray = (char*)malloc(size);
	for (unsigned long long i = 0; i < bytelength; i++) {
		*(cArray + i) = rand() % 26 + 'a';
	}
	return cArray;
}

void CharFileNoBuf(char* name, int Megasize){
	HANDLE h = CreateFile(name, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_FLAG_NO_BUFFERING, NULL);
	for (int i = 0; i < Megasize; i++){
		char* data = RandChar(1024 * 1024);
		DWORD written;
		WriteFile(h, data, 1024 * 1024, &written, NULL);
		free(data);
	}
	CloseHandle(h);
}


void GetFileReadTime(){
	char filename[10] = "0.tmp";
	int x;
	for (int n = 0; n <= 10; n++){
		filename[0] = (int)filename[0] + 1;
		x = (int)pow((float)2, n);
		CharFileNoBuf( filename, x );
		HANDLE h = CreateFile(filename, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_FLAG_NO_BUFFERING, NULL);
		int stride = 512;
		int fileSize = 1024 * 1024 * x;
		int totalStep = 1024;
		DWORD step;
		char* buf = (char*)malloc(stride);
		__int64 tsc1, tsc2;
		tsc1 = __rdtsc();
		tsc2 = __rdtsc();
		double time = 0;
		double emptytime = 0;
		for (int i = 0; i < totalStep; i++){
			tsc1 = __rdtsc();
			
			tsc2 = __rdtsc();
			emptytime += (double)(tsc2 - tsc1);
		}

		for (int i = 0; i < totalStep; i++){
			tsc1 = __rdtsc();
			BOOL b = ReadFile(h, buf, stride, &step, NULL);
			tsc2 = __rdtsc();
			time += (double)(tsc2 - tsc1);
		}
		free(buf);
		cout << x << "MB disk sequential read time per block: " << ( time- emptytime ) / totalStep << " cycles." << endl;
		CloseHandle(h);
	}
	cout << endl;
	filename[0] = '0';
	for (int n = 0; n <= 10; n++){
		filename[0] = (int)filename[0] + 1;
		HANDLE h = CreateFile(filename, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_FLAG_NO_BUFFERING, NULL);
		int stride = 512;
		int fileSize = 1024 * 1024 * pow((float)2, n);
		int totalStep = fileSize / stride;
		DWORD step;
		char* buf = (char*)malloc(stride);
		__int64 tsc1, tsc2;
		double avg = 0;
		srand(time(NULL));
		double emptytime = 0;
		tsc1 = __rdtsc();
		tsc2 = __rdtsc();
		for (int i = 0; i < 1024; i++){
			tsc1 = __rdtsc();
			tsc2 = __rdtsc();
			emptytime += (double)(tsc2 - tsc1);
		}
		for (int i = 0; i < 1024; i++){
			int pos = (rand()*RAND_MAX + rand()) % totalStep;
			DWORD d = SetFilePointer(h, pos*stride, NULL, FILE_BEGIN);
			tsc1 = __rdtsc();
			BOOL b = ReadFile(h, buf, stride, &step, NULL);
			tsc2 = __rdtsc();
			avg += (double)(tsc2 - tsc1);
		}
		free(buf);
		cout << (int)pow((float)2, n) << "MB disk random access read time per block: " << (avg- emptytime) / 1024 << " cycles." << endl;
		CloseHandle(h);
	}
}

int main() {
	GetFileReadTime();
	system("pause");
	return 0;
}