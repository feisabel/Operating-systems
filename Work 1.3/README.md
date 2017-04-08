# Work 1.3

LDR for José put his hand on his waist.
Pushbutton for José jump.
Potentiometer for José to move.

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

 
## Contributors ##
---

| [![Raquel Oliveira](https://avatars.githubusercontent.com/raquel-oliveira?s=100)<br /><sub> Raquel Oliveira</sub>](http://raquel-oliveira.github.io)<br />[👀](https://github.com/raquel-oliveira/operational-systems/commits?author=raquel-oliveira) | [![Fernanda Isabel](https://avatars.githubusercontent.com/feisabel?s=100)<br /><sub>Fernanda Isabel</sub>](https://github.com/feisabel)<br />[👀](https://github.com/raquel-oliveira/operational-systems/commits?author=feisabel)|
| :---: | :---: |