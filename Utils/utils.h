#ifndef _UTILS_
#define _UTILS_
#include <string>
#include <vector>

std::string run(const char* command);

char * stc(std::string a);

int readAnalog(int number);

struct Sys{
	int cached; //proc/meminfo in Kb
	int swapCached; //proc/meminfo in kb
	int swapTotal; //proc/meminfo in Kb
	int swapFree; //proc/meminfo in Kb
	int cache; //vmstat
	int swapIn; //vmstat
	int swapOut; //vmstat
};

struct Process {
	std::string name;
	long int pid;
	long int ppid;
	long int user_uid; //User that owns the process
  std::string user_name;
	float mem;
	int min_flt;
	int maj_flt;
	int swap;
	std::vector<Process*> children;
};

#endif
