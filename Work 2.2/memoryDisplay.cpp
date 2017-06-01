#include <unistd.h>
#include <cstdio>
#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <ulimit.h>
#include <signal.h>
#include <errno.h>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include "../Utils/utils.h"
#include <string.h>
#include <iomanip> //setw

using namespace std;

int main() {
	vector<int> pid;
    vector<float> mem;
    vector<int> min_flt;
    vector<int> maj_flt;
    int p, mif, maf; 
    float m;
	string s = run(stc("ps -eo pid,pmem,min_flt,maj_flt --no-header > infos.txt"));
  	ifstream myfile ("infos.txt");
  	if (myfile.is_open()) {
    	while ( getline (myfile,s) ) {
      		stringstream ss(s);
      		ss >> p >> m >> mif >> maf;
    		pid.push_back(p);
    		mem.push_back(m);
    		min_flt.push_back(mif);
    		maj_flt.push_back(maf);
    	}
   		myfile.close();
  	}
  	int dummy, cache, swapi, swapo;
 	s = run(stc("vmstat > infos.txt"));
  myfile.open("infos.txt", ifstream::in);
  	if (myfile.is_open()) {
  		getline (myfile,s);
  		getline (myfile,s);
  		getline (myfile,s);
      	stringstream ss(s);
      	ss >> dummy; 
        ss >> dummy;
        ss >> dummy; 
        ss >> dummy; 
        ss >> dummy; 
        ss >> cache; 
        ss >> swapi; 
        ss >> swapo;
   		myfile.close();
  	}
  	cout << "Total cache: " << cache << endl;
  	cout << "Swap-in: " << swapi << endl;
  	cout << "Swap-out: " << swapo << endl << endl;
  	cout << "   PID              %MEMORY       MINOR PAGE FAULTS      MAJOR PAGE FAULTS" << endl;
  	for(int i = 0; i < pid.size(); i++) {
  		cout << setw(7) << pid[i] << "           " << setw(7) << mem[i] << "            " << setw(7) << min_flt[i] << "            " << setw(7) << maj_flt[i] << endl;
  	}
	return 0;
}