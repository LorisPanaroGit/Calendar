//
// Created by loris on 22/09/2022.
//

#ifndef CALENDAR_CHAR_H
#define CALENDAR_CHAR_H
#include <iostream>
#include <string>

class CHAR {
public:
    CHAR() = default;
    CHAR(char num);
    char getChar() const;
    friend std::ostream& operator<<(std::ostream &os, const CHAR &toPrint);
    friend std::istream& operator>>(std::istream &is, CHAR &toAssign);
    bool operator<(const CHAR &toCompare) const;
    bool operator>(const CHAR &toCompare) const;
    bool operator==(const CHAR &toCompare) const;
    bool operator<=(const CHAR &toCompare) const;
    bool operator>=(const CHAR &toCompare) const;
    bool operator!=(const CHAR &toCompare) const;
    void operator=(const CHAR &toCompare);
    ~CHAR() = default;
private:
    char _char;
};


#endif //CALENDAR_CHAR_H
