//
// Created by luc on 2021-04-16.
//

#include "reportstatstable.h"
#include <string>

#include "tableview.h"

ReportStatsTable::ReportStatsTable() : logger(spdlog::get(LOG_NAME)) {
  model.setHeader({"Interface", "RX", "TX"});
}

void ReportStatsTable::setModel(const smalltable::DataModel_t &dataModel) {
  try {
    model.setDataModel(dataModel);
  } catch(const std::range_error& ex) {
    std::string msg = "Could not set stats data model: ";
    msg += ex.what();
    logger->error(msg);
    throw std::range_error(msg);
  }
}

void ReportStatsTable::printTable() const {
  smalltable::TableView view{model};
  view.draw();
}
