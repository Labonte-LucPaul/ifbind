//
// Created by luc on 2021-04-16.
//

#ifndef IFBIND_REPORTSTATSTABLE_H
#define IFBIND_REPORTSTATSTABLE_H

#include <spdlog/spdlog.h>
#include <memory>
#include "tablemodel.h"

#include "../log.h"

class ReportStatsTable {
 public:
  ReportStatsTable();

  void setModel(const smalltable::DataModel_t &dataModel);
  void printTable() const;

 private:
  std::shared_ptr<spdlog::logger> logger = nullptr;
  smalltable::TableModel model;
};

#endif  // IFBIND_REPORTSTATSTABLE_H
