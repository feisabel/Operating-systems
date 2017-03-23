#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>     /* exit, EXIT_FAILURE */
#include <stdbool.h>    /* bool */
#include "pmap.h"
#include "pin.h"

using namespace std;

/**
* Constructor
*/
Pin::Pin(std::string name, Direction direction, Value value){
	if (pinMap.find(name) == pinMap.end()){
		cout << "Not a pin avalaible" << endl;
		EXIT_FAILURE;
	}else{
		name_pin = name;

		fstream fs;
		fs.open("/sys/class/gpio/export");
		string number = pinMap[name_pin].substr(4, pinMap[name_pin].size());
		fs << number;
		//TODO: check if "bash: echo: write error: Device or resource busy"
		fs.close();

		d = direction;
		v = value;
		Pin::setDirection(direction);
		Pin::setValue(value);
	}
}

void Pin::setDirection(Direction d){
	fstream fs;

	fs.open("/sys/class/gpio/"+ pinMap[name_pin] + "/direction");
	switch(d){
		case Direction::IN:
			fs << "in";
			break;
		case Direction::OUT:
			fs << "out";
			break;
	}
	fs.close();
}


void Pin::setOn(){
	fstream fs;

	fs.open("/sys/class/gpio/"+ pinMap[name_pin] + "/value");
	fs << "1";
	fs.close();
	v = Value::HIGH;
}

void Pin::setOff(){
	fstream fs;

	fs.open("/sys/class/gpio/"+ pinMap[name_pin] + "/value");
	fs << "0";
	fs.close();
	v = Value::LOW;
}

void Pin::changeValue(){
	switch(v){
		case Value::HIGH:
			setOff();
			break;
		case Value::LOW:
			setOn();
			break;
	}
}
void Pin::setValue(Value value){
	fstream fs;

	fs.open("/sys/class/gpio/"+ pinMap[name_pin] + "/value");
	switch(value){
		case Value::HIGH:
			fs << "1";
			v = value;
			break;
		case Value::LOW:
			fs << "0";
			v = value;
			break;
	}
	fs.close();
}
