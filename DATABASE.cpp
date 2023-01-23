//
// Created by loris on 01/03/2022.
//

#include "DATABASE.h"

void DATABASE::reserveSpace(std::string tabName, const TABLE& toInsert) {
    _tables.insert({tabName, toInsert});
    //_tables[tabName].fillFields();
}

void DATABASE::insertLast(std::string tabName, std::string nameCol, std::string valToInsert) {
    _tables[tabName].insertLast(nameCol, valToInsert);
}

void DATABASE::insertRow(std::string tabName, std::vector<std::string> values) {
    _tables[tabName].insertRow(values);
}

TABLE &DATABASE::getTab(std::string nameTab) {
        return _tables[nameTab];
}

int DATABASE::getTabSize(std::string nameTab) {
    return _tables[nameTab].getTabDim();
}

bool DATABASE::tabIsPresent(std::string &tabToFind) {
    bool found = false;
    if(_tables.find(tabToFind) != _tables.end()){
        found = true;
    }
    return found;
}

bool DATABASE::colIsPresent(std::string &nameTab, std::string &colToFind) {
    bool found = false;
    if(_tables[nameTab].colIsPresent(colToFind)){
        found = true;
    }
    return found;
}

bool DATABASE::elemIsPresent(std::string &tabToFind, std::string &colToFind, std::string &valToFind) {
    bool found = false;
    if(_tables[tabToFind].elemIsPresent(valToFind, colToFind)){
        found = true;
    }
    return found;
}

void DATABASE::clearDatabase() {
    _tables.clear();
}

void DATABASE::deleteTab(std::string name) {
        _tables.erase(name);
}

void DATABASE::deleteColumn(std::string nameTab, std::string nameCol) {
    _tables[nameTab].deleteColumn(nameCol);
}

void DATABASE::deleteElement(std::string &nameTab, std::string &nameCol, std::string &toDelete) {
    _tables[nameTab].deleteElement(nameCol, toDelete);
}

void DATABASE::deleteRowWhereElementIs(std::string nameTab, std::string nameCol, std::string valToFind, char c) {
    _tables[nameTab].deleteRowWhere(nameCol, valToFind, c);
}

void DATABASE::deleteRowWhereElementIs(std::string nameTab, std::string nameCol, std::string valToFind1, std::string valToFind2, char c) {
    _tables[nameTab].deleteRowWhere(nameCol, valToFind1, valToFind2, c);
}

void DATABASE::flushColumnWhereTabIs(std::string &nameTab, std::string nameCol) {
    if(_tables[nameTab].colIsPresent(nameCol)){
        _tables[nameTab].flushColumn(nameCol);
    }
}

void DATABASE::deleteFirstTab() {
    _tables.erase(_tables.begin());
}

void DATABASE::deleteLastTab() {
    _tables.erase(_tables.end());
}

void DATABASE::printDatabase() const {
    if(!_tables.empty()){
        for(auto &itr : _tables){
            std::cout << "Nome_tabella: " << itr.first << std::endl;
            itr.second.printTab();
        }
    } else {
        std::cout << "Database vuoto: nessuna tabella presente" << std::endl;
    }
}

void DATABASE::printTabs(std::vector<std::string> tabNames) {
    for(auto &name : tabNames){
        this->printTab(name);
    }
    std::cout << std::endl;
}

void DATABASE::printTab(std::string tabName) {
    auto itr = _tables.find(tabName);
    if(itr != _tables.end()){
        std::cout << "Nome_tabella: " << itr->first << std::endl;
        itr->second.printTab();
    } else {
        std::cout << "Tabella " << tabName << " inesistente" << std::endl;
    }
}

void DATABASE::printFields(std::string tabName) {
    _tables[tabName].printFields();
}

void DATABASE::printColumns(std::string tabName, std::vector<std::string> columns) {
    if(_tables.find(tabName) != _tables.end()){
        _tables[tabName].printCol(columns);
    } else {
        std::cout << "Tabella " << tabName << " inesistente" << std::endl;
    }
}

void DATABASE::printTabWhereColumnIs(std::vector<std::string> colToFind) {
    std::vector<std::string> tabNames;
    for(auto &tabs : _tables){
        for(auto &namesToFind : colToFind){
            if(tabs.second.colIsPresent(namesToFind)){
                if(std::find(tabNames.begin(), tabNames.end(), tabs.first) == tabNames.end()){
                    tabNames.push_back(tabs.first);
                }
            }
        }
    }
    for(auto &toPrint : tabNames){
        this->printTab(toPrint);
    }
}

void DATABASE::printTabWhereElementIs(std::string nameTab, std::string nameCol, std::string valToFind, char c) {
    if(_tables.find(nameTab) != _tables.end()){
        _tables[nameTab].printRowWhere(nameCol, valToFind, c);
    }
}

void DATABASE::printTabWhereElementIs(std::string nameTab, std::string nameCol, std::string valToFind1, std::string valToFind2, char c) {
    if(_tables.find(nameTab) != _tables.end()){
        _tables[nameTab].printRowWhere(nameCol, valToFind1, valToFind2, c);
    }
}

void DATABASE::updateTab(std::string &nameTab, std::string &newName) {
    TABLE tabSaved;
    if(!tabIsPresent(newName)){
        auto itr = _tables.find(nameTab);
        if(itr != _tables.end()){
            tabSaved = itr->second;
            _tables.erase(nameTab);
            _tables.insert({newName, tabSaved});
            std::cout << "Tabella " << newName << " aggiornata correttamente" << std::endl;
        } else {
            std::cout << "Tabella " << nameTab << " non presente" << std::endl;
        }
    } else {
        std::cout << "Tabella " << newName << " già presente" << std::endl;
    }
}

void DATABASE::updateColName(std::string &nameTab, std::string &nameCol, std::string &newName) {
    _tables[nameTab].updateColName(nameCol, newName);
}

void DATABASE::updateColumnVals(std::string &nameTab, std::string &nameCol, std::string &newVal) {
    _tables[nameTab].updateColVals(nameCol, newVal);
}

void DATABASE::updateColumnElem(std::string &nameTab, std::string &nameCol, std::string &oldVal, std::string &newVal) {
    _tables[nameTab].updateColElem(nameCol, oldVal, newVal);
}

void DATABASE::updateTabRowWhere(std::string &nameTab, std::string &nameCol, std::string &valToFind, std::vector<std::string> &rowVals, char c) {
    _tables[nameTab].updateRowWhere(nameCol, valToFind, rowVals, c);
}

void DATABASE::fillFieldsOf(std::string &nameTab) {
    _tables[nameTab].fillFields();
}

std::string DATABASE::getNameFromFile(std::fstream &fp) {
    std::string nameToRet, line, spaceDelim = " ";
    size_t pos = 0;
    std::getline(fp, line);
    pos = line.find(spaceDelim);
    nameToRet = line.substr(pos + 1, line.size());
    return nameToRet;
}

std::vector<std::string> DATABASE::getNamesFromFile(std::fstream &fp) {
    std::vector<std::string> tabsOfFile;
    std::string tabOfFile;
    while(!fp.eof()){
        tabOfFile = this->getNameFromFile(fp);
        if(!tabOfFile.empty()){
            tabsOfFile.push_back(tabOfFile);
            this-> skipTab(fp);
        }
    }
    return tabsOfFile;
}

void DATABASE::saveTab(std::fstream &fp, std::string &tabName) {
    int nRow = _tables[tabName].getMaxColDim();
    int nCol = _tables[tabName].getTabDim();
    fp << "Nome_tabella: " << tabName << std::endl;
    fp << "Numero_righe: " << nRow << std::endl;
    fp << "Numero_colonne: "<< nCol << std::endl;
    _tables[tabName].saveTable(fp);
}

void DATABASE::saveTabs(std::fstream &fp, std::fstream &fp_tmp, std::vector<std::string> &tabNames) {
    std::string tabOfFile, line, word, spaceDelim = " ";
    std::vector<std::string> tabsOfFile;
    bool found;
    int i, col;
    size_t pos;
    tabsOfFile = this->getNamesFromFile(fp);
    /*
     * 3 casi
     * tabella nel file -> aggiornarla e rimuovere il nome dal vecchio file
     * tabella non nel file -> aggiungerla
     * se avanzano tabelle dal file vecchio basta trascriverle nel nuovo
     */
    for(auto &tabToSave : tabNames){
        auto tabToUpdate = std::find(tabsOfFile.begin(), tabsOfFile.end(), tabToSave);
        if(tabToUpdate != tabsOfFile.end()){
            //tabella da aggiornare
            this->saveTab(fp_tmp, tabToSave);
            tabsOfFile.erase(tabToUpdate);
        } else {
            //tabella non presente
            this->saveTab(fp_tmp, tabToSave);
        }
    }
    //tabelle che avanzano
    fp.clear();
    fp.seekg(std::ios::beg);
    for(auto tabToRewrite = tabsOfFile.begin(); tabToRewrite != tabsOfFile.end(); tabToRewrite++){
        found = false;
        while(!found){
            tabOfFile = this->getNameFromFile(fp);
            if((*(tabToRewrite) == tabOfFile)){
                //tabella da riscrivere nel nuovo file
                fp_tmp << "Nome_tabella: " << *tabToRewrite << std::endl;
                for(i = 0; i < 2; i++){
                    std::getline(fp, line);
                    fp_tmp << line << std::endl;
                    if(i == 0){
                        pos = line.find(spaceDelim);
                        word = line.substr(pos + 1, line.size());
                        col = std::stoi(word);
                    }
                }
                for(i = 0; i < col + 2; i++){
                    std::getline(fp, line);
                    fp_tmp << line << std::endl;
                }
                fp_tmp << std::endl;
                found = true;
            } else {
                this->skipTab(fp);
            }
        }
        fp.seekg(std::ios::beg);
    }
}

void DATABASE::saveDatabase(std::fstream &fp, std::fstream &fp_tmp) {
    std::vector<std::string> database;
    for(auto &tabToSave : _tables){
        database.push_back(tabToSave.first);
    }
    this->saveTabs(fp, fp_tmp, database);
}

void DATABASE::loadTab(std::fstream &fp, std::string tabName) {
    int row, col;
    std::string word;
    fp >> word >> row;
    fp >> word >> col;
    _tables[tabName].loadTable(fp, row, col);
}

void DATABASE::loadTabs(std::fstream &fp, std::vector<std::string> tabNames) {
    std::string tabName;
    bool found, present;
    for(auto tabToLoad = tabNames.begin(); tabToLoad != tabNames.end(); tabToLoad++){
        fp.seekp(std::ios::beg);
        found = false;
        present = true;
        while(!found && present){
            tabName = this->getNameFromFile(fp);
            if(tabName == *tabToLoad){
                found = true;
                this->loadTab(fp, tabName);
            } else if(tabName != *tabToLoad && fp.eof()){
                std::cout << "Tabella " << *tabToLoad << " non presente nel file" << std::endl;
                fp.clear();
                present = false;
            } else {
                this->skipTab(fp);
            }
        }
    }
}

void DATABASE::loadDatabase(std::fstream &fp) {
    std::vector<std::string> tabs, tabsOfFile;
    tabsOfFile = this->getNamesFromFile(fp);
    fp.clear();
    fp.seekp(std::ios::beg);
    if(!_tables.empty()){
        for(auto &tabsOfDatab : _tables){
            for(auto tabOfFile = tabsOfFile.begin(); tabOfFile != tabsOfFile.end(); tabOfFile++){
                if(tabsOfDatab.first != *tabOfFile){
                    tabs.push_back(*tabOfFile);
                }
            }
        }
        this->loadTabs(fp, tabs);
    } else {
        this->loadTabs(fp, tabsOfFile);
    }
}

void DATABASE::skipTab(std::fstream &fp) {
    std::string word;
    int row, col, i, j;
    fp >> word >> row;
    fp >> word >> col;
    for(i = 0; i < row + 2; i++){
        for(j = 0; j < col; j++){
            fp >> word;
        }
    }
    fp >> word;
}

void DATABASE::sortBy(std::string tabName, std::string colName, char comm) {
    _tables[tabName].sortBy(colName, comm);
}