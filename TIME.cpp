//
// Created by loris on 08/02/2022.
//

#include "TIME.h"

TIME::TIME(int hh, int mm) {
    _hh = hh; _mm = mm;
}

int TIME::getHh() const {
    return _hh;
}

int TIME::getMm() const {
    return _mm;
}

std::ostream &operator<<(std::ostream &os, const TIME &toPrint) {
    os << toPrint.getHh() << ":" << toPrint.getMm();
    return os;
}

std::istream &operator>>(std::istream &is, TIME &toAssign) {
    int hour, minute;
    char column;
    if(is >> hour >> column >> minute){
        if((hour < 25) && (column == ':') && (minute < 60)){
            toAssign = TIME(hour, minute);
        } else if((hour == 0) && (minute == 0)){
            toAssign = TIME();
        } else {
            throw std::invalid_argument("Formato orario non corretto");
        }
    } else {
        is.setstate(std::ios::failbit);
    }
    return is;
}

bool TIME::operator<(const TIME &toCompare) const {
    bool low = false;
    if(_hh < toCompare.getHh()){
        low = true;
    } else if(_hh == toCompare.getHh()){
        if(_mm < toCompare.getMm()){
            low = true;
        }
    }
    return low;
}

bool TIME::operator>(const TIME &toCompare) const {
    bool gre = false;
    if(_hh > toCompare.getHh()){
        gre = true;
    } else if(_hh == toCompare.getHh()){
        if(_mm > toCompare.getMm()){
            gre = true;
        }
    }
    return gre;
}

bool TIME::operator==(const TIME &toCompare) const {
    bool eq = false;
    if((_hh == toCompare.getHh()) && (_mm == toCompare.getMm())){
        eq = true;
    }
    return eq;
}

bool TIME::operator!=(const TIME &toCompare) const {
    bool neq = false;
    if((_hh != toCompare.getHh()) || (_mm != toCompare.getMm())){
        neq = true;
    }
    return neq;
}

void TIME::operator=(const TIME &toCompare) {
    _hh = toCompare.getHh();
    _mm = toCompare.getMm();
}

bool TIME::operator<=(const TIME &toCompare) const {
    bool loweq = false;
    if(*this < toCompare || *this == toCompare)
        loweq = true;
    return loweq;
}

bool TIME::operator>=(const TIME &toCompare) const {
    bool greeq = false;
    if(*this > toCompare || *this == toCompare)
        greeq = true;
    return greeq;
}


