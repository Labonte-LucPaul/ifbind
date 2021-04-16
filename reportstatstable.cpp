//
// Created by luc on 2021-04-16.
//

#include "reportstatstable.h"

#include "tableview.h"

ReportStatsTable::ReportStatsTable() {
  model.setHeader({"Interface", "RX", "TX"});
}
void ReportStatsTable::setModell(const smalltable::DataModel_t &dataModel) {
  model.setDataModel(dataModel);
}
void ReportStatsTable::printTable() const {
  smalltable::TableView view{model};
  view.draw();
}
