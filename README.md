# Operational Systems
[![All Contributors](https://img.shields.io/badge/all_contributors-2-orange.svg?style=flat-square)](#contributors)

## Work 1.1 
---

This project was devided in two parts. 

Part 1 prevents a fork bomb, by setting a limit for the number of processes of a user and then running a fork bomb.

Part 2 creates a JSON file, "1.1_2.json", that works as the pstree for a given process. Also, it keeps showing the number of processes in the operating system and the number of processes by user every 10 seconds.

### Set up environment
--- 

### Build & development 
---

Run `cd Work\ 1.1/`

Run `make`

#### Test
---

##### To check part 1 of the work 1.1:

Run `./part1`

Use ctrl+C to stop execution as this program will never stop running on its own.

##### To check part 2 of the work 1.1:

Run `./part2` and enter the PID of the process

## Work 1.2:
---

This project simulates a traffic light for CPU usage. If the CPU usage x is:
- x <= 25% : green LED lights up
- 25% < x <= 50% : yellow LED lights up
- 50% < x <= 75% : red LED lights up
- 75% < x : all leds blink frenetically

The user can click a panic button to kill the process using most CPU.

### Set up environment
--- 
You need to install the stress and cpulimit packages on the BeagleBone Black:

Run `apt-get install stress`

Run `apt-get install cpulimit`

On the BeagleBone Black, put the red LED on P9_14 (gpio50), the yellow LED on P9_16 (gpio51), the green LED on P9_22 (gpio2) and the button on P9_30 (gpio112).

Run `cd Work\ 1.2/`

Run `make`

### Build & development 
---

Run as root:

Run `./measureCPU`

Use ctrl+C to stop execution as this program will never stop running on its own.

### Test
---

To stress the beaglebone with a limit of 35%:

Run `stress -c 1 & cpulimit -p $( pidof -o $! stress ) -l 35`

Use ctrl+C to stop the limit and let stress run wild.

Use the panic button to kill the process using most CPU (in this case, stress).

## Work 1.3
---

### Set up environment
--- 
Run `sudo apt-get update`

Run `sudo apt-get install bb-cape-overlays`

Open the file **/boot/uEnvtxt** and change:
*#cape_enable=bone_capemgr.enable_partno=* to *cape_enable=bone_capemgr.enable_partno=BB-ADC*
 
## Contributors ##
---

| [![Raquel Oliveira](https://avatars.githubusercontent.com/raquel-oliveira?s=100)<br /><sub> Raquel Oliveira</sub>](http://raquel-oliveira.github.io)<br />[👀](https://github.com/raquel-oliveira/operational-systems/commits?author=raquel-oliveira) 
| [![Fernanda Isabel](https://avatars.githubusercontent.com/feisabel?s=100)<br /><sub>Fernanda Isabel</sub>](https://github.com/feisabel)<br />[👀](https://github.com/raquel-oliveira/operational-systems/commits?author=feisabel)
| :---: | :---: |
