all: program1 program2

jsoncpp.o: jsoncpp.cpp
	g++ -std=c++11 jsoncpp.cpp -c
program1: 1.1_1.cpp
	g++ -std=c++11 1.1_1.cpp -o part1
program2: ../Utils/utils.cpp 1.1_2.cpp jsoncpp.o
	g++ -std=c++11 ../Utils/utils.cpp 1.1_2.cpp -o part2 jsoncpp.o
