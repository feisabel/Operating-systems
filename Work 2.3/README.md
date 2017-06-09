# Work 2.3

This project consists of an urban train sinchronization program. The train system has seven train, each going in the rightwards direction 
on its rail. The rails have some parts in common with each other, where trains can only go through one at a time. Our program makes shure
no trains hit each other and no deadlocks occur, by synchronizing them using binary semaphores. Each part of the rails where two trains
can ride at the same time is a critical region, and by using a binary semaphore for each critical region we can assure no two trains will
ride at the same time on one rail, avoiding collisions.

The program is structured as a client-server system. The server is the train network and the client controls this network. The client can
turn trains on and off (either all at the same time or each train separately), as well as change the speed for any train. For this project,
the client was implemented on the BeagleBone Black, and we used GPIO buttons and potenciometer to choose between the options and control
the trains. The server is implemented on the computer using Qt. Client and server communicate via sockets.

//photo

### Set up environment
--- 
Install Qt on your computer.

On the BeagleBone Black:

Run `cd /sys/class/gpio`

Run `echo 115 > export`

Run `echo 20 > export`

Run `echo 7 > export`

Set up the beagleboneBlack:
 - P9_40 (AIN1) : Rotary Potentiometer
 - P9_27 (gpio_115) : Pushbutton (up)
 - P9_41 (gpio_20) : Pushbutton (down)
 - P9_42 (gpio_7) : Pushbutton (play)

Your Photoboard should be something like this:

//photo

## Build & development 
---

On the computer: 

Run Qt

Open the Train project on Qt

Run the program from Qt

---

On the BeagleBone Black:

Run `make`

Run `./client`
