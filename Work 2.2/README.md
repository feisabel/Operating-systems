# Work 2.2

This project consists of a visualization and monitoring system for processes' memory. It shows RAM, swapping and page faults for every process in execution and cache for the whole system every three seconds.

## Build & development 
---

Run `make`

Run `./run`

The program consists of a really long loop, in order to visualize memory updates for a long time. If you wish to stop it earlier, use `Ctrl+C`

## Stressing the system
---

To see swapping increasing, you can stress the system. While the program is running, in a new terminal tab:

Run `sudo sysctl vm.swappiness=100`

Run `stress --vm-bytes $(awk '/MemFree/{printf "%d\n", $2 * 1.1;}' < /proc/meminfo)k --vm-keep -m 1`

## Contributors ##
---

| [![Raquel Oliveira](https://avatars.githubusercontent.com/raquel-oliveira?s=100)<br /><sub> Raquel Oliveira</sub>](http://raquel-oliveira.github.io)<br />[👀](https://github.com/raquel-oliveira/operational-systems/commits?author=raquel-oliveira) | [![Fernanda Isabel](https://avatars.githubusercontent.com/feisabel?s=100)<br /><sub>Fernanda Isabel</sub>](https://github.com/feisabel)<br />[👀](https://github.com/raquel-oliveira/operational-systems/commits?author=feisabel)|
| :---: | :---: |
