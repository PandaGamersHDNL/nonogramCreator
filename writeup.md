# docker

download docker from the docker website
using this for my linux enviroment, not only for ease of use in the future but also for learning experience.

create a Dockerfile file inside the working directory

add the linux dist of your choice that are supported by mxe

in our case we use ubuntu 22.10 which should be stable

- add "FROM ubuntu:22.10"

on the [mxe website](https://mxe.cc/#requirements-debian) we get the requirements and add to the docker file
 ``

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
``