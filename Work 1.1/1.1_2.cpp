#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string.h> //stoi strcpy
#include <vector>
#include <iostream>
#include <sstream>  // istringstream

using namespace std;

struct Node {
	string name;
	long int pid;
	long int ppid;
	long int uid;
	vector<Node*> children;
};

string run(const char* command){
  int bufferSize = 128;
  char buff[bufferSize];
  string output = "";
  //cout << "command: " << command << endl;
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


Node* build_tree(long tgid) {
	Node* tree = new Node();
  char path[40], line[100], *p;
  FILE* statusf;

  snprintf(path, 40, "/proc/%ld/status", tgid);

  statusf = fopen(path, "r");
  printf("Open file do PID: %li\n", tgid);

  tree->pid = tgid;
  printf("Add PID: %li\n", tgid);
  while(fgets(line, 100, statusf)) {
      if(strncmp(line, "PPid:", 5) == 0){
        tree->ppid = atoi(line + 5);
        printf("Add PPID: %li of PID: %li\n", tree->ppid, tree->pid);
      }
      if(strncmp(line, "Uid:", 4) == 0){
        tree->uid = atoi(line + 4);  
        printf("Add UID: %li of PID: %li\n", tree->uid, tree->pid);
      }
      //break;
  }
  fclose(statusf);

  string listReturn = "pgrep " + to_string(tgid);
  char * command = new char [listReturn.length()+1];
  strcpy (command, listReturn.c_str());
  listReturn = run(command);
  istringstream f(listReturn);
  string l = "";    
  while (getline(f, l)) {
    int i = stoi(l);
    tree->children.push_back(build_tree(i));
      printf("Adicionei filho %li do pid %i\n",i , tgid );
  }
  printf("Adicionei os filho do pid %li\n", tgid );

  return tree;   
}


int main(void){
  int pid = 6;
  Node* tree = build_tree(pid);
  return 0;
}