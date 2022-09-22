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

#include "binder.h"

#include <tins/packet_sender.h>
#include <tins/pdu.h>
#include <tins/sniffer.h>
#include <tins/tins.h>
#include <cassert>
#include <mutex>
#include <string>
#include <thread>
#include <utility>

#include "log.h"

Binder::Binder(std::string iface1, std::string iface2)
    : iface1_(std::move(iface1)), iface2_(std::move(iface2)), logger(spdlog::get(LOG_NAME)) {
  stats.insert({iface1_, Stats{}});
  stats.insert({iface2_, Stats{}});
}

Binder::~Binder() { stop(); }

void Binder::start() {
  logger->info("Initializing bind {} <=> {}", iface1_, iface2_);
  if (run) {
    logger->info("Already listening");
    return;
  }
  assert(!iface1Handler.joinable());
  assert(!iface2Handler.joinable());
  run = true;
  iface1Handler = std::thread(&Binder::snifferThread, this, iface1_, iface2_);
  if (iface1_ != iface2_) iface2Handler = std::thread(&Binder::snifferThread, this, iface2_, iface1_);
}

void Binder::stop() {
  if (!run) return;
  logger->info("Stopping bind {} <=> {}", iface1_, iface2_);
  run = false;
  for (auto &sn : sniffers) sn->stop_sniff();

  if (iface1Handler.joinable()) iface1Handler.join();
  if (iface2Handler.joinable()) iface2Handler.join();
}

void Binder::snifferThread(const std::string &listenerIface, const std::string &senderIface) {
  logger->info("Starting bind thread {} -> {}", listenerIface, senderIface);
  Tins::SnifferConfiguration cfg;
  cfg.set_immediate_mode(true);
  std::scoped_lock<std::mutex> vec(pktMutex);
  auto sniffer = sniffers.emplace_back(std::make_shared<Tins::Sniffer>(listenerIface, cfg));
  pktMutex.unlock();
  Tins::PacketSender sender((Tins::NetworkInterface(senderIface)));
  sniffer->sniff_loop([this, &sender, &listenerIface, &senderIface](Tins::PDU &pdu) {
    const auto tmp = pdu.serialize();
    {
      std::scoped_lock<std::mutex> lock(pktMutex);
      if (lastPkt != tmp) {
        lastPkt = tmp;
        logger->debug("Sending packet {} -> {}", listenerIface, senderIface);
        sender.send(pdu);
        ++stats[listenerIface].received;
        ++stats[senderIface].sending;
      } else {
        lastPkt.clear();
      }
      return run.load();
    }
  });
  sniffer->stop_sniff();
  logger->info("Stopping bind {} -> {}", listenerIface, senderIface);
}
