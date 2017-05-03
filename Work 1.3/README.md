# Work 1.3

This project runs a game to be played with the BeagleBone Black as a joystick. The "game" is very simple and consists only of moving a stick figure, named José. The game could be improved so that José has to avoid shots, in order to have a real objective and allow winning/losing. Because the goal of the project was to implement threads and making a joystick with the BBB, we didn't worry too much about the game. We use the potenciometer for horizonal movements, the LDR for jumping and the button for a special feature (José puts his hand on his waist). Reading of the control information is done by threads (one for each), with the potenciometer thread having the highest priority and the button thread having the lowest priority.

### Set up environment
--- 
Run `sudo apt-get update`

Run `sudo apt-get install bb-cape-overlays`

Open the file **/boot/uEnvtxt** and change:
*#cape_enable=bone_capemgr.enable_partno=* to *cape_enable=bone_capemgr.enable_partno=BB-ADC*

Set up the beagleboneBlack:
 - P9_33 (AIN4) : Photocell (Light Dependent Resistor)
 - P9_40 (AIN1) : Rotary Potentiometer
 - P9_27 (gpio_115) : Pushbutton

Your Photoboard should be something like this:

![alt tag](Protoboard_bb.png?raw=true "Configuration")


## Build & development 
---

Run `make`

Run as root:

`echo 115 > /sys/class/gpio/export`

`./jose`

In order to quit the game, press 'q' then Enter.


## Contributors ##
---

| [![Raquel Oliveira](https://avatars.githubusercontent.com/raquel-oliveira?s=100)<br /><sub> Raquel Oliveira</sub>](http://raquel-oliveira.github.io)<br />[👀](https://github.com/raquel-oliveira/operational-systems/commits?author=raquel-oliveira) | [![Fernanda Isabel](https://avatars.githubusercontent.com/feisabel?s=100)<br /><sub>Fernanda Isabel</sub>](https://github.com/feisabel)<br />[👀](https://github.com/raquel-oliveira/operational-systems/commits?author=feisabel)|
| :---: | :---: |
