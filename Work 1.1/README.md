# Prevent Fork Bomb

This project was devided in two parts. 

Part 1 prevents a fork bomb, by setting a limit for the number of processes of a user and then running a fork bomb.

Part 2 creates a JSON file, "1.1_2.json", that works as the pstree for a given process. Also, it keeps showing the number of processes in the operating system and the number of processes by user every 10 seconds.

## Build & development 
---

Run `make`


## Test
---

#### To check part 1 of the work 1.1:

Run `./part1`

Use ctrl+C to stop execution as this program will never stop running on its own.

#### To check part 2 of the work 1.1:

Run `./part2` and enter the PID of the process

# Contributors
---

| [![Raquel Oliveira](https://avatars.githubusercontent.com/raquel-oliveira?s=100)<br /><sub> Raquel Oliveira</sub>](http://raquel-oliveira.github.io)<br />[👀](https://github.com/raquel-oliveira/operational-systems/commits?author=raquel-oliveira) | [![Fernanda Isabel](https://avatars.githubusercontent.com/feisabel?s=100)<br /><sub>Fernanda Isabel</sub>](https://github.com/feisabel)<br />[👀](https://github.com/raquel-oliveira/operational-systems/commits?author=feisabel)|
| :---: | :---: |

