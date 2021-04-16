//
// Created by luc on 2021-04-15.
//

#ifndef SMALLTABLE_TABLEVIEW_H
#define SMALLTABLE_TABLEVIEW_H

#include "tablemodel.h"
#include "model_index.h"

#include <string>
#include <sstream>

namespace smalltable {
    class TableView {
    public:
        explicit TableView(const TableModel &model);

        [[nodiscard]] std::string getTable() const;
        void draw() const;

    private:
        void calculateTableWidth();

        void drawLine() const;
        void drawHeader() const;
        void drawRows() const;

        TableModel _model;
        std::size_t tableWidth{0};
    };
}// namespace smalltable

#endif//SMALLTABLE_TABLEVIEW_H
