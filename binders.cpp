//  ifbind - Bind two interfaces as a bridge to simulate loopback connection.
//
//  Copyright (C) 2020  Luc Paul Labonté
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Affero General Public License as published
//  by the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Affero General Public License for more details.
//
//  You should have received a copy of the GNU Affero General Public License
//  along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
//  Contact: labonte.lucpaul+ifbind(at)gmail(dot)com
//  project: https://github.com/Labonte-LucPaul/ifbind

#include "binders.h"
#include <string>
#include <vector>

#include "binder.h"

Binders::~Binders() {
    stop();
}

void Binders::addBinder(const std::string &iface1, const std::string& iface2) {
    binders_.emplace_back(iface1, iface2);
}

void Binders::start() {
    for(auto& b : binders_)
        b.start();
}

void Binders::stop() {
    for(auto& b : binders_)
        b.stop();
}

void Binders::start(std::size_t idx) {
    binders_.at(idx).start();
}

void Binders::stop(std::size_t idx) {
    binders_.at(idx).stop();
}
