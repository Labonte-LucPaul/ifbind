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

cmake_minimum_required(VERSION 3.10.2)
project(ifbind CXX)


set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Xclang -fconcepts-ts")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(spdlog REQUIRED)
find_package(Threads REQUIRED)
find_package(libtins REQUIRED)

include_directories(deps/smalltable/include)

set(PROJ_LIB
        spdlog::spdlog
        tins
        Threads::Threads
        stdc++fs
        "${PROJECT_SOURCE_DIR}/deps/smalltable/libsmalltable_lib.a"
)

add_executable(ifbind main.cpp binder.cpp binder.h binders.cpp cxxopts.hpp log.h reportstatstable.cpp)
target_link_libraries(ifbind PUBLIC ${PROJ_LIB})