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

	return tree;    
}


int main(void){
  int pid = 6;
  Node* tree = build_tree(pid);
  return 0;
}