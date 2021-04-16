//
// Created by luc on 2021-04-14.
//

#ifndef SMALLTABLE_ABSTRACTMODEL_H
#define SMALLTABLE_ABSTRACTMODEL_H

#include "model_index.h"

namespace smalltable {
    class AbstractModel {
    public:
        AbstractModel() = default;
        virtual ~AbstractModel() = default;

        virtual int rowCount() const = 0;
        virtual int columnCount() const = 0;
        virtual std::string data(const ModelIndex &index) const = 0;
        virtual std::string getHeader(int column) const = 0;
        virtual std::size_t columnWidth(int column) const = 0;
        virtual bool hasIndex(int row, int column) const = 0;
    };
}// namespace smalltable
#endif//SMALLTABLE_ABSTRACTMODEL_H
