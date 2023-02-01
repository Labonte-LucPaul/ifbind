#!/bin/bash -e

mkdir -p deps
cd deps && git clone https://github.com/mfontanini/libtins.git
mkdir -p libtins/build
cd libtins/build && cmake .. -DLIBTINS_ENABLE_CXX11=1 -DLIBTINS_BUILD_SHARED=0
make
make install
ldconfig
cd ../../
git clone --single-branch --branch v1.x https://github.com/gabime/spdlog.git
mkdir -p spdlog/build
cd spdlog/build && cmake .. && make -j
