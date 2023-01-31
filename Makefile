#!make

#  ifbind - Bind two interfaces as a bridge to simulate loopback connection.
#
#  Copyright (C) 2020  Luc Paul Labonté
#
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU Affero General Public License as published
#  by the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU Affero General Public License for more details.
#
#  You should have received a copy of the GNU Affero General Public License
#  along with this program.  If not, see <https:#www.gnu.org/licenses/>.
#
#  Contact: labonte.lucpaul+ifbind(at)gmail(dot)com
#  project: https:#github.com/Labonte-LucPaul/ifbind

.DEFAULT_GOAL := help

ifeq ($(MAKE_J),)
MAKE_J := -j$(shell nproc)
endif

.PHONY: build
build:	libraries  ## Build the release version of ifbind

.PHONY: build-only
build-only:  ## only build ifbind, don't install dependencies
	@mkdir -p ./build
	@cd ./build
	@cd ./build && cmake .. -DCMAKE_BUILD_TYPE=Release
	@cd ./build && make

.PHONY: libraries
libraries: clean  ## Fetch & compile and install dependencies
	@mkdir -p deps
	@cd deps && git clone https://github.com/mfontanini/libtins.git
	@mkdir -p deps/libtins/build
	@cd deps/libtins/build && cmake .. -DLIBTINS_ENABLE_CXX11=1 -DLIBTINS_BUILD_SHARED=0
	@cd deps/libtins/build && make
	@cd deps/libtins/build && sudo make install
	@sudo ldconfig
	@cd deps && git clone --single-branch --branch v1.x git@github.com:gabime/spdlog.git
	@mkdir -p deps/spdlog/build
	@cd deps/spdlog/build && cmake .. && make -j

.PHONY: apt-deps
apt-deps:  ## install dependencies with apt, require sudo
	@sudo apt update && sudo apt install libpcap-dev libssl-dev cmake

.PHONY: install
install:  ## Install ifbind to /usr/local/bin, require sudo
	@cp build/ifbind /usr/local/bin

.PHONY: clean
clean:  ## Clean binaries generated
	@rm -rf build
	@rm -rf deps/libtins
	@rm -rf deps/spdlog

.PHONY: release  ## Build a release binary
release: .docker-image-builder
		./build.sh

.docker-image-builder:
	@docker build --rm --progress auto . -t ifbind:builder

.PHONY: help
help:
	@grep -E '^[a-zA-Z0-9_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sed 's/Makefile://' | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-15s\033[0m %s\n", $$1, $$2}'
