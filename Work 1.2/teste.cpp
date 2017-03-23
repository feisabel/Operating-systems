#include "api_gpio/pin.h"
#include "api_gpio/pmap.h"
#include <iostream>
#include <stdio.h>
#include <string.h> //stoi strcpy
#include <fstream>
#include <cstring>
#include <unistd.h> /*uslee sysconf*/

#include <stdexcept>
#include <sstream>  // istringstream


using namespace std;

/*
* http://stackoverflow.com/questions/16726779/how-do-i-get-the-total-cpu-usage-of-an-application-from-proc-pid-stat
* http://man7.org/linux/man-pages/man5/proc.5.html
*/
double getCpuUsage(int pid){
	ifstream stat;
	int utime, stime, cutime, cstime, starttime, uptime, seconds, hertz;
	double cpu_usage, total_time;
	string aux;

	stat.open("/proc/uptime");
	stat >> aux; uptime = stoi(aux);
	stat.close();

	stat.open("/proc/"+to_string(pid)+"/stat");
	for(int i = 1; i < 15; i ++){
		stat >> aux; //14
		//cout << "i : " << i << " => " << utime << endl;
	}
	utime = stoi(aux);
	stat >> aux; stime = stoi(aux);
	stat >> aux; cutime = stoi(aux);
	stat >> aux; cstime = stoi(aux);
	for (int i =1 ; i < 6; i++){
		stat >> aux;
	}
	starttime = stoi(aux);
	stat.close();

	total_time = utime + stime + cutime + cstime;
	hertz = sysconf(_SC_CLK_TCK);
	seconds = uptime - (starttime / hertz);
	cpu_usage = 100 * ((total_time/hertz)/seconds);

	/*cout << "uptime: " << uptime << endl;
	cout << "utime: " << utime << endl;
	cout << "stime: " << stime << endl;
	cout << "cutime: " << cutime << endl;
	cout << "cstime: " << cstime << endl;
	cout << "starttime: " << starttime << endl;
	cout << "Total time: " << total_time << endl;
	cout << "Hertz " << hertz << endl;
	cout << "seconds " << seconds << endl;*/
	cout << "CPU usage: " << cpu_usage << endl;
	return cpu_usage;
}

int main(void){
	init();
	
	int pid;;
  	cin >> pid;
  	double cpu_usage;
  	unsigned int microseconds = 100000; //0.1s
  	unsigned int w = 2000000; //2s
		
	Pin red ("P9_14", Direction::OUT, Value::LOW);
	Pin yellow ("P9_16", Direction::OUT, Value::LOW);
	Pin green ("P9_22", Direction::OUT, Value::LOW);

	while(1){
		cpu_usage = getCpuUsage(pid);
		if (cpu_usage < 25) {
			green.setOn();
			yellow.setOff();
			red.setOff();
		} else if (cpu_usage < 50) {
			green.setOff();
			yellow.setOn();
			red.setOff();
		} else if (cpu_usage < 75) {
			green.setOff();
			yellow.setOff();
			red.setOn();
		} else {
			green.changeValue();
			yellow.changeValue();
			red.changeValue();
			usleep(microseconds); 
		}
	}


	return 0;
}