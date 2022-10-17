FROM ubuntu:22.04

RUN apt-get -y update
RUN apt-get upgrade

RUN apt-get install -y --no-install-recommends --fix-missing\
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
RUN mkdir build
WORKDIR ./build
RUN git clone https://github.com/mxe/mxe.git
COPY . .
# TODO add this so error will be gone in next step
RUN ln -s /usr/bin/python3 /usr/bin/python
# RUN cd ./mxe && make gcc MXE_USE_CCACHE=
RUN cd ./mxe && make download-qtbase MXE_USE_CCACHE=
# added jobs hopefully goes faster
RUN cd mxe && sudo make qtbase MXE_TARGETS="x86_64-w64-mingw32.static" MXE_USE_CCACHE= --jobs 8

# path to mxe
ENV PATH /mxe/usr/bin:$PATH
RUN export PATH=/mnt/c/Users/panda/Documents/nonogramCreator/mxe/usr/bin:$PATH
RUN /mxe/usr/x86_64-w64-mingw32.static/qt5/bin/qmake
RUN make
