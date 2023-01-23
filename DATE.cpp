//
// Created by loris on 08/02/2022.
//

#include "DATE.h"

DATE::DATE(int yy, int mm, int dd) {
    _yy = yy; _mm = mm; _dd = dd;
}

int DATE::getYy() const {
    return _yy;
}

int DATE::getMm() const {
    return _mm;
}

int DATE::getDd() const {
    return _dd;
}

std::ostream &operator<<(std::ostream &os, const DATE &toPrint) {
    os << toPrint.getDd() << "/" << toPrint.getMm() << "/" << toPrint.getYy();
    return os;
}

std::istream &operator>>(std::istream &is, DATE &toAssign) {
    int day, month, year;
    char col1, col2;
    if(is >> day >> col1 >> month >> col2 >> year){
        if((day < 32) && (col1 == '/') && (month < 13) && (col2 == '/') && (year > 1000)){
            toAssign = DATE(year, month, day);
        } else if((day == 0) && (month == 0) && (year == 0)){
            toAssign = DATE();
        } else {
            throw std::invalid_argument("Formato data non corretto");
        }
    } else {
        is.setstate(std::ios::failbit);
    }
    return is;
}

bool DATE::operator<(const DATE &toCompare) const {
    bool low = false;
    if(_yy < toCompare.getYy())
        low = true;
    else if(_yy == toCompare.getYy()){
        if(_mm < toCompare.getMm())
            low = true;
        else if(_mm == toCompare.getMm()){
            if(_dd < toCompare.getDd())
                low = true;
        }
    }
    return low;
}

bool DATE::operator>(const DATE &toCompare) const {
    bool gre = false;
    if(_yy > toCompare.getYy())
        gre = true;
    else if(_yy == toCompare.getYy()){
        if(_mm > toCompare.getMm())
            gre = true;
        else if(_mm == toCompare.getMm()){
            if(_dd > toCompare.getDd())
                gre = true;
        }
    }
    return gre;
}

bool DATE::operator==(const DATE &toCompare) const {
    bool eq = false;
    if((_yy == toCompare.getYy()) && (_mm == toCompare.getMm()) && (_dd == toCompare.getDd()))
        eq = true;
    return eq;
}

bool DATE::operator!=(const DATE &toCompare) const {
    bool neq = false;
    if((_yy != toCompare.getYy()) || (_mm != toCompare.getMm()) || (_dd != toCompare.getDd()))
        neq = true;
    return neq;
}

void DATE::operator=(const DATE &toCompare) {
    _yy = toCompare.getYy(); _mm = toCompare.getMm(); _dd = toCompare.getDd();
}

bool DATE::operator<=(const DATE &toCompare) const {
    bool loweq = false;
    if(*this < toCompare || *this == toCompare)
        loweq = true;
    return loweq;
}

bool DATE::operator>=(const DATE &toCompare) const {
    bool greeq = false;
    if(*this > toCompare || *this == toCompare)
        greeq = true;
    return greeq;
}




