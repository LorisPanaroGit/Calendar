//
// Created by loris on 09/02/2022.
//

#include "TABLE.h"


void TABLE::reserveSpace(std::string name, std::string type) {
    switch(toTypes(type)){
        case OptInt:
            _columns[name].reset(new COLUMNINT);
            break;
        case OptFloat:
            _columns[name].reset(new COLUMNFLOAT);
            break;
        case OptChar:
            _columns[name].reset(new COLUMNCHAR);
            break;
        case OptBool:
            _columns[name].reset(new COLUMNBOOL);
            break;
        case OptString:
            _columns[name].reset(new COLUMNTEXT);
            break;
        case OptDate:
            _columns[name].reset(new COLUMNDATE);
            break;
        case OptTime:
            _columns[name].reset(new COLUMNTIME);
            break;
        case NVopt:
            std::cout << "Tipo " << type << " sconosciuto" << std::endl;
            break;
    }
}

void TABLE::insertRow(std::vector<std::string> values) {
    std::map<std::string, std::shared_ptr<COLUMNBASE>>::iterator cols = _columns.begin();
    this->fillFields();
    for(auto &val : values){
        cols->second->loadElemLast(val);
        cols++;
    }
}

void TABLE::fillFields() {
    int maxColDim = 0;
    for(auto &itr : _columns){
        if(itr.second->getDim() > maxColDim)
            maxColDim = itr.second->getDim();
    }
    for(auto &itr : _columns){
        itr.second->fillField(maxColDim);
    }
}

void TABLE::updateColName(std::string &nameCol, std::string &newCol) {
    std::shared_ptr<COLUMNBASE> colSaved;
    if(!colIsPresent(newCol)){
        auto itr = _columns.find(nameCol);
        if(itr != _columns.end()){
            colSaved = itr->second;
            _columns.erase(nameCol);
            _columns.insert({newCol, colSaved});
            std::cout << "Colonna " << newCol << " aggiornata correttamente" << std::endl;
        } else {
            std::cout << "Colonna " << nameCol << " non presente" << std::endl;
        }
    } else {
        std::cout << "Colonna " << newCol << " già presente" << std::endl;
    }
}

void TABLE::updateColVals(std::string &nameCol, std::string &valToAdd) {
    _columns[nameCol]->loadElemLast(valToAdd);
}

void TABLE::updateColElem(std::string &nameCol, std::string &valToUpdate, std::string &valToAdd) {
    _columns[nameCol]->updateElem(valToUpdate, valToAdd);
}

void TABLE::updateRowWhere(std::string &nameCol, std::string &val, std::vector<std::string> &rowVals, char c) {
    std::vector<int> posToUpdate;
    int i, j;
    if(colIsPresent(nameCol)){
        posToUpdate = _columns[nameCol]->getElemWhere(val, c);
        if(!posToUpdate.empty()){
            for(i = 0; i < posToUpdate.size(); i++){
                j = 0;
                for(auto &records : _columns){
                    records.second->loadElementAt(rowVals[j], posToUpdate[i]);
                    j++;
                }
            }
            std::cout << "Riga aggiornata correttamente" << std::endl;
        } else {
            std::cout << "Valore " << val << " non presente" << std::endl;
        }
    } else {
        std::cout << "Colonna " << nameCol << " non presente" << std::endl;
    }
}

void TABLE::updateColumn(std::string &columnName) {
    if(this->colIsPresent(columnName)){
        this->flushColumn(columnName);
    }
}

std::string TABLE::getColType(std::string colName) const {
    std::string typeToRet;
    auto col = _columns.find(colName);
    if(col != _columns.end()){
        typeToRet = col->second->getType();
    } else {
        std::cout << "Colonna " << colName << " inesistente" << std::endl;
    }
    return typeToRet;
}

int TABLE::getColDim() {
    return _columns.begin()->second->getDim();
}

int TABLE::getTabDim() {
    return _columns.size();
}

int TABLE::getMaxColDim() {
    int max = 0;
    for(auto &itr : _columns){
        if(itr.second->getDim() > max){
            max = itr.second->getDim();
        }
    }
    return max;
}

bool TABLE::colIsPresent(std::string colToFind) {
    bool found = false;
    if(_columns.find(colToFind) != _columns.end()){
        found = true;
    }
    return found;
}

bool TABLE::elemIsPresent(std::string &toFind, std::string &colName) {
    bool found = false;
    if(_columns[colName]->elementIsPresent(toFind)){
        found = true;
    }
    return found;
}

void TABLE::printCol(std::vector<std::string> columnNames) {
    int i;
    if(!_columns.empty()){
        for(i = 0; i < columnNames.size(); i++) {
           if(_columns.find(columnNames[i]) == _columns.end()){
               auto toRemove = std::find(columnNames.begin(), columnNames.end(), columnNames[i]);
               columnNames.erase(toRemove);
           }
        }
        for(auto &name : columnNames){
            std::cout << name << " ";
        }
        std::cout << std::endl;
        for(i = 0; i < _columns.begin()->second->getDim(); i++){
            for(auto &name : columnNames){
                _columns[name]->printAt(i);
                std::cout << " ";
            }
            std::cout << std::endl;
        }
    } else {
        std::cout << "Tabella vuota: nessun valore presente" << std::endl;
    }
}


void TABLE::printTab() const {
    int i, maxSize = 0;
    if(!_columns.empty()){
        for(auto& fields : _columns){
            std::cout << fields.first << " ";
            if(fields.second->getDim() > maxSize){
                maxSize = fields.second->getDim();
            }
        }
        std::cout << std::endl;
        for(i = 0; i < maxSize; i++){
            for(auto& values : _columns){
                values.second->printAt(i);
                std::cout << " ";
            }
            std::cout << std::endl;
        }
    } else {
        std::cout << "Tabella vuota: nessun valore presente" << std::endl;
    }
}

void TABLE::printFields() const {
    if(!_columns.empty()){
        for(auto &fields : _columns){
            std::cout << fields.first << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "Tabella vuota: nessun valore presente" << std::endl;
    }
}

void TABLE::printRowWhere(std::string colName, std::string &val, char c) {
    int i;
    std::vector<int> posToPrint;
    if(!_columns.empty()){
        auto itr = _columns.find(colName);
        if(itr != _columns.end()){
            posToPrint = itr->second->getElemWhere(val, c);
            if(!posToPrint.empty()){
                this->printFields();
                for(i = 0; i < posToPrint.size(); i++){
                    for(auto &records : _columns){
                        records.second->printAt(posToPrint[i]);
                        std::cout << " ";
                    }
                    std::cout << std::endl;
                }
            } else {
                std::cout << "Valore " << val << " non presente" << std::endl;
            }
        } else {
            std::cout << "Colonna " << colName << " inesistente" << std::endl;
        }
    } else {
        std::cout << "Tabella vouta: nessun valore presente" << std::endl;
    }
}

void TABLE::printRowWhere(std::string colName, std::string &val1, std::string &val2, char c) {
    int i;
    std::vector<int> posToPrint;
    if(!_columns.empty()){
        auto itr = _columns.find(colName);
        if(itr != _columns.end()){
            posToPrint = itr->second->getElemWhere(val1, val2, c);
            if(!posToPrint.empty()){
                this->printFields();
                for(i = 0; i < posToPrint.size(); i++){
                    for(auto &records : _columns){
                        records.second->printAt(posToPrint[i]);
                        std::cout << " ";
                    }
                    std::cout << std::endl;
                }
            }
        } else {
            std::cout << "Colonna " << colName << " inesistente" << std::endl;
        }
    } else {
        std::cout << "Tabella vuota: nessun valore presente" << std::endl;
    }
}

void TABLE::sortBy(std::string colName, char comm) {
    auto itr = _columns.find(colName);
    int i , j;
    if(itr != _columns.end()){
        if(!itr->second->isEmpty()){
            for(i = 0; i < itr->second->getDim(); i++){
                for(j = i + 1; j < itr->second->getDim(); j++){
                    if(comm == 'a'){
                        if(itr->second->greatherThan(i, j)){
                            for(auto &records : _columns){
                                records.second->exchangeValues(i, j);
                            }
                        }
                    } else if(comm == 'd'){
                        if(!(itr->second->greatherThan(i, j))){
                            for(auto &records : _columns){
                                records.second->exchangeValues(i, j);
                            }
                        }
                    }
                }
            }
        } else {
            std::cout << "Colonna '" << itr->first << "' vuota: nessun valore inserito" << std::endl;
        }
    } else {
        std::cout << "Colonna " << colName << " inesistente" << std::endl;
    }
}

void TABLE::swapRows(int row1, int row2) {
    for(auto &records : _columns){
        records.second->exchangeValues(row1, row2);
    }
}

void TABLE::deleteTab() {
    _columns.clear();
}

void TABLE::deleteColumn(std::string &columnName) {
    if(_columns.find(columnName) != _columns.end()){
        _columns.erase(columnName);
    } else {
        std::cout << "Colonna " << columnName << " non presente" << std::endl;
    }
}

void TABLE::deleteElement(std::string &columnName, std::string &toDelete) {
    _columns[columnName]->deleteElem(toDelete);
}

void TABLE::deleteFirstRow() {
    for(auto &values : _columns){
        values.second->deleteFirst();
    }
}

void TABLE::deleteLastRow() {
    for(auto &values : _columns){
        values.second->deleteLast();
    }
}

void TABLE::flushColumn(std::string colName) {
    if(colIsPresent(colName)){
        _columns[colName]->deleteColumn();
    }
}

void TABLE::deleteRowWhere(std::string colName, std::string &val, char c) {
    int i;
    std::vector<int> posToDel;
    if(!_columns.empty()){
        auto itr = _columns.find(colName);
        if(itr != _columns.end()){
            posToDel = itr->second->getElemWhere(val, c);
            for(i = posToDel.size() - 1; i >= 0; i--){
                for(auto &records : _columns){
                    records.second->deleteAt(posToDel[i]);
                }
            }
        } else {
            std::cout << "Colonna " << colName << " inesistente" << std::endl;
        }
    } else {
        std::cout << "Tabella vouta: nessun valore presente" << std::endl;
    }
}

void TABLE::deleteRowWhere(std::string colName, std::string &val1, std::string &val2, char c) {
    int i;
    std::vector<int> posToDel;
    if(!_columns.empty()){
        auto itr = _columns.find(colName);
        if(itr != _columns.end()){
            posToDel = itr->second->getElemWhere(val1, val2, c);
            for(i = posToDel.size() - 1; i >= 0; i--){
                for(auto &records : _columns){
                    records.second->deleteAt(posToDel[i]);
                }
            }
        } else {
            std::cout << "Colonna " << colName << " inesistente" << std::endl;
        }
    } else {
        std::cout << "Tabella vouta: nessun valore presente" << std::endl;
    }
}

void TABLE::saveTable(std::fstream &fp) {
    int i, colSize;
    std::string elem;
    if(!_columns.empty()) {
        for (auto &itr: _columns) {
            fp << itr.second->getType() << " ";
        }
        fp << std::endl;
        for (auto &itr: _columns) {
            fp << itr.first << " ";
        }
        fp << std::endl;
        colSize = this->getMaxColDim();
        for (i = 0; i < colSize; i++) {
            for (auto &itr: _columns) {
                elem = itr.second->getElAtPos(i);
                if (!elem.empty()) {
                    fp << elem << " ";
                } else {
                    fp << "/ ";
                }
            }
            fp << std::endl;
        }
        fp << std::endl;
    } else {
        fp << std::endl;
    }
}

void TABLE::loadTable(std::fstream &fp, int nRow, int nCol) {
    int i, j;
    std::string word;
    std::vector<std::string> types, names;
    for(i = 0; i < nCol; i++){
        fp >> word;
        types.push_back(word);
    }
    for(i = 0; i < nCol; i++){
        fp >> word;
        names.push_back(word);
    }
    for(i = 0; i < nCol; i++){
        this->reserveSpace(names[i], types[i]);
    }
    for(i = 0; i < nRow; i++){
        for(j = 0; j < nCol; j++){
            fp >> word;
            if(word != "/"){
                _columns[names[j]]->loadElemLast(word);
            }
        }
    }
}

void TABLE::insertLast(std::string nameCol, std::string &toAdd) {
    _columns[nameCol]->loadElemLast(toAdd);
    //this->fillFields();
}

void TABLE::insertFirst(std::string nameCol, std::vector<std::string> &toAdd) {
    for(auto &itr : toAdd){
        _columns[nameCol]->loadElemFirst(itr);
    }
    //this->fillFields();
}

TABLE& TABLE::operator=(const TABLE &toAssign) {
    _columns = toAssign._columns;
    return *this;
}