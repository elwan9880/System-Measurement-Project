#include <iostream>
#include <stdlib.h>
#include <intrin.h>
#include <iostream>
//#include <Processthreadsapi.h>
#include <windows.h>
using namespace std;

void procedure0(){
	return;
}
void procedure1(int x){
	return;
}

void procedure2(int x1, int x2){
	return;
}

void procedure3(int x1, int x2, int x3){
	return;
}

void procedure4(int x1, int x2, int x3, int x4){
	return;
}

void procedure5(int x1, int x2, int x3, int x4, int x5){
	return;
}

void procedure6(int x1, int x2, int x3, int x4, int x5, int x6){
	return;
}

void procedure7(int x1, int x2, int x3, int x4, int x5, int x6, int x7){
	return;
}

int main(){
	__int64 tsc1, tsc2;
	double time = 0;
	double emptytime = 0;
	int loop = 1;
	/*
	procedure0();
	procedure1(1);
	procedure2(1, 2);
	procedure3(1, 2, 3);
	procedure4(1, 2, 3, 4);
	procedure5(1, 2, 3, 4, 5);
	procedure6(1, 2, 3, 4, 5, 6);
	procedure7(1, 2, 3, 4, 5, 6, 7);
	*/
	int i;
	tsc1 = __rdtsc();
	tsc2 = __rdtsc();

	tsc1 = __rdtsc();
	for ( i = 0; i < loop; i++){
		
	}
	tsc2 = __rdtsc();
	emptytime = (double)(tsc2 - tsc1);
	cout << "emptytime: " << (emptytime) / loop << " cycles." << endl;
	tsc1 = __rdtsc();
	for ( i = 0; i < loop; i++){
		procedure0();
		
	}
	tsc2 = __rdtsc();
	time = (double)(tsc2 - tsc1);
	cout << "Procedure with 0 argument time: " << (time - emptytime) / loop << " cycles." << endl;
	
	tsc1 = __rdtsc();
	for ( i = 0; i < loop; i++){
		procedure1(1);

	}
	tsc2 = __rdtsc();
	time = (double)(tsc2 - tsc1);
	cout << "Procedure with 1 argument time: " << (time - emptytime) / loop << " cycles." << endl;

	tsc1 = __rdtsc();
	for ( i = 0; i < loop; i++){
		procedure2(1,2);

	}
	tsc2 = __rdtsc();
	time = (double)(tsc2 - tsc1);
	cout << "Procedure with 2 argument time: " << (time - emptytime) / loop << " cycles." << endl;
	
	tsc1 = __rdtsc();
	for ( i = 0; i < loop; i++){
		procedure3(1,2,3);

	}
	tsc2 = __rdtsc();
	time = (double)(tsc2 - tsc1);
	cout << "Procedure with 3 argument time: " << (time - emptytime) / loop << " cycles." << endl;

	tsc1 = __rdtsc();
	for ( i = 0; i < loop; i++){
		procedure4(1,2,3,4);

	}
	tsc2 = __rdtsc();
	time = (double)(tsc2 - tsc1);
	cout << "Procedure with 4 argument time: " << (time - emptytime) / loop << " cycles." << endl;

	tsc1 = __rdtsc();
	for ( i = 0; i < loop; i++){
		procedure5(1,2,3,4,5);

	}
	tsc2 = __rdtsc();
	time = (double)(tsc2 - tsc1);
	cout << "Procedure with 5 argument time: " << (time - emptytime) / loop << " cycles." << endl;

	tsc1 = __rdtsc();
	for ( i = 0; i < loop; i++){
		procedure6(1,2,3,4,5,6);

	}
	tsc2 = __rdtsc();
	time = (double)(tsc2 - tsc1);
	cout << "Procedure with 6 argument time: " << (time - emptytime) / loop << " cycles." << endl;

	tsc1 = __rdtsc();
	for ( i = 0; i < loop; i++){
		procedure7(1,2,3,4,5,6,7);

	}
	tsc2 = __rdtsc();
	time = (double)(tsc2 - tsc1);
	cout << "Procedure with 7 argument time: " << (time - emptytime) / loop << " cycles." << endl;

	GetCurrentProcessId();
	tsc1 = __rdtsc();
	for ( i = 0; i < loop; i++){
		GetCurrentProcessId();
	}
	tsc2 = __rdtsc();
	time = (double)(tsc2 - tsc1);
	cout << "System call overhead time: " << (time - emptytime) / loop << " cycles." << endl;
	system("pause");
	return 0;
}