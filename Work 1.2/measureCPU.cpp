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
#include "api_gpio/pin.h"
#include "api_gpio/pmap.h"
#include <string.h>
//#include <stdexcept>

using namespace std;

string run(const char* command){
  int bufferSize = 128;
  char buff[bufferSize];
  string output = "";
  FILE *procStream = popen(command, "r");

  if(procStream == NULL){
    throw std::runtime_error("Could not get process output");
  }else{
    try{
      while (!feof(procStream)) {
          if (fgets(buff, bufferSize, procStream) != NULL)
              output += buff;
      }
    }catch(...){
      pclose(procStream);
      throw std::runtime_error("Error while getting output of process");
    }
    pclose(procStream);
    return output;
  }
}

char * stc(string a){
  char * b = new char [a.length()+1];
  strcpy (b, a.c_str());
  return b;
}

void killTopProcess() {
	string s = run(stc("ps aux | sort -nrk 3,3 | head -n 1"));
	stringstream ss(s);

	int pid; 
	string dummy;
	ss >> dummy >> pid;
	cout << "Kill the " << pid << endl;

	kill(pid, SIGKILL);
}

vector<long long> getCPUValues() {
	FILE* file;
	long long user, nice, sys, idle;
	file = fopen("/proc/stat", "r");
	fscanf(file, "cpu %lli %lli %lli %lli", &user, &nice, &sys, &idle);
	fclose(file);

	vector<long long> CPUValues;
	CPUValues.push_back(user);
	CPUValues.push_back(nice);
	CPUValues.push_back(sys);
	CPUValues.push_back(idle);
	return CPUValues;
}

double calculatePercentage(vector<long long> first, vector<long long> second) {
	long long total;
	double usage;
	total = (second[0] - first[0]) + (second[1] - first[1]) + (second[2] - first[2]);
	usage = total;
	total += (second[3] - first[3]);
	usage /= total;
	usage *= 100;
	return usage;
}

int main() {
	init();

	vector<long long> first, second;
	double usage;

	Pin red ("P9_14", Direction::OUT, Value::LOW);
	Pin yellow ("P9_16", Direction::OUT, Value::LOW);
	Pin green ("P9_22", Direction::OUT, Value::LOW);
	Pin btn ("P9_30", Direction::IN, Value::LOW);

	while(1){
		first = getCPUValues();
		usleep(500000);
		second = getCPUValues();

		usage = calculatePercentage(first, second);
		cout << "Usage: " << usage << endl;
		if(usage <= 25.0) {
			green.setOn();
			yellow.setOff();
			red.setOff();
		} else if (usage <= 50.0) {
			green.setOff();
			yellow.setOn();
			red.setOff();
		} else if (usage <= 75.0) {
			green.setOff();
			yellow.setOff();
			red.setOn();
		} else {
			for(int i = 0; i < 5; i++) {
				green.setOn();
				yellow.setOff();
				red.setOff();
				usleep(100000);
				green.setOff();
				yellow.setOn();
				red.setOff();
				usleep(100000);
				green.setOff();
				yellow.setOff();
				red.setOn();
				usleep(100000);
			}
			red.setOff();
		}
		if (btn.getValue() == 1){
			killTopProcess();
			cout << "Process killed" << endl;
			usleep(1000000);
		}
	}
}