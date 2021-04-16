//
// Created by luc on 2021-04-16.
//

#ifndef IFBIND_REPORTSTATSTABLE_H
#define IFBIND_REPORTSTATSTABLE_H

#include "tablemodel.h"

class ReportStatsTable {
public:
  ReportStatsTable();

  void setModell(const smalltable::DataModel_t &dataModel);
  void printTable() const;

private:
  smalltable::TableModel model;
};

#endif // IFBIND_REPORTSTATSTABLE_H
