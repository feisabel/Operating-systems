#include <fstream>
#include <stdio.h>
#include <errno.h>
#include <stdexcept>
#include <stdio.h>
#include <string.h>

std::string run(const char* command){
  int bufferSize = 128;
  char buff[bufferSize];
  std::string output = "";
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

char * stc(std::string a){
  char * b = new char [a.length()+1];
  strcpy (b, a.c_str());
  return b;
}