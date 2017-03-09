#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string.h> //stoi strcpy
#include <vector>
#include <iostream>
#include <sstream>  // istringstream
#include <unistd.h>

using namespace std;

struct Node {
	string name;
	long int pid;
	long int ppid;
	long int user_uid; //User that owns the process
  string user_name;
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

char * stc(string a){
  char * b = new char [a.length()+1];
  strcpy (b, a.c_str());
  return b;
}

Node* build_tree(long tgid) {
	Node* tree = new Node();
  char path[40], line[100], *p;
  FILE* statusf;

  snprintf(path, 40, "/proc/%ld/status", tgid);

  statusf = fopen(path, "r");
  //printf("Open file do PID: %li\n", tgid);

  if(!statusf){
    fprintf(stderr, "Problem trying to open\n");
    exit(-1); 
  }

  tree->pid = tgid;
  while(fgets(line, 100, statusf)) {
      if(strncmp(line, "PPid:", 5) == 0){
        tree->ppid = atoi(line + 5);
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
  cout << "Add process: " << tgid << "(" << tree->name << ")" << "\nPPid: " << tree->ppid << "\nUid: " << tree->user_uid << "(" << tree->user_name << ")\n\n\n";
  fclose(statusf);

  char * command = stc("pgrep " + to_string(tgid));
  string listReturn = run(command);
  istringstream f(listReturn);
  string l = "";    
  while (getline(f, l)) {
    int i = stoi(l);
    tree->children.push_back(build_tree(i));
      //printf("Adicionei filho %i do pid %li\n",i , tgid );
  }
  //printf("Adicionei os filho do pid %li\n", tgid );

  return tree;   
}

int main(void){
  int pid;;
  cin >> pid;
  unsigned int microseconds = 10000000; //10 segundos
  Node* tree = build_tree(pid);

  char * c_nbProc = stc("ps -A --no-headers | wc -l");
  char * c_nbProcUser = stc("ps hax -o user | sort | uniq -c");

  while(true){
    cout << "Number of process in the OS: \n" << run(c_nbProc) ;
    cout << "Number of process by user:\n" <<run(c_nbProcUser) ;
    usleep(microseconds); 
  }
  return 0;
}