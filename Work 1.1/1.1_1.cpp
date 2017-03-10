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
#include <string.h>
#include <sstream>

using namespace std;

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

int main(int argc, char *argv[]) {
	//setting a limit for the number of processes of the user
	long u = -1;
	struct rlimit r;
	r.rlim_cur = 100;
	r.rlim_max = 200;
	u = setrlimit(RLIMIT_NPROC, &r);

	string s = "ps -u | grep exec | wc -l";
	char * ch = new char [s.length()+1];
  	strcpy (ch, s.c_str());


	//saving the pid of the first process
	pid_t original = getpid();

	//if setting the limit was successful, allow the fork bomb
	if(u >= 0) {
		pid_t idProcesso = original;
		//fork bomb
		while(1) {
			idProcesso = fork();

			//if the result from fork was -1, print its error
			if(idProcesso < 0) {
				cout << "Error: " << strerror(errno) << endl;
			}
		}
	}
	//if setting the limit was unsuccessful, print error message
	else {
		printf("Could not set process limit.\n");
	}
	return 0;
}