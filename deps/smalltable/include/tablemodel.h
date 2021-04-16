//
// Created by luc on 2021-04-14.
//

#ifndef SMALLTABLE_TABLEMODEL_H
#define SMALLTABLE_TABLEMODEL_H

#include <string>
#include <vector>

#include "abstract_model.h"

namespace smalltable {
    using Header_t = std::vector<std::string>;
    using DataModel_t = std::vector<std::vector<std::string>>;

    class TableModel : public AbstractModel {
    public:
        TableModel();
        int rowCount() const override;
        int columnCount() const override;
        std::string data(const ModelIndex &index) const override;
        std::string getHeader(int column) const override;
        std::size_t columnWidth(int column) const override;
        bool hasIndex(int row, int column) const override;

        void setDataModel(const DataModel_t &dataModel);
        void setHeader(const Header_t &header);

    private:
        DataModel_t _dataModel;
        Header_t _header;
    };
}// namespace smalltable
#endif//SMALLTABLE_TABLEMODEL_H
