#include <unistd.h>

int main() {
	/*double *array = new double[60000];
	for(int i = 0; i < 60000; i++){
		array[i] = 10000;
	}
	*/
	double *morre_diabo = new double[1024*1024*700];
	for (int i = 0; i < 1024*1024*700; ++i)
		morre_diabo[i] = 34.535234;
	usleep(100000000);
	return 0;
}
