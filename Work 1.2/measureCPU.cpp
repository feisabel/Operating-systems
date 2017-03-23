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

using namespace std;

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
	vector<long long> first, second;
	double usage;

	Pin red ("P9_14", Direction::OUT, Value::LOW);
	Pin yellow ("P9_16", Direction::OUT, Value::LOW);
	Pin green ("P9_22", Direction::OUT, Value::LOW);

	for(int i = 0; i < 20; i++) {
		first = getCPUValues();
		usleep(5000000);
		second = getCPUValues();

		usage = calculatePercentage(first, second);
		if(usage <= 25.0) {
			green.setOn();
			yellow.setOff();
			red.setOff();
		}
		else if (usage <= 50.0) {
			green.setOff();
			yellow.setOn();
			red.setOff();
		}
		else if (usage <= 75.0) {
			green.setOff();
			yellow.setOff();
			red.setOn();
		}
		else {
			green.changeValue();
			yellow.changeValue();
			red.changeValue();
			usleep(500000);
		}
	}

}