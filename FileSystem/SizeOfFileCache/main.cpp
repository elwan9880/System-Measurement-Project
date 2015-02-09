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

void CharFile(char* name, int Megasize){
	HANDLE mfile = CreateFile(name, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	for (int i = 0; i < Megasize; i++){
		char* data = RandChar(1024 * 1024);
		DWORD written;
		WriteFile(mfile, data, 1024 * 1024, &written, NULL);
		free(data);
	}
	CloseHandle(mfile);
}


void FileAccess(){
	char filename[10] = "0.tmp";
	int x;
	for (int j = 0; j <= 10; j++){
		filename[0] = (int)filename[0] + 1;
		x = (int)pow((float)2, j);
		CharFile(filename, x);
		HANDLE h = CreateFile(filename, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		int stride = 1024 * 256;
		int fileSize = 1024 * 1024 * x;
		int pos = 0;
		DWORD step;
		char* buf = (char*)malloc(stride);
		__int64 tsc1, tsc2;
		tsc1 = __rdtsc();
		tsc2 = __rdtsc();
		double time = 0;
		double emptytime = 0;
		
		for(int i = 0; i < 10000; i++){
			tsc1 = __rdtsc();
			tsc2 = __rdtsc();	
			emptytime += (double)(tsc2 - tsc1);
		}
		
		for (int i = 0; i < 10000; i++){
			tsc1 = __rdtsc();
			BOOL b = ReadFile(h, buf, stride, &step, NULL);
			tsc2 = __rdtsc();
			time += (double)(tsc2 - tsc1);
			pos += (int)step;
			if (fileSize - pos < stride){
				DWORD d = SetFilePointer(h, 0, NULL, FILE_BEGIN);
			}
		}
		free(buf);
		cout << x << "MB file read time (each time cached 256 KB): " << (time - emptytime) / 10000 << " cycles." << endl;
	}
}

int main() {
	FileAccess();
	system("pause");
	return 0;
}