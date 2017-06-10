# Work 2.3
<!--https://github.com/raquel-oliveira/operational-systems/files/1066093/Lab_Trabalho_2.3.pdf-->

This project consists of an urban train synchronization program. The train system has seven train, each going in the rightwards direction
on its rail. The rails have some parts in common with each other, where trains can only go through one at a time. Our program makes sure
no trains hit each other and no deadlocks occur, by synchronizing them using binary semaphores. Each part of the rails where two trains
can ride at the same time is a critical region, and by using a binary semaphore for each critical region we can assure no two trains will
ride at the same time on one rail, avoiding collisions.

The program is structured as a client-server system. The server is the train network and the client controls this network. The client can
turn trains on and off (either all at the same time or each train separately), as well as change the speed for any train. For this project,
the client was implemented on the BeagleBone Black, and we used GPIO buttons and potentiometer to choose between the options and control
the trains. The server is implemented on the computer using Qt. Client and server communicate via sockets.

## Set up environment
---

### Client:
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

![alt tag](Documents/Client_bb.png?raw=true "Configuration")
<!-- ![Protoboard] (https://user-images.githubusercontent.com/6775247/27006026-0ec42d36-4e01-11e7-8485-f85b6d473d5c.png)-->

![Set up](https://user-images.githubusercontent.com/6775247/27006613-c24713f2-4e0e-11e7-9772-98333537258b.gif)

### Server:

[Install QT](https://www.qt.io/download/) if you have not installed yet.


## Build & development
---

On the computer:

Run Qt

Open the Train project on Qt (`Train/TrabalhoTrem.pro`)

Run the program from Qt

---

On the BeagleBone Black:

Run `make`

Run `./client`

![Build](https://user-images.githubusercontent.com/6775247/27006615-caad989a-4e0e-11e7-94cf-cc90df36eb48.gif)

## Demo
---
![Demo](https://user-images.githubusercontent.com/6775247/27006617-ceaea24a-4e0e-11e7-8903-050e2a6a4586.gif)
