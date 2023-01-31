FROM ubuntu:22.04

RUN apt-get update && apt-get --fix-broken install -y --no-install-recommends software-properties-common \
    git cmake automake libc++-dev \
      libgtest-dev \
      libgflags-dev \
        libpcap-dev \
    libboost-all-dev \
      libboost-atomic-dev \
      libboost-thread-dev \
      libboost-system-dev \
      libboost-date-time-dev \
      libboost-regex-dev \
        ccache \
        clang make

## CLANG 10 - disabled, gRPC hangs while establishing a connection
#RUN apt-get install -y gnupg2 &&  apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 15CF4D18AF4F7421 \
#  && apt install -y --no-install-recommends software-properties-common \
#  && add-apt-repository "deb http://apt.llvm.org/bionic/ llvm-toolchain-bionic-10 main" \
#  && apt install -y --no-install-recommends clang-10 lldb-10 lld-10 \
#  && ln -s /usr/bin/clang-10 /usr/bin/clang \
#  && ln -s /usr/bin/clang++-10 /usr/bin/clang++

WORKDIR /build
COPY install_deps.sh /build
RUN rm -rf /var/lib/apt/lists/*

RUN ./install_deps.sh

COPY build.sh /root/ \
