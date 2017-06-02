#include <unistd.h>

int main() {
	/*double *array = new double[60000];
	for(int i = 0; i < 60000; i++){
		array[i] = 10000;
	}
	usleep(100000000);*/
	double *morre_diabo = new double[1024*1024*900];
	for (int i = 0; i < 1024*1024*900; ++i)
		morre_diabo[i] = 34.535234;
	return 0;
}
