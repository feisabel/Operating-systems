all: program1

program1: ../Utils/api_gpio/pmap.cpp ../Utils/api_gpio/pin.cpp ../Utils/utils.cpp client.cpp
	g++ -std=c++11 ../Utils/api_gpio/pmap.cpp ../Utils/api_gpio/pin.cpp ../Utils/utils.cpp client.cpp -o client -lpthread
