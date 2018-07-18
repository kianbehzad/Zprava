# Zprava - INSTALL

## Overview

We developed Zprava on Mac OS. (Mac OS 10.12+ tested and is recommended). It is  important that the graphics card driver is installed properly. Zprava will compile and run in both 32 and 64 bits Linux, Mac OS and Windows 10.

Zprava is written in C++, in order to compile it, you will need a working toolchain, a c++ compiler and Qt framework installed.

###incomplete

### Linux/Unix and MacOS X Installation

Pre-requirements:

Zprava have a official domain and host on [Zprava](https://zprava.ir/admin/). but to run the code with the server capabilities on a local machine do as follow:
If you dont have Django installed on your system please install it from the following link:
- [Install Django](https://docs.djangoproject.com/en/2.0/topics/install/)
or just run the following command in the command line:
```bash
$ pip install Django==2.0.5
```

Next run the server from your terminal:

```bash
$ git clone https://github.com/kianbehzad/Zprava-server.git 
$ cd Zprava-server/Zprava
$ python3 manage.py makemigrations signup
$ python3 manage.py makemigrations chat
$ python3 manage.py migrate
$ python3 manage.py runserver
```

Now, all you need to do is to compile and run the client code.
In order to do so open the provided ".pro" file in the "ZPclient/Zprava" directory with qtcreator IDE and then run the code from the menubar, or you can run it with qmake.



### Windows Installation

Pre-requirements:

Zprava have a official domain and host on [Zprava](https://zprava.ir/admin/). but to run the code with the server capabilities on a local machine do as follow:
If you dont have Django installed on your system please install it from the following link:
- [Install Django](https://docs.djangoproject.com/en/2.0/howto/windows/)

Next run the server from your terminal:

```bash
$ git clone https://github.com/kianbehzad/Zprava-server.git 
$ cd Zprava-server/Zprava
$ python3 manage.py makemigrations signup
$ python3 manage.py makemigrations chat
$ python3 manage.py migrate
$ python3 manage.py runserver
```

Now, all you need to do is to compile and run the client code.
In order to do so open the provided ".pro" file in the "ZPclient/Zprava" directory with qtcreator IDE and then run the code from the menubar, or you can run it with qmake.


