#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string.h> //stoi strcpy
#include <vector>
#include <iostream>
#include <sstream>  // istringstream
#include <unistd.h>
#include <fstream>
#include "json.h"

using namespace std;

struct Node {
	string name;
	long int pid;
	long int ppid;
	long int user_uid; //User that owns the process
  string user_name;
	vector<Node*> children;
};

Json::Value DFS(Node* u) {
  Json::Value nod;
  Json::Value children;
  nod["Name"] = Json::Value(u->name);
  nod["PID"] = Json::Value((unsigned int)u->pid);
  nod["PPID"] = Json::Value((unsigned int)u->ppid);
  nod["UID"] = Json::Value((unsigned int)u->user_uid);
  nod["UID Name"] = Json::Value(u->user_name);
  for(int i = 0; i < u->children.size(); i++) {
    Node* v = u->children[i];
      children.append(DFS(v));
  }
  nod["Children"] = children;
  return nod;
}

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

Node* build_tree(long tgid, Node * father) {
	Node* tree = new Node();
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

int main(void){
  static string file_name = "1.1_2.json";
  int pid;;
  cin >> pid;
  unsigned int microseconds = 10000000; //10 segundos
  Node* tree = build_tree(pid, NULL);

  Json::Value t = DFS(tree);

  Json::StyledWriter writer;
  ofstream outp(file_name);
  outp << writer.write(t);
  outp.close();

  cout << "====================Tree of process " << pid << " in the file: " << file_name << "===================" <<endl;
  char * c_nbProc = stc("ps -A --no-headers | wc -l");
  char * c_nbProcUser = stc("ps hax -o user | sort | uniq -c");

  while(true){
    cout << "====================Number of process in the OS: ====================\n" << run(c_nbProc) ;
    cout << "====================Number of process by user:=======================\n" <<run(c_nbProcUser) ;
    usleep(microseconds); 
  }
  return 0;
}