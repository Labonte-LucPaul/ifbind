//
// Created by luc on 2021-04-14.
//

#ifndef SMALLTABLE_MODEL_INDEX_H
#define SMALLTABLE_MODEL_INDEX_H

#include <string>

namespace smalltable {
    struct ModelIndex {
        int row{-1};
        int column{-1};
        std::string data;
        inline bool isValid() const { return !(row == -1 || column == -1); }
    };
}// namespace smalltable
#endif//SMALLTABLE_MODEL_INDEX_H
