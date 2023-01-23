//
// Created by loris on 01/03/2022.
//

#ifndef CALENDAR_DATABASE_H
#define CALENDAR_DATABASE_H
#include <iostream>
#include <memory>
#include <algorithm>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <cstdio>
#include "Utils.hpp"
#include "TABLE.h"

class DATABASE {
public:
    DATABASE() = default;
    /*insert functions*/
    void reserveSpace(std::string tabName, const TABLE& toInsert);
    void insertLast(std::string tabName, std::string nameCol, std::string valToInsert);
    void insertRow(std::string tabName, std::vector<std::string> values);
    /*get functions*/
    TABLE& getTab(std::string nameTab);
    int getTabSize(std::string nameTab);
    bool tabIsPresent(std::string &tabToFind);
    bool colIsPresent(std::string &nameTab, std::string &colToFind);
    bool elemIsPresent(std::string &tabToFind, std::string &colToFind, std::string &valToFind);
    /*delete functions*/
    void clearDatabase();
    void deleteTab(std::string name);
    void deleteColumn(std::string nameTab, std::string nameCol);
    void deleteElement(std::string &nameTab, std::string &nameCol, std::string &toDelete);
    void deleteRowWhereElementIs(std::string nameTab, std::string nameCol, std::string valToFind, char c);
    void deleteRowWhereElementIs(std::string nameTab, std::string nameCol, std::string valToFind1, std::string valToFind2, char c);
    void flushColumnWhereTabIs(std::string &nameTab, std::string nameCol);
    void deleteFirstTab();
    void deleteLastTab();

    template<typename T> void deleteTabWhere(std::string tabName, std::string colName, T& where, char c) const{

    }
    /*print functions*/
    void printDatabase() const;
    void printTabs(std::vector<std::string> tabNames);
    void printTab(std::string tabName);
    void printFields(std::string tabName);
    void printColumns(std::string tabName, std::vector<std::string> columns);
    void printTabWhereColumnIs(std::vector<std::string> colToFind);
    void printTabWhereElementIs(std::string nameTab, std::string nameCol, std::string valToFind, char c);
    void printTabWhereElementIs(std::string nameTab, std::string nameCol, std::string valToFind1, std::string valToFind2, char c);
    /*update functions*/
    void updateTab(std::string &nameTab, std::string &newName);
    void updateColName(std::string &nameTab, std::string &nameCol, std::string &newName);
    void updateColumnVals(std::string &nameTab, std::string &nameCol, std::string &newVal);
    void updateColumnElem(std::string &nameTab, std::string &nameCol, std::string &oldVal, std::string &newVal);
    void updateTabRowWhere(std::string &nameTab, std::string &nameCol, std::string &valToFind, std::vector<std::string> &rowVals, char c);
    void fillFieldsOf(std::string &nameTab);
    /*saving functions*/
    std::string getNameFromFile(std::fstream &fp);
    std::vector<std::string> getNamesFromFile(std::fstream &fp);
    void saveTab(std::fstream& fp, std::string &tabName);
    void saveTabs(std::fstream &fp, std::fstream &fp_tmp, std::vector<std::string> &tabNames);
    void saveDatabase(std::fstream &fp, std::fstream &fp_tmp);
    void loadTab(std::fstream& fp, std::string tabName);
    void loadTabs(std::fstream &fp, std::vector<std::string> tabNames);
    void loadDatabase(std::fstream &fp);
    void skipTab(std::fstream& fp);
    /*sorting functions*/
    void sortBy(std::string tabName, std::string colName, char comm);
    ~DATABASE() {}

private:
    std::map<std::string, TABLE> _tables;

};


#endif //CALENDAR_DATABASE_H
