all: program1 program2

program1: ../Utils/api_gpio/pmap.cpp ../Utils/api_gpio/pin.cpp ../Utils/utils.cpp client.cpp
	g++ -std=c++11 ../Utils/api_gpio/pmap.cpp ../Utils/api_gpio/pin.cpp ../Utils/utils.cpp client.cpp -o client -lpthread

program2: server.cpp
	g++ -std=c++11 -o server server.cpp -lpthread
