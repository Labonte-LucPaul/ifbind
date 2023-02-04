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

#ifndef IFBIND_BINDER_H
#define IFBIND_BINDER_H

#include <atomic>
#include <memory>
#include <mutex>
#include <string>
#include <thread>

#include <tins/packet_sender.h>
#include <tins/pdu.h>
#include <tins/sniffer.h>
#include <tins/tins.h>

#include <spdlog/spdlog.h>

#include "../log.h"

struct Stats {
  std::uint64_t received{0};
  std::uint64_t sending{0};
};

class Binder {
 public:
  Binder() = delete;
  Binder(const Binder& b) : logger(spdlog::get(LOG_NAME)) {
    iface1_ = b.iface1_;
    iface2_ = b.iface2_;
    stats[iface1_] = {};
    stats[iface2_] = {};
  }

  Binder(std::string iface1, std::string iface2);
  ~Binder();

  void start();
  void stop();

  inline std::string binder() const {
    std::string status = run ? "connected" : "disconnected";
    return iface1_ + " <=> " + iface2_ + " " + status;
  }

  inline const std::map<std::string, Stats>& interfacesStats() const {
    std::scoped_lock<std::mutex> lock(pktMutex);
    return stats;
  }

  inline void clearStats() {
    std::scoped_lock<std::mutex> lock(pktMutex);
    for (auto& [iface, stat] : stats) stats[iface] = {};
  }

 private:
  void snifferThread(const std::string& listenerIface, const std::string& senderIface);

  std::string iface1_{};
  std::string iface2_{};
  std::shared_ptr<spdlog::logger> logger = nullptr;

  std::atomic<bool> run{false};
  std::thread iface1Handler;

  std::thread iface2Handler;
  mutable std::mutex pktMutex;

  std::vector<std::shared_ptr<Tins::Sniffer>> sniffers{};
  std::map<std::string, Stats> stats;
};

#endif  // IFBIND_BINDER_H
