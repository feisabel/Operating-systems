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
	string name;
	long int pid;
	long int ppid;
	long int user_uid; //User that owns the process
  string user_name;
	float mem;
	int min_flt;
	int maj_flt;
	string swap;
	vector<Process*> children;
};

map<long int, Process> processes;

Process* build_tree(long tgid, Process * father) {
	Process* tree = new Process();
  char path[40], line[100], *p;
  FILE* statusf;

  snprintf(path, 40, "/proc/%ld/status", tgid);

  statusf = fopen(path, "r");
  //printf("Open file do PID: %li\n", tgid);

  if(!statusf){
    //fprintf(stderr, "Problem trying to open\n");
  }
  else{
    tree->pid = tgid;
    while(fgets(line, 100, statusf)) {
        if(strncmp(line, "PPid:", 5) == 0){
          tree->ppid = atoi(line + 5);
          if (father != NULL)
            father->children.push_back(tree);
        }
        if(strncmp(line, "Uid:", 4) == 0){
          //line => Uid :Real, effective, saved set, and  file system UIDs
          tree->user_uid = atoi(line + 4);  //get real
          string getUidComplet = run(stc("getent passwd " + to_string(tree->user_uid)));
          tree->user_name = getUidComplet.substr(0, getUidComplet.find(":"));
        }
        if(strncmp(line, "Name:", 5) == 0){
          tree->name =  string(line).substr(6, strlen(line));
        }
				if(strncmp(line, "VmSwap:", 7) == 0){
          tree->swap =  string(line).substr(8, strlen(line));
        }
        //break;
    }
   // cout << "Add process: " << tgid << "(" << tree->name << ")" << "\nPPid: " << tree->ppid << "\nUid: " << tree->user_uid << "(" << tree->user_name << ")\n\n\n";
    fclose(statusf);

    char * command = stc("pgrep -P" + to_string(tgid));
    string listReturn = run(command);
    istringstream f(listReturn);
    string l = "";
    while (getline(f, l)) {
      int i = stoi(l);
      build_tree(i, tree);
    }
  }
  return tree;
}

/*Update global variable "processes" with values:
* mem : Memory usage of process
* min_flt : Minor pages fault
* maj_flt : Major pages fault
*
* @param file: name of the file
*/
void getPs(){
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
}

void DFS(Process* u) {
	processes[u->pid].name = u->name;
	processes[u->pid].ppid = u->ppid;
	processes[u->pid].user_uid = u->user_uid;
	processes[u->pid].user_name = u->user_name;
	processes[u->pid].swap = u->swap;
  for(int i = 0; i < u->children.size(); i++) {
    Process* v = u->children[i];
			DFS(v);
  }
}

void printInfoSystem(){
	int dummy, cache, swapi, swapo;
	string s = run(stc("vmstat > infos.txt"));
	ifstream myfile (file_name);
	myfile.open(file_name, ifstream::in);
		if (myfile.is_open()) {
			getline (myfile,s); //header
			getline (myfile,s); //header
			getline (myfile,s); //values
			stringstream ss(s);
			ss >> dummy; //r
			ss >> dummy; //b
			ss >> dummy; //swpd
			ss >> dummy; //free
			ss >> dummy; //buff
			ss >> cache; //cache
			ss >> swapi; //si
			ss >> swapo; //so
			myfile.close();
		}
		cout << "Total cache: " << cache << endl;
  	cout << "Swap-in: " << swapi << endl;
  	cout << "Swap-out: " << swapo << endl << endl;
}

int main() {
  int p, mif, maf;
  float m;
	getPs();
	Process* tree = build_tree(1, NULL);
	//DFS(tree);
	cout << "   PID              %MEMORY       MINOR PAGE FAULTS      MAJOR PAGE FAULTS      SWAP" << endl;
	map<long int,Process>::iterator it = processes.begin();
	for (it=processes.begin(); it!=processes.end(); ++it)
		cout << setw(7) << it->first << "           " << setw(7) << it->second.mem << "            " << setw(7) << it->second.min_flt << "            " << setw(7) << it->second.maj_flt << "            " << setw(7) << it->second.swap <<endl;

	return 0;
}
