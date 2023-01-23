//
// Created by loris on 09/02/2022.
//

#ifndef CALENDAR_TABLE_H
#define CALENDAR_TABLE_H
#include "Utils.hpp"
#include "COLUMNBASE.h"
#include "COLUMNINT.h"
#include "COLUMNFLOAT.h"
#include "COLUMNCHAR.h"
#include "COLUMNBOOL.h"
#include "COLUMNTEXT.h"
#include "COLUMNDATE.h"
#include "COLUMNTIME.h"
#include <iostream>
#include <map>
#include <memory>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>

/*
 * trasformare tutto in const reference, anche in column.hpp per velocità e memoria
 */

class TABLE {
public:
    TABLE() = default;
    /*insert functions*/
    void reserveSpace(std::string name, std::string type);
    void insertRow(std::vector<std::string> values);
    void fillFields();
    /*update functions*/
    void updateColName(std::string &nameCol, std::string &newCol);
    void updateColVals(std::string &nameCol, std::string &valToAdd);
    void updateColElem(std::string &nameCol, std::string &valToUpdate, std::string &valToAdd);
    void updateRowWhere(std::string &nameCol, std::string &val, std::vector<std::string> &rowVals, char c);
    void updateColumn(std::string &columnName);

    template<typename T> void updateAt(int row, std::string &name, T toUpdate) {
        if(!_columns.empty()){
            auto itr = _columns.find(name);
            if(itr != _columns.end()){
                auto col = dynamic_cast<COLUMN<T> *>(itr->second.get());
                if(col != nullptr){
                    col->updateAt(row, toUpdate);
                }
            }
        } else {
            std::cout << "Tabella vuota: nessun valore presente" << std::endl;
        }
    }

    void insertLast(std::string nameCol, std::string &toAdd);

    template<typename T> void insertLast(std::string nameCol, T &toAdd) {
        auto col = dynamic_cast<COLUMN<T> *>(_columns[nameCol].get());
        if(col != nullptr){
            col->insertLast(toAdd);
        }
        //this->fillFields();
    }

    void insertFirst(std::string nameCol, std::vector<std::string> &toAdd);

    template<typename T> void insertFirst(std::string nameCol, T &toAdd) {
        auto itr = _columns.find(nameCol); //find column
        if(itr != _columns.end()){
            auto col = dynamic_cast<COLUMN<T> *>(itr->second.get()); //get column
            if(col != nullptr){
                col->insertFirst(toAdd);
            }
        } else {
            std::cout << "Colonna " << nameCol << " inesistente" << std::endl;
        }
        this->fillFields();
    }
    /*get functions*/
    std::string getColType(std::string colName) const;
    int getColDim();
    int getTabDim();
    int getMaxColDim();
    bool colIsPresent(std::string colToFind);
    bool elemIsPresent(std::string &toFind, std::string &colName);
    /*delete functions*/
    void deleteTab();
    void deleteColumn(std::string &columnName);
    void deleteElement(std::string &columnName, std::string &toDelete);
    void deleteFirstRow();
    void deleteLastRow();
    void flushColumn(std::string colName);
    void deleteRowWhere(std::string colName, std::string &val, char c);
    void deleteRowWhere(std::string colName, std::string &val1, std::string &val2, char c);
    /*print functions*/
    void printCol(std::vector<std::string> columnNames);
    void printFields() const;
    void printTab() const;
    void printRowWhere(std::string colName, std::string &val, char c);
    void printRowWhere(std::string colName, std::string &val1, std::string &val2, char c);
    /*saving functions*/
    void saveTable(std::fstream& fp);
    void loadTable(std::fstream& fp, int nRow, int nCol);
    /*sorting function*/
    void sortBy(std::string colName, char comm);
    void swapRows(int row1, int row2);
    /*overload operator*/
    TABLE& operator=(const TABLE &toAssign);

    ~TABLE() = default;

private:
     std::map<std::string, std::shared_ptr<COLUMNBASE>> _columns;
};


#endif //CALENDAR_TABLE_H
