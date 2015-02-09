#include "main.h"

//#pragma intrinsic(__rdtsc)

using namespace std;
#define PageSize 32677
#define LIMIT 1073741824 // Giga = 1024 x 1024 x 1024 1073741824
//#define MEGA 1048576
#define MEGA 100
#define CLOCKS_PER_SEC 3292140000

/*
int procedure(int x){
	return 0;
}
*/

int main() {

	//cout << i << "\n";
	int a = 0;
	double i = (double)__rdtsc();
	double k = (double)__rdtsc();
	int mm;
	i = (double)__rdtsc();
	
	for (mm = 0; mm < MEGA; mm++)
	{


	}
	//}

	k = (double) __rdtsc();
	//cout << k << "\n";
	double diff = (k - i);// / (double)CLOCKS_PER_SEC;
	cout << "Looptime is " << diff / MEGA << endl;
	//cout<<"size of int ="<<sizeof(int)<<endl;
	int j;
	double m = (double) __rdtsc();
	double n = (double)__rdtsc();
	m = (double)__rdtsc();
	for (j = 0; j < MEGA; j++)
	{
		//procedure(0);
		a;

	}
	n = (double) __rdtsc();
	double diff2 = (n - m);// / (double)CLOCKS_PER_SEC;
	cout << "Readtime is " << diff2 / MEGA << endl;
	//cout << "function call time is " << diff2 / MEGA << endl;
	cout << "Pure readtime is " << (diff2 - diff) / MEGA << endl;
	cout << "In second : " << ( 1000000000 * (diff2 - diff) / MEGA) / CLOCKS_PER_SEC<< "ns" << endl;
	system("pause");
	return 0;
}