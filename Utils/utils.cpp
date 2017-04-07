#include <fstream>
#include <stdio.h>
#include <errno.h>
#include <stdexcept>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sstream>

#define PATH_ADC "/sys/bus/iio/devices/iio:device0/in_voltage"

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
 
int readAnalog(int number){
   std::stringstream ss;
   ss << PATH_ADC << number << "_raw";
   std::fstream fs;
   fs.open(ss.str().c_str(), std::fstream::in);
   fs >> number;
   fs.close();
   return number;
}