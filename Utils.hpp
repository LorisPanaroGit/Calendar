//
// Created by loris on 09/02/2022.
//

#ifndef CALENDAR_UTILS_HPP
#define CALENDAR_UTILS_HPP
#include <iostream>

enum types {
    OptInt,
    OptFloat,
    OptChar,
    OptBool,
    OptString,
    OptDate,
    OptTime,
    NVopt
};

inline types toTypes(std::string& strType) {
    types enumType = NVopt;
    if(strType == "INT")
        enumType = OptInt;
    else if(strType == "FLOAT")
        enumType = OptFloat;
    else if(strType == "CHAR")
        enumType = OptChar;
    else if(strType == "BOOL")
        enumType = OptBool;
    else if(strType == "STRING")
        enumType = OptString;
    else if(strType == "DATE")
        enumType = OptDate;
    else if(strType == "TIME")
        enumType = OptTime;
    return enumType;
}

enum command {
    SELECT,
    PRINT,
    SORT,
    INSERT,
    DELETE,
    UPDATE,
    CREATE,
    SAVE,
    LOAD,
    QUIT,
    NVCOMM
};

inline command toCommand(std::string& com) {
    command c = NVCOMM;
    if(com == "SELEZIONA" || com == "Seleziona" || com == "seleziona")
        c = SELECT;
    else if(com == "STAMPA" || com == "Stampa" || com == "stampa")
        c = PRINT;
    else if(com == "ORDINA" || com == "Ordina" || com == "ordina")
        c = SORT;
    else if(com == "INSERISCI" || com == "Inserisci" || com == "inserisci")
        c = INSERT;
    else if(com == "CANCELLA" || com == "Cancella" || com == "cancella")
        c = DELETE;
    else if(com == "AGGIORNA" || com == "Aggiorna" || com == "aggiorna")
        c = UPDATE;
    else if(com == "NUOVA" || com == "Nuova" || com == "nuova")
        c = CREATE;
    else if(com == "NUOVO" || com == "Nuovo" || com == "nuovo")
        c = CREATE;
    else if(com == "SALVA" || com == "Salva" || com == "salva")
        c = SAVE;
    else if(com == "CARICA" || com == "Carica" || com == "carica")
        c = LOAD;
    else if(com == "TERMINA" || com == "Termina" || com == "termina")
        c = QUIT;
    else std::cout << "Comando " << com << " sconosciuto" << std::endl;
    return c;
}

enum keyword {
    ELEMENT,
    COL,
    ROW,
    TAB,
    DATAB,
    NAME,
    WHERE,
    NVKEY
};

inline keyword toKeyword(std::string& elem) {
    keyword e = NVKEY;
    if(elem == "ELEMENTO" || elem == "Elemento" || elem == "elemento")
        e = ELEMENT;
    else if(elem == "COLONNA" || elem == "Colonna" || elem == "colonna")
        e = COL;
    else if(elem == "RIGA" || elem == "Riga" || elem == "riga")
        e = ROW;
    else if(elem == "TABELLA" || elem == "Tabella" || elem == "tabella")
        e = TAB;
    else if(elem == "DATABASE" || elem == "Database" || elem == "database")
        e = DATAB;
    else if(elem == "NOME" || elem == "Nome" || elem == "nome")
        e = NAME;
    else if(elem == "DOVE" || elem == "Dove" || elem == "dove")
        e = WHERE;
    return e;
}

enum operators {
    INCREASING,
    DECREASING,
    GREATER,
    LOWER,
    EQUAL,
    BETWEEN,
    OUTSIDE,
    NVOP
};

inline operators toOperator(std::string& op) {
    operators o = NVOP;
    if(op == ">")
        o = GREATER;
    else if(op == "<")
        o = LOWER;
    else if(op == "=")
        o = EQUAL;
    else if(op == "<>")
        o = BETWEEN;
    else if(op == "><")
        o = OUTSIDE;
    else if(op == "CRESCENTE" || op == "Crescente" || op == "crescente")
        o = INCREASING;
    else if(op == "DECRESCENTE" || op == "Decrescente" || op == "decrescente")
        o = DECREASING;
    return o;
}

#endif //CALENDAR_UTILS_HPP
