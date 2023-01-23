//
// Created by loris on 22/09/2022.
//

#include "FLOAT.h"

FLOAT::FLOAT(float num) {
    _float = num;
}

float FLOAT::getFloat() const {
    return _float;
}

std::ostream &operator<<(std::ostream &os, const FLOAT &toPrint) {
    os << toPrint.getFloat();
    return os;
}

std::istream &operator>>(std::istream &is, FLOAT &toAssign) {
    std::string val;
    int numDots = 0;
    if(is >> val){
        for(auto &car: val){
            if(((car < '0') && (car != '.')) || (car > '9')){
                throw std::invalid_argument("Formato decimale non corretto");
            } else if(car == '.'){
                numDots++;
                if(numDots > 1){
                    throw std::invalid_argument("Formato decimale non corretto");
                }
            }
        }
        toAssign = FLOAT(std::stof(val));
    } else {
        is.setstate(std::ios::failbit);
    }
    return is;
}

bool FLOAT::operator<(const FLOAT &toCompare) const {
    bool low = false;
    if(_float < toCompare.getFloat()){
        low = true;
    }
    return low;
}

bool FLOAT::operator>(const FLOAT &toCompare) const {
    bool gre = false;
    if(_float > toCompare.getFloat()){
        gre = true;
    }
    return gre;
}

bool FLOAT::operator==(const FLOAT &toCompare) const {
    bool eq = false;
    if(_float == toCompare.getFloat()){
        eq = true;
    }
    return eq;
}

bool FLOAT::operator<=(const FLOAT &toCompare) const {
    bool loweq = false;
    if(_float <= toCompare.getFloat()){
        loweq = true;
    }
    return loweq;
}

bool FLOAT::operator>=(const FLOAT &toCompare) const {
    bool greeq = false;
    if(_float >= toCompare.getFloat()){
        greeq = true;
    }
    return greeq;
}

bool FLOAT::operator!=(const FLOAT &toCompare) const {
    bool neq = false;
    if(_float != toCompare.getFloat()){
        neq = true;
    }
    return neq;
}

void FLOAT::operator=(const FLOAT &toCompare) {
    _float = toCompare.getFloat();
}

