#include <unistd.h>
#include <cstdio>
#include <stdio.h> //strlen
#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <ulimit.h>
#include <signal.h>
#include <errno.h>
#include <algorithm>
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
map<long int, Process> processes;
Sys systemInfo;

bool compareByMemory(const Process &a, const Process &b) {
	return a.mem < b.mem;
}

Process* build_tree(long tgid, Process * father) {
	Process* tree = new Process();
  char path[40], line[100], *p;
  FILE* statusf;

  snprintf(path, 40, "/proc/%ld/status", tgid);

  statusf = fopen(path, "r");
  if(!statusf){
    //fprintf(stderr, "Problem trying to open\n");
  }
  else{
    tree->pid = tgid;
		//tree->swap = -1;// initialize to check after; TODO: check if -1 is impossible
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
					//clean of "\n":
					int len = tree->name.size();
					if(len> 0 && tree->name[len-1] == '\n')
						tree->name[--len] = '\0';
        }
				if(strncmp(line, "VmSwap:", 7) == 0){
//					cout << "tem para pid "<< tree->pid << endl;
          tree->swap =  stoi(string(line).substr(8, strlen(line)));
        }
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
	string output = run(stc("ps -eo pid,pmem,min_flt,maj_flt --no-header > infos.txt"));
	ifstream myfile (file_name);
	if (myfile.is_open()) {
		while ( getline (myfile, output) ) {
			Process aux;
			stringstream ss(output);
  		ss >> aux.pid >> aux.mem >> aux.min_flt  >> aux.maj_flt;
			processes[aux.pid] = aux;
			//initialize in case the is no swap:
			//processes[aux.pid].swap = 0;
    }
   	myfile.close();
	}
}

void DFS(Process* u) {
	processes[u->pid].name = u->name;
	processes[u->pid].ppid = u->ppid;
	processes[u->pid].user_uid = u->user_uid;
	processes[u->pid].user_name = u->user_name;
	//if(u->swap > 0 && u->swap == 0){
		processes[u->pid].swap = u->swap;
	//} else{
	//	processes[u->pid].swap = 0;
	//}
  for(int i = 0; i < u->children.size(); i++) {
    Process* v = u->children[i];
		processes[u->pid].children.push_back(v);
		DFS(v);
  }
}

void updateInfoSystem(){
	int aux;
	/*string s = run(stc("vmstat > infos.txt"));
	ifstream myfile (file_name);
	if (myfile.is_open()) {
		getline (myfile,s); //header
		getline (myfile,s); //header
		getline (myfile,s); //values
		stringstream ss(s);
		ss >> aux; //r
		ss >> aux; //b
		ss >> aux; //swpd
		ss >> aux; //free
		ss >> aux; //buff
		ss >> systemInfo.cache; //cache
		ss >> systemInfo.swapIn; //si
		ss >> systemInfo.swapOut; //so
		myfile.close();
	}*/
	char path[40], line[100], *p;
	snprintf(path, 40, "/proc/meminfo");
	FILE* statusf = fopen(path, "r");;
	if(!statusf){
	    fprintf(stderr, "Problem trying to check /proc/meminfo\n");
	}
	else{
		while(fgets(line, 100, statusf)) {
			if(strncmp(line, "Cached:", 7) == 0){
				systemInfo.cached = stoi(string(line).substr(8, strlen(line)));
			}
			if(strncmp(line, "SwapCached:", 11) == 0){
				systemInfo.swapCached = stoi(string(line).substr(12, strlen(line)));
			}
			if(strncmp(line, "SwapTotal:", 10) == 0){
				systemInfo.swapTotal = stoi(string(line).substr(11, strlen(line)));
			}
			if(strncmp(line, "SwapFree:", 9) == 0){
				systemInfo.swapFree = stoi(string(line).substr(10, strlen(line)));
			}
		}
	}
}

void print() {
  processes.clear();
  // get pid,pmem,min_flt,maj_flt by ps
  getPs();
  //get ppid, uid, name, vmswap by /proc/status
  Process* tree = build_tree(1, NULL); //atualiza os swap caso tenham
  DFS(tree);

	//Take all values
	vector<Process> v;
	for(map<long int,Process>::iterator it = processes.begin(); it != processes.end(); ++it) {
  	v.push_back(it->second);
	}
	//Ordenate by memory
	sort(v.begin(), v.end(), compareByMemory);

  //show info
  system("clear");
  cout << setw(7) << "PID"<< "   |"  << setw(20) << "NAME" << "   |"  << setw(7) << "%MEMORY" << "   |" << setw(20) << "MINOR PAGE FAULTS"<< "   |" << setw(20)<<"MAJOR PAGE FAULTS"<< "   |" << setw(7) <<"SWAP" << endl;
  for (int it =0 ; it < v.size(); it++){
    cout << setw(7) << v[it].pid << "   |" << setw(20) << v[it].name << "   |" << setw(7) << v[it].mem << "   |" << setw(20) << v[it].min_flt << "   |" << setw(20) << v[it].maj_flt << "   |" << setw(7) << v[it].swap<<endl;
	}
  updateInfoSystem();
  cout << "\nVALORES DO SISTEMA:\n";
  cout << setw(25) << "meminfo" << setw(25) << "|" << endl;
  //cout << setw(15) << "vmstat" << setw(15) << "|" << endl;
  //meminfo
  cout << setw(7) << "Cached" << setw(8) << "|";
  cout << setw(7) << "SwapCached" << "    |";
  cout << setw(5) << "SwapTotal" << setw(5) << "|";
  cout << setw(5) << "SwapFree"<< setw(5) << "|";
  cout << setw(5) << "SwapUsed"<< setw(5) << "|" << endl;
  //vmstat
 /* cout << setw(5) << "Cache"<< setw(6) << "|";
  cout << setw(5) << "SwapIn"<< setw(5) << "|";
  cout << setw(5) << "SwapOut"<< setw(5) << "|"<< endl;*/
  //values meminfo
  cout << setw(7) << systemInfo.cached << setw(8) << "|";
  cout << setw(7) << systemInfo.swapCached << setw(8) << "|";
  cout << setw(7) << systemInfo.swapTotal << setw(7) << "    |";
  cout << setw(7) << systemInfo.swapFree << setw(6) << "|";
  cout << setw(7) << systemInfo.swapTotal - systemInfo.swapFree << setw(6) << "|" << endl;

  //values vmstat
  /*cout << setw(5) << systemInfo.cache << setw(5) << "|";
  cout << setw(5) << systemInfo.swapIn << setw(6) << "|";
  cout << setw(5) << systemInfo.swapOut << setw(5) << "|"<< endl;*/
}

int main() {

  for(int i = 0; i < 100; i++) {
    print();
    usleep(3000000);
  }

	return 0;
}
