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

#ifndef IFBIND_BINDERS_H
#define IFBIND_BINDERS_H

#include <string>
#include <vector>

#include "binder.h"

class Binders {
public:
    Binders() = default;
    ~Binders();

    void addBinder(const std::string& iface1, const std::string& iface2);

    void start();
    void stop();
    void start(std::size_t idx);
    void stop(std::size_t idx);

    [[nodiscard]] inline std::string list() const {
        std::string lst;
        int i = 0;
        for(const auto& b : binders_)
            lst += std::to_string(++i) + ": " + b.binder() + "\n";
        return lst;
    }

private:
    std::vector<Binder> binders_{};
};


#endif //IFBIND_BINDERS_H
