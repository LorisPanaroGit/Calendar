//
// Created by loris on 08/02/2022.
//

#ifndef CALENDAR_COLUMNBASE_H
#define CALENDAR_COLUMNBASE_H
#include <iostream>
#include <vector>


class COLUMNBASE {
public:
    /*get functions*/
    virtual int getDim() const = 0;
    virtual std::string getElAtPos(int row) const = 0;
    virtual std::string getType() const = 0;
    virtual std::vector<int> getElemWhere(std::string &strWhere, char c) const = 0;
    virtual std::vector<int> getElemWhere(std::string &strWhere1, std::string &strWhere2, char c) const = 0;
    virtual bool elementIsPresent(std::string &val) = 0;
    /*insert functions*/
    virtual void loadElemFirst(const std::string& toInsert) = 0;
    virtual void loadElemLast(const std::string& toInsert) = 0;
    virtual void loadElementAt(const std::string& toInsert, int row) = 0;
    virtual void updateElem(const std::string &elem1, const std::string &elem2) = 0;
    virtual void fillField(int maxSize) = 0;
    /*print functions*/
    virtual void printAt(int row) const = 0;
    virtual void printColumn() const = 0;
    /*delete functions*/
    virtual void deleteFirst() = 0;
    virtual void deleteAt(int pos) = 0;
    virtual void deleteElem(std::string &toDelete) = 0;
    virtual void deleteLast() = 0;
    virtual void deleteColumn() = 0;
    /*exchange function*/
    virtual void exchangeValues(int row1, int row2) = 0;
    virtual bool greatherThan(int row1, int row2) const = 0;
    virtual bool isEmpty() const = 0;
    /*deconstructor*/
    virtual ~COLUMNBASE() {}

protected:
    std::string _columnType;
};


#endif //CALENDAR_COLUMNBASE_H
