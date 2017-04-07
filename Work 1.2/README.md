# CPU Usage

This project simulates a traffic light for CPU usage. If the CPU usage x is:
- x <= 25% : green LED lights up
- 25% < x <= 50% : yellow LED lights up
- 50% < x <= 75% : red LED lights up
- 75% < x : all leds blink frenetically

The user can click a panic button to kill the process using most CPU.

## Set up environment
--- 
You need to install the stress and cpulimit packages on the BeagleBone Black:

Run `apt-get install stress`

Run `apt-get install cpulimit`

Set up the beagleboneBlack:
 - P9_14 (gpio50) : red LED
 - P9_16 (gpio51) : yellow LED
 - P9_22 (gpio2) : green LED
 - P9_30 (gpio112) : Pushbutton

Your Photoboard should be something like this:

![alt tag](Protoboard_bb.png?raw=true "Configuration")

Run `make`

## Build & development 
---

Run as root:

`./measureCPU`

Use ctrl+C to stop execution as this program will never stop running on its own.

## Test
---

To stress the beaglebone with a limit of 35%:

Run `stress -c 1 & cpulimit -p $( pidof -o $! stress ) -l 35`

Use ctrl+C to stop the limit and let stress run wild.

Use the panic button to kill the process using most CPU (in this case, stress).

# Contributors #
---

| [![Raquel Oliveira](https://avatars.githubusercontent.com/raquel-oliveira?s=100)<br /><sub> Raquel Oliveira</sub>](http://raquel-oliveira.github.io)<br />[👀](https://github.com/raquel-oliveira/operational-systems/commits?author=raquel-oliveira) | [![Fernanda Isabel](https://avatars.githubusercontent.com/feisabel?s=100)<br /><sub>Fernanda Isabel</sub>](https://github.com/feisabel)<br />[👀](https://github.com/raquel-oliveira/operational-systems/commits?author=feisabel)|
| :---: | :---: |

