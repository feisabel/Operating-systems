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
#include <map>

using namespace std;
static string file_name = "infos.txt";

struct Process {
	long int pid;
	float mem;
	int min_flt;
	int maj_flt;
};

int main() {
	map<long int, Process> processes;
  int p, mif, maf;
  float m;
	string s = run(stc("ps -eo pid,pmem,min_flt,maj_flt --no-header > infos.txt"));
  ifstream myfile (file_name);
  if (myfile.is_open()) {
		while ( getline (myfile,s) ) {
			stringstream ss(s);
  		ss >> p >> m >> mif >> maf;
			Process aux;
			aux.pid = p;
			aux.mem = m;
			aux.min_flt = mif;
			aux.maj_flt = maf;
			processes[p] = aux;
    }
   	myfile.close();
  }
  int dummy, cache, swapi, swapo;
 	s = run(stc("vmstat > infos.txt"));
  myfile.open(file_name, ifstream::in);
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
		map<long int,Process>::iterator it = processes.begin();
		for (it=processes.begin(); it!=processes.end(); ++it)
		cout << setw(7) << it->first << "           " << setw(7) << it->second.mem << "            " << setw(7) << it->second.min_flt << "            " << setw(7) << it->second.maj_flt << endl;

	return 0;
}
