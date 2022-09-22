//
// Created by luc on 2021-04-17.
//

#ifndef SMALLTABLE_TABLEVIEWBASE_H
#define SMALLTABLE_TABLEVIEWBASE_H

#include <string>

namespace smalltable {
    class TableviewBase {
    public:
        ~TableviewBase() = default;

        virtual std::string getTable() const = 0;
        virtual void draw() const = 0;

    protected:
        virtual void calculateTableWidth() = 0;
        virtual void drawLine() const = 0;
        virtual void drawHeader() const = 0;
        virtual void drawRows() const = 0;
    };
}// namespace smalltable
#endif//SMALLTABLE_TABLEVIEWBASE_H
