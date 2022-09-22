//
// Created by luc on 2021-04-17.
//

#ifndef SMALLTABLE_BORDERLESSTABLEVIEW_H
#define SMALLTABLE_BORDERLESSTABLEVIEW_H

#include "tableviewbase.h"
#include "tablemodel.h"

namespace smalltable {
    class BorderlessTableView : public TableviewBase {
    public:
        BorderlessTableView(const TableModel &model);

        std::string getTable() const override;
        void draw() const override;

    private:
        void calculateTableWidth() override;
        void drawLine() const override;
        void drawHeader() const override;
        void drawRows() const override;

        TableModel _model;
        std::size_t tableWidth{0};
    };
}// namespace smalltable

#endif//SMALLTABLE_BORDERLESSTABLEVIEW_H
