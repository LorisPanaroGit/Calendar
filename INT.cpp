//
// Created by loris on 22/09/2022.
//

#include "INT.h"

INT::INT(int num) {
    _int = num;
}

int INT::getInt() const {
    return _int;
}

std::ostream &operator<<(std::ostream &os, const INT &toPrint) {
    os << toPrint.getInt();
    return os;
}

std::istream &operator>>(std::istream &is, INT &toAssign) {
    std::string val;
    if(is >> val){
        for(auto &car : val){
            if((car < '0') || (car > '9')){
                throw std::invalid_argument("Formato numero intero non corretto");
            }
        }
        toAssign = INT(std::stoi(val));
    } else {
        is.setstate(std::ios::failbit);
    }
    return is;
}

bool INT::operator<(const INT &toCompare) const {
    bool low = false;
    if(_int < toCompare.getInt()){
        low = true;
    }
    return low;
}

bool INT::operator>(const INT &toCompare) const {
    bool gre = false;
    if(_int > toCompare.getInt()){
        gre = true;
    }
    return gre;
}

bool INT::operator==(const INT &toCompare) const {
    bool eq = false;
    if(_int == toCompare.getInt()){
        eq = true;
    }
    return eq;
}

bool INT::operator<=(const INT &toCompare) const {
    bool loweq = false;
    if(_int <= toCompare.getInt()){
        loweq = true;
    }
    return loweq;
}

bool INT::operator>=(const INT &toCompare) const {
    bool greeq = false;
    if(_int >= toCompare.getInt()){
        greeq = true;
    }
    return greeq;
}

bool INT::operator!=(const INT &toCompare) const {
    bool neq = false;
    if(_int != toCompare.getInt()){
        neq = true;
    }
    return neq;
}

void INT::operator=(const INT &toCompare) {
    _int = toCompare.getInt();
}

