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

#include <experimental/filesystem>
#include <algorithm>
#include <chrono>
#include <csignal>
#include <iostream>
#include <memory>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

// setcap cap_net_raw,cap_net_admin=eip xxxx

#include "binders.h"
#include "cxxopts.hpp"
#include "log.h"

using namespace std::chrono_literals;

constexpr auto VERSION = "1.1.0";

using Interfaces = std::vector<std::pair<std::string, std::string>>;

Binders binders;
static bool main_run = false;

void SignalHandler(const int signal) {
    auto logger = spdlog::get(LOG_NAME);
    logger->info("Caught signal ({}).", signal);
    binders.stop();
    logger->flush();
    main_run = false;
    exit(signal);
}

std::pair<std::string, std::string> split(const std::string &str) {
    if (std::count(str.begin(), str.end(), ':') != 1)
        throw std::runtime_error("Invalid interfaces bind, format is 'interface1:interface2': " + str);
    const auto pos = str.find(':');
    if (pos == std::string::npos) throw std::runtime_error("Require ':' to seperate interfaces");

    return {str.substr(0, pos), str.substr(pos + 1)};
}

Interfaces getInterfaces(const std::vector<std::string> &strInterfaces) {
    Interfaces interfaces;
    for (const auto &iface : strInterfaces) {
        interfaces.emplace_back(split(iface));
    }
    return interfaces;
}

void checkUniqueInterfaces(const Interfaces &interfaces) {
    std::set<std::string> unique;
    for (const auto &i : interfaces) {
        auto res = unique.insert(i.first);
        if (!res.second)
            throw std::runtime_error("Can only use an interface once: " + i.first);
        if(i.first != i.second) {
            res = unique.insert(i.second);
            if (!res.second)
                throw std::runtime_error("Can only use an interface once: " + i.second);
        }
    }
}

void printHelp() {
    std::cout << "\tstart" << "\t\tStart all binding interfaces" << std::endl;
    std::cout << "\tstop" << "\t\tStop all binding interfaces" << std::endl;
    std::cout << "\tconnect idx" << "\tStart specific binding at index" << std::endl;
    std::cout << "\tdisconnect idx" << "\tStop specific binding at index" << std::endl;
    std::cout << "\tlist" << "\t\tList binding interfaces and status" << std::endl;
    std::cout << "\thelp" << "\t\tDisplay this help message" << std::endl;
    std::cout << "\texit" << "\t\tExit program" << std::endl;
}

void printVersion() {
    std::cout << "ifbind - version " << VERSION << std::endl;
}

int main(int argc, char *argv[]) {
    cxxopts::Options options(argv[0], "ifbind - bind interfaces as a loop back\nMight require sudo access");
    options.positional_help("[args]").show_positional_help();

    std::vector<std::string> ifaces{};

    options.add_options()
            ("b,bind", "Bind 2 interfaces, format: 'iface1:iface2'; repeatable argument",
             cxxopts::value<std::vector<std::string>>())
            ("h,help", "Print this help message and exit")
            ("d,debug", "Set log level to DEBUG")
            ("i,interactive", "Specify whether to use a cli to change status",
             cxxopts::value<bool>()->default_value("false"))
            ("version", "Display application version and info and exit");

    auto results = options.parse(argc, argv);

    if (results.count("help")) {
        std::cout << options.help() << std::endl;
        exit(0);
    } else if (results["version"].as<bool>()) {
        printVersion();
        exit(0);
    }

    Interfaces interfaces{};
    if (results.count("bind")) {
        const auto binds = results["bind"].as<std::vector<std::string>>();
        interfaces = getInterfaces(binds);
        checkUniqueInterfaces(interfaces);
    } else {
        std::cout << options.help() << std::endl;
        exit(0);
    }

    bool interactive = results["interactive"].as<bool>();

    std::shared_ptr<spdlog::logger> logger = nullptr;
    auto sink = std::make_shared<spdlog::sinks::stderr_color_sink_mt>();
    if (interactive) {
        auto path = std::experimental::filesystem::current_path();
        path /= "ifbind.log";
        logger = spdlog::basic_logger_mt(LOG_NAME, path, true);
        spdlog::flush_every(1s);
        std::cout << "logfile: " << path << std::endl;
    } else {
        logger = std::make_shared<spdlog::logger>(LOG_NAME, sink);
        spdlog::register_logger(logger);
    }
    if (results["debug"].as<bool>())
        logger->set_level(spdlog::level::debug);

    logger->info("Interactive mode: {}", interactive);
    logger->info("Init...");

    signal(SIGINT, SignalHandler);
    signal(SIGTERM, SignalHandler);

    for (const auto &i : interfaces)
        binders.addBinder(i.first, i.second);

    if (interactive) {
        auto parse = [](const std::string &ln) {
            std::vector<std::string> sp{};
            std::size_t pos = 0;
            std::size_t pos2 = 0;
            do {
                pos2 = ln.find(' ', pos);
                sp.push_back(ln.substr(pos, pos2));
                pos = pos2 + 1;
            } while (pos2 != std::string::npos);
            return sp;
        };
        std::cout << "Interactive mode" << std::endl << "Type 'help' to list a set of commands\n\n";
        std::string input;
        do {
            std::cout << "> ";
            std::getline(std::cin, input);

            if (input == "start") {
                binders.start();
            } else if (input == "list") {
                std::cout << binders.list();
            } else if (input == "stop") {
                binders.stop();
            } else if (input.find("connect") != std::string::npos) {
                auto sp = parse(input);
                if (sp.empty() || sp.size() > 2) {
                    std::cout << "Invalid command '" << input << "'" << std::endl;
                } else {
                    if (sp.size() == 1) {
                        if (sp.front() == "connect")
                            binders.start();
                        else if (sp.front() == "disconnect")
                            binders.stop();
                        else
                            std::cout << "Invalid connection command '" << sp.front() << "'\n";
                    } else {
                        auto idx = std::stoi(sp.back()) - 1;
                        try {
                            if (sp.front() == "connect")
                                binders.start(idx);
                            else if (sp.front() == "disconnect")
                                binders.stop(idx);
                            else
                                std::cout << "Invalid connection command '" << sp.front() << "'\n";
                        } catch (const std::out_of_range &ex) {
                            logger->error("Invalid index {}", sp.back());
                            std::cout << "Invalid index " << sp.back() << std::endl;
                        }
                    }
                }
            } else if (input == "help") {
                printHelp();
            } else if (!input.empty() && input != "exit") {
                std::cout << "Invalid command '" << input << "'\n";
            }
            logger->flush();
        } while (input != "exit");
        binders.stop();
    } else {
        main_run = true;
        binders.start();
        while (main_run) {
          std::this_thread::sleep_for(1s);
        }
    }
    return 0;
}
