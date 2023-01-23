//
// Created by loris on 22/09/2022.
//

#ifndef CALENDAR_FLOAT_H
#define CALENDAR_FLOAT_H
#include <iostream>
#include <string>
#include <exception>

class FLOAT {
public:
    FLOAT() = default;
    FLOAT(float num);
    float getFloat() const;
    friend std::ostream& operator<<(std::ostream &os, const FLOAT &toPrint);
    friend std::istream& operator>>(std::istream &is, FLOAT &toAssign);
    bool operator<(const FLOAT &toCompare) const;
    bool operator>(const FLOAT &toCompare) const;
    bool operator==(const FLOAT &toCompare) const;
    bool operator<=(const FLOAT &toCompare) const;
    bool operator>=(const FLOAT &toCompare) const;
    bool operator!=(const FLOAT &toCompare) const;
    void operator=(const FLOAT &toCompare);
    ~FLOAT() = default;
private:
    float _float;
};


#endif //CALENDAR_FLOAT_H
