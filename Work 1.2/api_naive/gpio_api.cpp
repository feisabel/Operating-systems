#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <cstring>
#include "gpio_api.h"

using namespace std;

void setOn(int gpio){
	string path = "/sys/class/gpio/gpio"+to_string(gpio)+"/value";
	ofstream fs(path);
	fs << "1";
	fs.close();
}

void setOff(int gpio){
	string path = "/sys/class/gpio/gpio"+to_string(gpio)+"/value";
	ofstream fs(path);
	fs << "0";
	fs.close();
}

void changeValue(int gpio){
	string path = "/sys/class/gpio/gpio"+to_string(gpio)+"/value";
	ifstream ifs(path);
	ofstream ofs(path);
	string line;
	getline(ifs, line);
	cout << line << "\n";
	if (strncmp(line.c_str(), "1", 1)){
	 	ofs << "1";
	}else{
		ofs << "0";
	}
	ifs.close();
	ofs.close();
}

int getValue(int gpio){
	string path = "/sys/class/gpio/gpio"+to_string(gpio)+"/value";
	ifstream fs(path);
	string line;
    getline(fs, line);
    fs.close();
    return stoi(line);
}

void setIn(int gpio){
	string path = "/sys/class/gpio/gpio"+to_string(gpio)+"/direction";
	ofstream fs(path);
	fs << "in";
	fs.close();
}

void setOut(int gpio){
	string path = "/sys/class/gpio/gpio"+to_string(gpio)+"/direction";
	ofstream fs(path);
	fs << "out";
	fs.close();
}

string getDirection(int gpio){
	string path = "/sys/class/gpio/gpio"+to_string(gpio)+"/direction";
	ifstream fs(path);
	string line;
    getline(fs, line);
    fs.close();
    return line;
}