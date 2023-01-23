//
// Created by loris on 22/09/2022.
//

#ifndef CALENDAR_INT_H
#define CALENDAR_INT_H
#include <iostream>
#include <string>
#include <exception>

class INT {
public:
    INT() = default;
    INT(int num);
    int getInt() const;
    friend std::ostream& operator<<(std::ostream &os, const INT &toPrint);
    friend std::istream& operator>>(std::istream &is, INT &toAssign);
    bool operator<(const INT &toCompare) const;
    bool operator>(const INT &toCompare) const;
    bool operator==(const INT &toCompare) const;
    bool operator<=(const INT &toCompare) const;
    bool operator>=(const INT &toCompare) const;
    bool operator!=(const INT &toCompare) const;
    void operator=(const INT &toCompare);
    ~INT() = default;
private:
    int _int;
};


#endif //CALENDAR_INT_H
