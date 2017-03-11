/*
This program is about preventing a fork bomb. 
We set a limit for the number of processes of a user and then run a fork bomb.
The fork call will create new processes as long as the total number of processes of a user hasn't reached the established limit.
After that, the fork call will not be able to create new processes, return -1. The error message is outed by the program.
In order to see how many processes were created by the program, type "ps -u | grep executable_name | wc -l" at the terminal while the program is running.
This program never ends; although the fork bomb is prevented, the while(true) loop still runs forever. In order to stop execution, use ctrl+C.
*/


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