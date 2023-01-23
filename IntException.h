//
// Created by loris on 27/09/2022.
//

#ifndef CALENDAR_INTEXCEPTION_H
#define CALENDAR_INTEXCEPTION_H

class IntException {
public:
    IntException() : message("Formto numero intero non valido"){}
    const char* what() const {
        return message;
    }
private:
    const char *message;
};


#endif //CALENDAR_INTEXCEPTION_H
