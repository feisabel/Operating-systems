# Operational Systems
[![All Contributors](https://img.shields.io/badge/all_contributors-2-orange.svg?style=flat-square)](#contributors)

## Work 1.1 

### Set up environment
--- 

### Build & development 
---

Run `cd Work\ 1.1/`

Run `make`

#### Test
##### To check part 1 of the work 1.1:

Run `./part1`

Remember to use ctrl+C to stop execution as this program will never stop running on its own.
##### To check part 2 of the work 1.1:

Run `./part2` and enter the PID of the process

## Work 1.2:

### Set up environment
--- 
You need to install the stress and cpulimit packages on the beaglebone:

Run `apt-get install stress`
Run `apt-get install cpulimit`


### Build & development 
---
Run `cd Work\ 1.2/`

Run `make`

Run `./measureCPU`

Remember to use ctrl+C to stop execution as this program will never stop running on its own.

### Test

To stress the beaglebone with a limit of 35%:
Run `stress -c 1 & cpulimit -p $( pidof -o $! stress ) -l 35`

Use ctrl+C to stop the limit and let stress run wild.

Use the panic button to kill the process using most CPU (in this case, stress).
 
 
## Contributors ##
---

| [![Raquel Oliveira](https://avatars.githubusercontent.com/raquel-oliveira?s=100)<br /><sub> Raquel Oliveira</sub>](http://raquel-oliveira.github.io)<br />[👀](https://github.com/raquel-oliveira/operational-systems/commits?author=raquel-oliveira) 
| [![Fernanda Isabel](https://avatars.githubusercontent.com/feisabel?s=100)<br /><sub>Fernanda Isabel</sub>](https://github.com/feisabel)<br />[👀](https://github.com/raquel-oliveira/operational-systems/commits?author=feisabel)
| :---: | :---: |
