# Operational Systems
[![All Contributors](https://img.shields.io/badge/all_contributors-2-orange.svg?style=flat-square)](#contributors)

## Work 1.1 ( Prevent Fork Bomb )
---

This project was devided in two parts. 

Part 1 prevents a fork bomb, by setting a limit for the number of processes of a user and then running a fork bomb.

Part 2 creates a JSON file, "1.1_2.json", that works as the pstree for a given process. Also, it keeps showing the number of processes in the operating system and the number of processes by user every 10 seconds.

To check it out : 

Run `cd Work\ 1.1/`

## Work 1.2 ( CPU Usage )
---

This project simulates a traffic light for CPU usage. If the CPU usage x is:
- x <= 25% : green LED lights up
- 25% < x <= 50% : yellow LED lights up
- 50% < x <= 75% : red LED lights up
- 75% < x : all leds blink frenetically

The user can click a panic button to kill the process using most CPU.

To check it out:

Run `cd Work\ 1.2/`

## Work 1.3 ( Threads and GPIO )
---

This project runs a game to be played with the BeagleBone Black as a joystick. We use the potenciometer for horizonal movements, the LDR for jumping and the button for a special feature. Reading of the control information is done by threads (one for each).

To check it out:

Run `cd Work\ 1.3/`

## Work 2.2 ( Memory management )
---
This project consists of a visualization and monitoring system for processes' memory. It shows RAM, swapping and page faults for every process in execution and cache for the whole system every three seconds. 

To check it out:

Run `cd Work\ 2.2/`
 
## Contributors ##
---

| [![Raquel Oliveira](https://avatars.githubusercontent.com/raquel-oliveira?s=100)<br /><sub> Raquel Oliveira</sub>](http://raquel-oliveira.github.io)<br />[👀](https://github.com/raquel-oliveira/operational-systems/commits?author=raquel-oliveira) | [![Fernanda Isabel](https://avatars.githubusercontent.com/feisabel?s=100)<br /><sub>Fernanda Isabel</sub>](https://github.com/feisabel)<br />[👀](https://github.com/raquel-oliveira/operational-systems/commits?author=feisabel)|
| :---: | :---: |
