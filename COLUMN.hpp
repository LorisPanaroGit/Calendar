//
// Created by loris on 09/02/2022.
//

#ifndef CALENDAR_COLUMN_HPP
#define CALENDAR_COLUMN_HPP
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <utility>
#include "COLUMNBASE.h"

template<typename T>
class COLUMN : public COLUMNBASE {
public:
    /*get functions*/
    int getDim() const {
        return _column.size();
    }

    std::string getElAtPos(int row) const {
        std::stringstream stream;
        std::string toRet;
        if(row < _column.size()){
            stream << _column[row];
            toRet = stream.str();
        }
        return toRet;
    }

    T& getElem(int row) const {
        return _column[row];
    }

    std::vector<T> getColumn() const {
        return _column;
    }

    std::vector<int> getElemWhere(std::string &strWhere, char c) const {
        std::vector<int> posToReturn;
        T where;
        std::stringstream stringVal;
        stringVal << strWhere;
        stringVal >> where;
        int i;
        for(i = 0; i < _column.size(); i++){
            if(c == 'g'){
                if(_column[i] > where){
                    posToReturn.push_back(i);
                }
            } else if(c == 'l'){
                if(_column[i] < where){
                    posToReturn.push_back(i);
                }
            } else if(c == 'e'){
                if(_column[i] == where){
                    posToReturn.push_back(i);
                }
            }
        }
        return posToReturn;
    }

    std::vector<int> getElemWhere(std::string &strWhere1, std::string &strWhere2, char c) const {
        std::vector<int> posToReturn;
        T where1, where2;
        std::stringstream stringVal1, stringVal2;
        stringVal1 << strWhere1;
        stringVal1 >> where1;
        stringVal2 << strWhere2;
        stringVal2 >> where2;
        int i;
        for(i = 0; i < _column.size(); i++){
            if(c == 'i'){
                if((_column[i] >= where1) && (_column[i] <= where2)){
                    posToReturn.push_back(i);
                }
            } else if(c == 'o'){
                if((_column[i] <= where1) && (_column[i] >= where2)){
                    posToReturn.push_back(i);
                }
            }
        }
        return posToReturn;
    }

    bool elementIsPresent(std::string &val) {
        bool found = false;
        T where;
        std::stringstream stringVal;
        stringVal << val;
        stringVal >> where;
        if(std::find(_column.begin(), _column.end(), where) != _column.end()){
            found = true;
        }
        return found;
    }

    std::string getType() const {
        return _columnType;
    }
    /*insert functions*/
    void updateAt(int row, T &other) {
        _column[row] = other;
    }

    void insertLast(T &other) {
        _column.push_back(other);
    }

    void insertFirst(T &other) {
        _column.insert(_column.begin(), other);
    }

    void loadElemLast(const std::string& toInsert) {
        std::stringstream stringVal;
        T templateVal;
        if(toInsert != "/"){
            stringVal << toInsert;
            stringVal >> templateVal;
            this->insertLast(templateVal);
        } else {
            this->insertLast(_defaultVal);
        }
    }

    void loadElementAt(const std::string& toInsert, int row) {
        std::stringstream stringVal;
        T templateVal;
        stringVal << toInsert;
        stringVal >> templateVal;
        _column[row] = templateVal;
    }

    void updateElem(const std::string &elem1, const std::string &elem2) {
        typename std::vector<T>::iterator pos;
        std::stringstream stringVal1, stringVal2;
        T valToFind, valToAdd;
        stringVal1 << elem1;
        stringVal1 >> valToFind;
        stringVal2 << elem2;
        stringVal2 >> valToAdd;
        pos = std::find(_column.begin(), _column.end(), valToFind);
        _column.erase(pos);
        _column.insert(pos, valToAdd);
    }

    void loadElemFirst(const std::string& toInsert) {
        std::stringstream stringVal;
        T templateVal;
        stringVal << toInsert;
        stringVal >> templateVal;
        this->insertFirst(templateVal);
    }

    void fillField(int maxSize) {
        /*maybe to do with reserve space, no need of default value*/
        while(_column.size() < maxSize){
            _column.push_back(_defaultVal);
        }
//        _column.resize(maxSize);
//        _column.reserve(maxSize);
    }
    /*print functions*/
    void printAt(int row) const {
        if(!_column.empty() && row < _column.size()){
            std::cout << _column[row];
        } /*else {
            std::cout << "/";
            //std::cout << _defaultVal;
        }*/
    }

    void printColumn() const {
        if(!_column.empty()){
            for(auto it : _column)
                std::cout << it << std::endl;
        }
    }
    /*delete functions*/
    void deleteFirst() {
        _column.erase(_column.begin());
    }

    void deleteAt(int row) {
        _column[row] = T();
    }

    void deleteElem(std::string &toDelete) {
        std::stringstream stringVal;
        T toDel;
        if(this->elementIsPresent(toDelete)){
            stringVal << toDelete;
            stringVal >> toDel;
            auto pos = std::find(_column.begin(), _column.end(), toDel);
            *pos = _defaultVal;
        } else {
            std::cout << "Elemento " << toDelete << " non presente" << std::endl;
        }
    }

    void deleteLast() {
        _column.pop_back();
    }

    void deleteColumn() {
        while(!(_column.empty()))
            _column.pop_back();
    }
    /*exchange functions*/
    void exchangeValues(int row1, int row2) {
        T tmp;
        if(row2 < _column.size()){
            tmp = _column[row1];
            _column[row1] = _column[row2];
            _column[row2] = tmp;
        }
    }

    bool greatherThan(int row1, int row2) const {
        bool gre = false;
        if(_column[row1] > _column[row2])
            gre = true;
        return gre;
    }

    bool isEmpty() const {
        bool toRet = false;
        if(_column.empty()){
            toRet = true;
        }
        return toRet;
    }

protected:
    std::vector<T> _column;
    T _defaultVal;
};


#endif //CALENDAR_COLUMN_HPP
