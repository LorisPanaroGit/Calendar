//
// Created by loris on 08/02/2022.
//

#ifndef CALENDAR_TIME_H
#define CALENDAR_TIME_H
#include <iostream>
#include <sstream>
#include <stdexcept>


class TIME {
public:
    TIME() = default;
    TIME(int hh, int mm);
    /*get function*/
    int getHh() const;
    int getMm() const;
    /*print functions*/
    friend std::ostream& operator<<(std::ostream &os, const TIME &toPrint);
    friend std::istream& operator>>(std::istream& is, TIME &toAssign);
    /*operators*/
    bool operator<(const TIME &toCompare) const;
    bool operator>(const TIME &toCompare) const;
    bool operator==(const TIME &toCompare) const;
    bool operator<=(const TIME &toCompare) const;
    bool operator>=(const TIME &toCompare) const;
    bool operator!=(const TIME &toCompare) const;
    void operator=(const TIME &toCompare);
    ~TIME() = default;

private:
    int _hh, _mm;
};


#endif //CALENDAR_TIME_H
