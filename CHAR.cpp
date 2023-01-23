//
// Created by loris on 22/09/2022.
//

#include "CHAR.h"

CHAR::CHAR(char num) {
    _char = num;
}

char CHAR::getChar() const {
    return _char;
}

std::ostream &operator<<(std::ostream &os, const CHAR &toPrint) {
    os << toPrint.getChar();
    return os;
}

std::istream &operator>>(std::istream &is, CHAR &toAssign) {
    std::string val;
    if(is >> val){
        if(val.size() > 1){
            throw std::invalid_argument("Formato carattere non corretto");
        }
        toAssign = CHAR(val[0]);
    } else {
        is.setstate(std::ios::failbit);
    }
    return is;
}

bool CHAR::operator<(const CHAR &toCompare) const {
    bool low = false;
    if(_char < toCompare.getChar()){
        low = true;
    }
    return low;
}

bool CHAR::operator>(const CHAR &toCompare) const {
    bool gre = false;
    if(_char > toCompare.getChar()){
        gre = true;
    }
    return gre;
}

bool CHAR::operator==(const CHAR &toCompare) const {
    bool eq = false;
    if(_char == toCompare.getChar()){
        eq = true;
    }
    return eq;
}

bool CHAR::operator<=(const CHAR &toCompare) const {
    bool loweq = false;
    if(_char <= toCompare.getChar()){
        loweq = true;
    }
    return loweq;
}

bool CHAR::operator>=(const CHAR &toCompare) const {
    bool greeq = false;
    if(_char >= toCompare.getChar()){
        greeq = true;
    }
    return greeq;
}

bool CHAR::operator!=(const CHAR &toCompare) const {
    bool neq = false;
    if(_char != toCompare.getChar()){
        neq = true;
    }
    return neq;
}

void CHAR::operator=(const CHAR &toCompare) {
    _char = toCompare.getChar();
}

