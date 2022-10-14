# WSL

I use wsl to run the cross compilation that way i don't have to rebuild everything, it should also be faster than docker or vm cus it has a better connection to the resources available (cpu, internet connection,etc)


create a Dockerfile file inside the working directory

add the linux dist of your choice that are supported by mxe

in our case we use ubuntu 22.10 which should be stable

- add "FROM ubuntu:22.10"

on the [mxe website](https://mxe.cc/#requirements-debian) we get the requirements and add to the docker file
 ```

apt-get install \
    autoconf \
    automake \
    autopoint \
    bash \
    bison \
    bzip2 \
    flex \
    g++ \
    g++-multilib \
    gettext \
    git \
    gperf \
    intltool \
    libc6-dev-i386 \
    libgdk-pixbuf2.0-dev \
    libltdl-dev \
    libssl-dev \
    libtool-bin \
    libxml-parser-perl \
    lzip \
    make \
    openssl \
    p7zip-full \
    patch \
    perl \
    python3 \
    python3-mako \
    ruby \
    sed \
    unzip \
    wget \
    xz-utils
```

next we clone the mxe git repository

```Dockerfile
git clone https://github.com/mxe/mxe.git
```
TODO copy (docker)

then we go in the mxe directory and build the qtbase package
we add the --jobs parameter to do this in paralel

```Dockerfile
cd ./mxe && make download-qtbase --jobs=2
```
then we run the command down below to build the compiler for me i had to run it in sudo or cmake wouldn't compile and make would throw an error
```Dockerfile
sudo make qbase MXE_TARGETS='x86_64-w64-mingw32.static'
```
we run this command so the enviroment for compiling is there
 export PATH=/mnt/c/Users/panda/Documents/nonogramCreator/mxe/usr/bin:$PATH

 then we run qmake  mxe/usr/x86_64-w64-mingw32.static/qt5/bin/qmake

 then we run make