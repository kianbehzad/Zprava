# Zprava - INSTALL

## Overview

We developed Zprava on Mac OS. (Mac OS 10.12+ tested and is recommended). It is  important that the graphics card driver is installed properly. Zprava will compile and run in both 32 and 64 bits Linux and Mac OS.

Zprava is written in C++, in order to compile it, you will need a working toolchain and a c++ compiler.

###incomplete

### Linux/Unix Installation

Pre-requirements:

Zprava still doesnt have a official domain and host so to run the code with the server capabilities do as follow:
If you dont have node.js installed on your system please install it from the following link:
- [Install Node.js](https://nodejs.org/en/download/)

Next run the server from your terminal:

```bash
$ git clone https://github.com/streetbz/Zprava.git 
$ cd ZPserver
$ nodejs ZPserver.js
```

Now, all you need to do is to compile and run the client code.
In order to do so open the provided ".pro" file in the "ZPclient/Zprava" directory with qtcreator IDE and then run the code from the menubar.



### Mac OS X Installation

Pre-requirements:

Zprava still doesnt have a official domain and host so to run the code with the server capabilities do as follow:
If you dont have node.js installed on your system please install it from the following link:
- [Install Node.js](https://nodejs.org/en/download/)

Next run the server from your terminal:

```bash
$ git clone https://github.com/streetbz/Zprava.git 
$ cd ZPserver
$ node ZPserver.js
```

Now, all you need to do is to compile and run the client code.
In order to do so open the provided ".pro" file in the "ZPclient/Zprava" directory with qtcreator IDE and then run the code from the menubar.


