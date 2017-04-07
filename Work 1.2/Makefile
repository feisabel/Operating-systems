all: program1

program1: ../Utils/api_gpio/pmap.cpp ../Utils/api_gpio/pin.cpp ../Utils/utils.cpp measureCPU.cpp
	g++ -std=c++11 ../Utils/api_gpio/pmap.cpp ../Utils/api_gpio/pin.cpp ../Utils/utils.cpp measureCPU.cpp -o measureCPU