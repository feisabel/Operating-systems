#include <unistd.h>
#include <cstdio>
#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <sys/types.h>
#include <ulimit.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <errno.h>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <string.h>
#include <thread>
#include <pthread.h>

#define PATH_ADC "/sys/bus/iio/devices/iio:device0/in_voltage"
using namespace std;
int n = 20, m = 20;
bool jump = false;
bool running = true;

void draw() {
	if(!jump) {
		cout << "\r" << endl << endl << endl << endl << endl << endl << endl;
		string s1 = "";
		string s2 = "";
		for(int i = 0; i < n; i++) {
			s1 += " ";
		}
		for(int i = 0; i < m; i++) {
			s2 += " ";
		}
		cout << s1 << " o " << s2 << endl << s1 << "`|," << s2 << endl << s1 << " ^ " << s2 << endl;
	}
	else {
		cout << "\r" << endl << endl << endl << endl;
		string s1 = "";
		string s2 = "";
		for(int i = 0; i < n; i++) {
			s1 += " ";
		}
		for(int i = 0; i < m; i++) {
			s2 += " ";
		}
		cout << s1 << " o " << s2 << endl << s1 << "`|," << s2 << endl << s1 << " ^ " << s2 << endl;
		cout << endl << endl << endl;
	}
}

void read_pot(){
	int number = 1;
	while(running) {
		
		stringstream ss;
    	ss << PATH_ADC << number << "_raw";
    	fstream fs;
    	fs.open(ss.str().c_str(), fstream::in);
    	fs >> number;
    	fs.close();
    	//cout << n << " " << m << " " << number<< endl;
    	if(number > 2048) {
    		if (n > 0) {
				n--;
				m++;
			}
    	}
    		
    	else {
    		if (m > 0) {
				m--;
				n++;
			}
    	}
    	system("clear");
    	draw();
    	number = 1;
    }
}

void read_botao(){

}

void read_luz(){

}


int main() {
	draw();
	char c;
	std::thread pot(read_pot);
	std::thread botao(read_botao);
	std::thread luz(read_luz);
	struct sched_param param1;
	struct sched_param param2;
	struct sched_param param3;
	param1.sched_priority = sched_get_priority_max(SCHED_RR);
	param3.sched_priority = sched_get_priority_min(SCHED_RR);
	param2.sched_priority = sched_get_priority_max(SCHED_RR)/2;
	pthread_setschedparam(pot.native_handle(), SCHED_RR, &param1);
	pthread_setschedparam(luz.native_handle(), SCHED_RR, &param2);
	pthread_setschedparam(botao.native_handle(), SCHED_RR, &param3);
	cin >> c;

	if(c == 'q') {
		/*if(c == 'j') {
			if (n > 0) {
				n--;
				m++;
			}
		}
		else if(c == 'k') {
			if (m > 0) {
				m--;
				n++;
			}
		}*/
		running = false;
	}
	pot.join();
	botao.join();
	luz.join();

}