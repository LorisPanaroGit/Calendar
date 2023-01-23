//
// Created by loris on 08/02/2022.
//

#ifndef CALENDAR_DATE_H
#define CALENDAR_DATE_H
#include <iostream>
#include <sstream>
#include <stdexcept>

class DATE {
public:
    DATE() = default;
    DATE(int yy, int mm, int dd);
    /*get function*/
    int getYy() const;
    int getMm() const;
    int getDd() const;
    /*print functions*/
    friend std::ostream& operator<<(std::ostream &os, const DATE &toPrint);
    friend std::istream& operator>>(std::istream &is, DATE &toAssign);
    /*operators*/
    bool operator<(const DATE &toCompare) const;
    bool operator>(const DATE &toCompare) const;
    bool operator==(const DATE &toCompare) const;
    bool operator<=(const DATE &toCompare) const;
    bool operator>=(const DATE &toCompare) const;
    bool operator!=(const DATE &toCompare) const;
    void operator=(const DATE &toCompare);
    ~DATE() = default;

private:
    int _yy, _mm, _dd;
};


#endif //CALENDAR_DATE_H
