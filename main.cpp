#include <iostream>
#include <cstdio>
#include <fstream>
#include "Utils.hpp"
#include "INT.h"
#include "DATE.h"
#include "TIME.h"
#include "COLUMN.hpp"
#include "TABLE.h"
#include "DATABASE.h"

/*
 * cambiare printTabWhere in TabRowhere
 * cambiare le funzioni delle map con where con il metodo di update row where
 * cancella elemento 1 2 3... -> fare funzione in table e database
 * riguardare UPDATE COL
 * fare controlli se metto più parametri del dovuto
 * magari mettere <= e >=
 */

std::vector<std::string> splitWords(std::string& line, std::string& toDelim);

int main() {
    bool quitProgram = false, statusOk;
    DATABASE database1;
    std::string line, delim = " ", nameTab, nameCol, rowLine;
    std::vector<std::string> sentence, cols, rowVals, tabsToSave, tabsToLoad;
    std::vector<std::string>::iterator posSentence;
    std::string colToSort, colToDelete, valToInsert, valToFind, valToFind2, valToDelete;
    std::string order, sign;
    std::string newTab, newCol, newType, tab = "numeri";
    std::vector<std::string> tabs;
    char o, s;
    int foundExcp;
    std::fstream fptr, fptr_tmp;
    while(!quitProgram){
        std::cout << ">>";
        statusOk = true;
        std::getline(std::cin, line);
        if(!line.empty()){
            sentence = splitWords(line, delim);
            posSentence = sentence.begin();
        } else {
            statusOk = false;
        }
        while((posSentence != sentence.end()) && statusOk && !quitProgram){
            switch(toCommand(*posSentence)){
                case SELECT:
                    posSentence++;
                    if(posSentence != sentence.end()){
                        switch(toKeyword(*posSentence)){
                            case DATAB:
                                std::cout << "Impossibile selezionare un database" << std::endl;
                                statusOk = false;
                            case TAB:
                                posSentence++;
                                if(posSentence != sentence.end()){
                                    if(database1.tabIsPresent(*posSentence)){
                                        nameTab = *posSentence;
                                        posSentence++;
                                        if(posSentence != sentence.end()){
                                            std::cout << "Impossibile selezionare piu di una tabella" << std::endl;
                                            nameTab.clear();
                                            statusOk = false;
                                        }
                                    } else {
                                        nameTab.clear();
                                        std::cout << "Tabella " << *posSentence << " non presente" << std::endl;
                                        statusOk = false;
                                    }
                                } else {
                                    std::cout << "Parametro mancante: nome tabella" << std::endl;
                                    statusOk = false;
                                }
                                break;
                            case COL:
                                if(!nameTab.empty()){
                                    posSentence++;
                                    if(posSentence != sentence.end()){
                                        if(database1.colIsPresent(nameTab, *posSentence)){
                                            nameCol = *posSentence;
                                            posSentence++;
                                            if(posSentence != sentence.end()){
                                                std::cout << "Impossibile selezionare piu di una colonna" << std::endl;
                                                nameCol.clear();
                                                statusOk = false;
                                            } else {
                                                posSentence--;
                                            }
                                        } else {
                                            nameCol.clear();
                                            std::cout << "Colonna " << *posSentence << " non presente" << std::endl;
                                            statusOk = false;
                                        }
                                        posSentence++;
                                    } else {
                                        std::cout << "Parametro mancante: nome colonna" << std::endl;
                                        statusOk = false;
                                    }
                                } else {
                                    std::cout << "Nessuna tabella selezionata" << std::endl;
                                    statusOk = false;
                                }
                                break;
                            case ROW:
                                std::cout << "Impossibile selezionare riga" << std::endl;
                                statusOk = false;
                                break;
                            case ELEMENT:
                                std::cout << "Impossibile selezionare elemento" << std::endl;
                                statusOk = false;
                                break;
                            case NAME:
                                std::cout << "Impossibile selezionare nome" << std::endl;
                                statusOk = false;
                                break;
                            case WHERE:
                                std::cout << "Impossibile selezionare 'dove'" << std::endl;
                                statusOk = false;
                                break;
                            case NVKEY:
                                std::cout << "Parola chiave " << *posSentence << " sconosciuta" << std::endl;
                                statusOk = false;
                                break;
                            default:
                                statusOk = false;
                                break;
                        }
                    } else {
                        std::cout << "Nessun parametro per il comando seleziona" << std::endl;
                        statusOk = false;
                    }
                    break;
                case PRINT:
                    posSentence++;
                    if(posSentence != sentence.end()){
                        switch (toKeyword(*posSentence)){
                            case DATAB:
                                database1.printDatabase();
                                posSentence++;
                                if(posSentence != sentence.end()){
                                    std::cout << "Impossibile stampare piu di un database" << std::endl;
                                    statusOk = false;
                                }
                                break;
                            case TAB:
                                posSentence++;
                                if((posSentence != sentence.end()) && (toKeyword(*posSentence) == NVKEY)){ //stampa tabella nome_tabella
                                    while(posSentence != sentence.end()){
                                        nameTab = *posSentence;
                                        database1.printTab(nameTab);
                                        posSentence++;
                                    }
                                } else if((posSentence != sentence.end()) && (toKeyword(*posSentence) == WHERE)) {
                                    //stampa tabella dove
                                    posSentence++;
                                    if(toKeyword(*posSentence) == COL){ //stampa tabella dove colonna
                                        posSentence++;
                                        if((posSentence != sentence.end()) && (toOperator(*posSentence) == EQUAL)){ //stampa tabella dove colonna =
                                            posSentence++;
                                            if(posSentence != sentence.end()){
                                                while(posSentence != sentence.end()){
                                                    nameCol = *posSentence;
                                                    cols.push_back(nameCol);
                                                    posSentence++;
                                                }
                                                database1.printTabWhereColumnIs(cols);
                                                cols.clear();
                                            } else {
                                                std::cout << "Parametro mancante: nome colonna" << std::endl;
                                                statusOk = false;
                                            }
                                        } else {
                                            std::cout << "Parametro mancante: operatore" << std::endl;
                                            statusOk = false;
                                        }
                                    } else {
                                        std::cout << "Parametro per 'dove' mancante" << std::endl;
                                        statusOk = false;
                                    }
                                } else {
                                    std::cout << "Parametro mancante: nome tabella oppure 'dove'" << std::endl;
                                    statusOk = false;
                                }
                                break;
                            case COL:
                                if(!nameTab.empty()){
                                    posSentence++;
                                    if(posSentence != sentence.end()){
                                        while(posSentence != sentence.end()){
                                            nameCol = *posSentence;
                                            if(database1.colIsPresent(nameTab, nameCol)){
                                                cols.push_back(*posSentence);
                                            } else {
                                                std::cout << "Colonna " << *posSentence << " non presente" << std::endl;
                                            }
                                            posSentence++;
                                        }
                                        database1.printColumns(nameTab, cols);
                                        cols.clear();
                                    } else {
                                        std::cout << "Parametro mancante: nome colonna" << std::endl;
                                        statusOk = false;
                                    }
                                } else {
                                    std::cout << "Nessuna tabella selezionata" << std::endl;
                                    statusOk = false;
                                }
                                break;
                            case ROW:
                                if(!nameTab.empty()){
                                    posSentence++; //stampa riga dove
                                    if(posSentence != sentence.end()){
                                        if(toKeyword(*posSentence) == WHERE){
                                            posSentence++; //stampa roga dove elemento
                                            if(posSentence != sentence.end()){
                                                if(toKeyword(*posSentence) == ELEMENT){
                                                    posSentence++; //stampa riga dove elemento colonna
                                                    if(posSentence != sentence.end()){
                                                        if(toKeyword(*posSentence) == COL){
                                                            posSentence++; //stampa riga dove elemento colonna test
                                                            if(posSentence != sentence.end()){
                                                                nameCol = *posSentence;
                                                                posSentence++; //stampa riga dove elemento colonna test <>
                                                                if(posSentence != sentence.end()){
                                                                    sign = *posSentence;
                                                                    posSentence++; //stampa riga dove elemento colonna test <> elemento1
                                                                    if(posSentence != sentence.end()){
                                                                        valToFind = *posSentence;
                                                                        try{
                                                                            switch(toOperator(sign)){
                                                                                case INCREASING:
                                                                                    std::cout << "Operatore invalido" << std::endl;
                                                                                    statusOk = false;
                                                                                    break;
                                                                                case DECREASING:
                                                                                    std::cout << "Operatore invalido" << std::endl;
                                                                                    statusOk = false;
                                                                                    break;
                                                                                case GREATER:
                                                                                    s = 'g';
                                                                                    posSentence++;
                                                                                    if(posSentence != sentence.end()){
                                                                                        std::cout << "Impossibile selezionare piu di un elemento" << std::endl;
                                                                                        statusOk = false;
                                                                                    } else {
                                                                                        database1.printTabWhereElementIs(nameTab, nameCol, valToFind, s);
                                                                                    }
                                                                                    break;
                                                                                case LOWER:
                                                                                    s = 'l';
                                                                                    posSentence++;
                                                                                    if(posSentence != sentence.end()){
                                                                                        std::cout << "Impossibile selezionare piu di un elemento" << std::endl;
                                                                                        statusOk = false;
                                                                                    } else {
                                                                                        database1.printTabWhereElementIs(nameTab, nameCol, valToFind, s);
                                                                                    }
                                                                                    break;
                                                                                case EQUAL:
                                                                                    s = 'e';
                                                                                    posSentence++;
                                                                                    if(posSentence != sentence.end()){
                                                                                        std::cout << "Impossibile selezionare piu di un elemento" << std::endl;
                                                                                        statusOk = false;
                                                                                    } else {
                                                                                        database1.printTabWhereElementIs(nameTab, nameCol, valToFind, s);
                                                                                    }
                                                                                    break;
                                                                                case BETWEEN:
                                                                                    s = 'i';
                                                                                    posSentence++;
                                                                                    if(posSentence != sentence.end()){
                                                                                        valToFind2 = *posSentence;
                                                                                        posSentence++;
                                                                                        if(posSentence != sentence.end()){
                                                                                            std::cout << "Impossibile selezionare piu di due elementi" << std::endl;
                                                                                            statusOk = false;
                                                                                        } else {
                                                                                            database1.printTabWhereElementIs(nameTab, nameCol, valToFind, valToFind2, s);
                                                                                        }
                                                                                    } else {
                                                                                        std::cout << "Parametro mancante: secondo elemento" << std::endl;
                                                                                        statusOk = false;
                                                                                    }
                                                                                    break;
                                                                                case OUTSIDE:
                                                                                    s = 'o';
                                                                                    posSentence++;
                                                                                    if(posSentence != sentence.end()){
                                                                                        valToFind2 = *posSentence;
                                                                                        posSentence++;
                                                                                        if(posSentence != sentence.end()){
                                                                                            std::cout << "Impossibile selezionare piu di due elementi" << std::endl;
                                                                                            statusOk = false;
                                                                                        } else {
                                                                                            database1.printTabWhereElementIs(nameTab, nameCol, valToFind, valToFind2, s);
                                                                                        }
                                                                                    } else {
                                                                                        std::cout << "Parametro mancante: secondo elemento" << std::endl;
                                                                                        statusOk = false;
                                                                                    }
                                                                                    break;
                                                                                case NVOP:
                                                                                    std::cout << "Operatore " << *posSentence << " sconosciuto" << std::endl;
                                                                                    statusOk = false;
                                                                                default:
                                                                                    statusOk = false;
                                                                                    break;
                                                                            }
                                                                        } catch(std::invalid_argument &ex){
                                                                            std::cout << ex.what() << std::endl;
                                                                            statusOk = false;
                                                                        }
                                                                    } else {
                                                                        std::cout << "Parametro mancante: valore elemento" << std::endl;
                                                                        statusOk = false;
                                                                    }
                                                                } else {
                                                                    std::cout << "Parametro mancante: operatore" << std::endl;
                                                                    statusOk = false;
                                                                }
                                                            } else {
                                                                std::cout << "Parametro mancante: nome colonna" << std::endl;
                                                                statusOk = false;
                                                            }
                                                        } else if((toKeyword(*posSentence) != COL) && (toKeyword(*posSentence) != NVKEY)){
                                                            std::cout << "Parola chiave " << *posSentence << " non accettata" << std::endl;
                                                            statusOk = false;
                                                        } else {
                                                            std::cout << "Parola chiave " << *posSentence << " sconosciuta" << std::endl;
                                                            statusOk = false;
                                                        }
                                                    } else {
                                                        std::cout << "Parametro mancante: colonna" << std::endl;
                                                        statusOk = false;
                                                    }
                                                } else if((toKeyword(*posSentence) != ELEMENT) && (toKeyword(*posSentence) != NVKEY)) {
                                                    std::cout << "Parola chiave " << *posSentence << " non accettata" << std::endl;
                                                    statusOk = false;
                                                } else {
                                                    std::cout << "Parola chiave " << *posSentence << " sconosciuta" << std::endl;
                                                    statusOk = false;
                                                }
                                            } else {
                                                std::cout << "Parametro per 'dove' mancante" << std::endl;
                                                statusOk = false;
                                            }
                                        } else if((toKeyword(*posSentence) != WHERE) && (toKeyword(*posSentence) != NVKEY)) {
                                            std::cout << "Parola chiave " << *posSentence << " non accettata" << std::endl;
                                            statusOk = false;
                                        } else {
                                            std::cout << "Parola chiave " << *posSentence << " sconosciuta" << std::endl;
                                            statusOk = false;
                                        }
                                    } else {
                                        std::cout << "Parametro mancante: 'dove'" << std::endl;
                                        statusOk = false;
                                    }
                                } else {
                                    std::cout << "Nessuna tabella selezionata" << std::endl;
                                    statusOk = false;
                                }
                                break;
                            case ELEMENT:
                                std::cout << "Impossibile stampare un elemento" << std::endl;
                                statusOk = false;
                                break;
                            case NAME:
                                std::cout << "Impossibile stampare un nome" << std::endl;
                                statusOk = false;
                                break;
                            case WHERE:
                                std::cout << "Impossibile stampare 'dove'" << std::endl;
                                statusOk = false;
                                break;
                            case NVKEY:
                                std::cout << "Parola chiave " << *posSentence << " sconosciuta" << std::endl;
                                statusOk = false;
                                break;
                            default:
                                statusOk = false;
                                break;
                        }
                    } else {
                        std::cout << "Nessun parametro per il comando stampa" << std::endl;
                        statusOk = false;
                    }
                    break;
                case SORT:
                    posSentence++;
                    if(posSentence != sentence.end()){
                        switch(toKeyword(*posSentence)){
                            case DATAB:
                                std::cout << "Impossibile ordinare un database" << std::endl;
                                statusOk = false;
                                break;
                            case TAB:
                                std::cout << "Impossibile ordinare una tabella" << std::endl;
                                statusOk = false;
                                break;
                            case COL:
                                if(!nameTab.empty()){
                                    posSentence++;
                                    if(posSentence != sentence.end()){
                                        colToSort = *posSentence;
                                        posSentence++;
                                        if(posSentence != sentence.end()){
                                            order = *posSentence;
                                            switch(toOperator(order)){
                                                case INCREASING:
                                                    o = 'a';
                                                    database1.sortBy(nameTab, colToSort, o);
                                                    break;
                                                case DECREASING:
                                                    o = 'd';
                                                    database1.sortBy(nameTab, colToSort, o);
                                                    break;
                                                default:
                                                    std::cout << "Operatore " << order << " non valido" << std::endl;
                                                    statusOk = false;
                                                    break;
                                            }
                                            posSentence++;
                                        } else {
                                            std::cout << "Parametro mancante: tipo ordinamento" << std::endl;
                                            statusOk = false;
                                        }
                                    } else {
                                        std::cout << "Parametro mancante: nome colonna" << std::endl;
                                        statusOk = false;
                                    }
                                } else {
                                    std::cout << "Nessuna tabella selezionata" << std::endl;
                                    statusOk = false;
                                }
                                break;
                            case ROW:
                                std::cout << "Impossibile ordinare riga" << std::endl;
                                statusOk = false;
                                break;
                            case ELEMENT:
                                std::cout << "Impossibile ordinare un elemento" << std::endl;
                                statusOk = false;
                                break;
                            case NAME:
                                std::cout << "Impossibile ordinare un nome" << std::endl;
                                statusOk = false;
                                break;
                            case WHERE:
                                std::cout << "Impossibile trovare colonna da ordinare" << std::endl;
                                statusOk = false;
                                break;
                            case NVKEY:
                                std::cout << "Parola chiave " << *posSentence << " sconosciuta" << std::endl;
                                statusOk = false;
                                break;
                            default:
                                statusOk = false;
                                break;
                        }
                    } else {
                        std::cout << "Nessun parametro per il comando ordina" << std::endl;
                        statusOk = false;
                    }
                    break;
                case INSERT:
                    posSentence++;
                    if(posSentence != sentence.end()){
                        switch(toKeyword(*posSentence)){
                            case DATAB:
                                std::cout << "Impossibile creare un database: gia esistente" << std::endl;
                                statusOk = false;
                                break;
                            case TAB:
                                posSentence++;
                                if(posSentence != sentence.end()){
                                    while(posSentence != sentence.end()){
                                        newTab = *posSentence;
                                        database1.reserveSpace(newTab, TABLE());
                                        posSentence++;
                                    }
                                } else {
                                    std::cout << "Parametro mancante: nome tabella" << std::endl;
                                    statusOk = false;
                                }
                                break;
                            case COL:
                                if(!nameTab.empty()){
                                    posSentence++; //crea colonna esempio tipo, esempio2 tipo2
                                    if(posSentence != sentence.end()){
                                        while(posSentence != sentence.end()){
                                            newCol = *posSentence;
                                            posSentence++;
                                            if(posSentence != sentence.end()){
                                                newType = *posSentence;
                                                database1.getTab(nameTab).reserveSpace(newCol, newType);
                                                posSentence++;
                                            } else {
                                                std::cout << "Parametro mancante: tipo colonna per colonna '" << newCol << "'" << std::endl;
                                                statusOk = false;
                                            }
                                        }
                                    } else {
                                        std::cout << "Parametro mancante: nome colonna" << std::endl;
                                        statusOk = false;
                                    }
                                } else {
                                    std::cout << "Nessuna tabella selezionata" << std::endl;
                                    statusOk = false;
                                }
                                break;
                            case ROW:
                                if(!nameTab.empty()){
                                    posSentence++;
                                    if(posSentence == sentence.end()){
                                        std::cout << "Colonne tabella " << nameTab << " : ";
                                        database1.printFields(nameTab);
                                        std::cout << "Nuova riga per  " << nameTab << " : ";
                                        std::getline(std::cin, rowLine);
                                        rowVals = splitWords(rowLine, delim);
                                        if(rowVals.size() < database1.getTabSize(nameTab)){
                                            std::cout << "Numero elementi da inserire minore del numero di colonne" << std::endl;
                                            statusOk = false;
                                        } else if(rowVals.size() > database1.getTabSize(nameTab)){
                                            std::cout << "Numero elementi da inserire maggiore del numero di colonne" << std::endl;
                                            statusOk = false;
                                        } else {
                                            database1.insertRow(nameTab, rowVals);
                                        }
                                        rowVals.clear();
                                        rowLine.clear();
                                    } else {
                                        std::cout << "Parametri in eccesso per 'inserisci riga'" << std::endl;
                                        statusOk = false;
                                    }
                                } else {
                                    std::cout << "Nessuna tabella selezionata" << std::endl;
                                    statusOk = false;
                                }
                                break;
                            case ELEMENT:
                                if(!nameTab.empty()){
                                    if(!nameCol.empty()){
                                        posSentence++;
                                        if(posSentence != sentence.end()){
                                            try{
                                                foundExcp = 0;
                                                while(posSentence != sentence.end()){
                                                    valToInsert = *posSentence;
                                                    database1.insertLast(nameTab, nameCol, valToInsert);
                                                    posSentence++;
                                                    foundExcp++;
                                                }
                                            } catch(std::invalid_argument &ex){
                                                std::cout << ex.what() << std::endl;
                                                for(int i = 0; i < foundExcp; i++){
                                                    posSentence--;
                                                    database1.deleteElement(nameTab, nameCol, *posSentence);
                                                }
                                                statusOk = false;
                                            }
                                        } else {
                                            std::cout << "Parametro mancante: elemento" << std::endl;
                                            statusOk = false;
                                        }
                                    } else {
                                        std::cout << "Nessuna colonna selezionata" << std::endl;
                                        statusOk = false;
                                    }
                                } else {
                                    std::cout << "Nessuna tabella selezionata" << std::endl;
                                    statusOk = false;
                                }
                                break;
                            case NAME:
                                std::cout << "Impossibile creare nome" << std::endl;
                                statusOk = false;
                                break;
                            case WHERE:
                                std::cout << "Impossibile creare 'dove'" << std::endl;
                                statusOk = false;
                                break;
                            case NVKEY:
                                std::cout << "Parola chiave " << *posSentence << " sconosciuta" << std::endl;
                                statusOk = false;
                                break;
                            default:
                                statusOk = false;
                                break;
                        }
                    } else {
                        std::cout << "Nessun parametro per il comando crea" << std::endl;
                        statusOk = false;
                    }
                    break;
                case DELETE:
                    posSentence++;
                    if(posSentence != sentence.end()){
                        switch(toKeyword(*posSentence)){
                            case DATAB:
                                posSentence++;
                                if(posSentence == sentence.end()){
                                    database1.clearDatabase();
                                    std::cout << "Database eliminato correttamente" << std::endl;
                                } else {
                                    std::cout << "Impossibile eliminare piu di un database" << std::endl;
                                    statusOk = false;
                                }
                                break;
                            case TAB:
                                posSentence++;
                                if(posSentence!= sentence.end()){
                                    while(posSentence != sentence.end()){
                                        if(database1.tabIsPresent(*posSentence)){
                                            database1.deleteTab(*posSentence); //da rivedere: non cancella correttamente le tabelle
                                            std::cout << "Tabella " << *posSentence << " eliminata correttamente" << std::endl;
                                        } else {
                                            std::cout << "Tabella " << *posSentence << " non presente" << std::endl;
                                        }
                                        posSentence++;
                                    }
                                } else {
                                    std::cout << "Parametro mancante: nome tabella" << std::endl;
                                    statusOk = false;
                                }
                                break;
                            case COL:
                                if(!nameTab.empty()){
                                    posSentence++;
                                    if(posSentence != sentence.end()){
                                        while(posSentence != sentence.end()){
                                            colToDelete = *posSentence;
                                            database1.deleteColumn(nameTab, colToDelete);
                                            posSentence++;
                                        }
                                    } else {
                                        std::cout << "Parametro mancante: nome colonna" << std::endl;
                                        statusOk = false;
                                    }
                                } else {
                                    std::cout << "Nessuna tabella selezionata" << std::endl;
                                    statusOk = false;
                                }
                                break;
                            case ROW:
                                if(!nameTab.empty()){
                                    posSentence++; //elimina riga dove
                                    if(posSentence != sentence.end()){
                                        if(toKeyword(*posSentence) == WHERE){
                                            posSentence++;
                                            if(posSentence != sentence.end()){
                                                if(toKeyword(*posSentence) == ELEMENT){
                                                    posSentence++; //elimina riga dove elemento colonna
                                                    if(posSentence != sentence.end()){
                                                        if(toKeyword(*posSentence) == COL){
                                                            posSentence++; //elimina riga dove elemento colonna nome_colonna
                                                            if(posSentence != sentence.end()){
                                                                nameCol = *posSentence;
                                                                posSentence++; //elimina riga dove elemento colonna nome_colonna <>
                                                                if(posSentence != sentence.end()){
                                                                    sign = *posSentence;
                                                                    posSentence++;
                                                                    if(posSentence != sentence.end()){
                                                                        valToFind = *posSentence;
                                                                        try{
                                                                            switch(toOperator(sign)){
                                                                                case INCREASING:
                                                                                    std::cout << "Operatore invalido" << std::endl;
                                                                                    statusOk = false;
                                                                                    break;
                                                                                case DECREASING:
                                                                                    std::cout << "Operatore invalido" << std::endl;
                                                                                    statusOk = false;
                                                                                    break;
                                                                                case GREATER:
                                                                                    s = 'g';
                                                                                    database1.deleteRowWhereElementIs(nameTab, nameCol, valToFind, s);
                                                                                    posSentence++;
                                                                                    break;
                                                                                case LOWER:
                                                                                    s = 'l';
                                                                                    database1.deleteRowWhereElementIs(nameTab, nameCol, valToFind, s);
                                                                                    posSentence++;
                                                                                    break;
                                                                                case EQUAL:
                                                                                    if(database1.elemIsPresent(nameTab, nameCol, valToFind)){
                                                                                        s = 'e';
                                                                                        database1.deleteRowWhereElementIs(nameTab, nameCol, valToFind, s);
                                                                                        posSentence++;
                                                                                    } else {
                                                                                        std::cout << "Elemento " << valToFind << " non presente" << std::endl;
                                                                                        statusOk = false;
                                                                                    }
                                                                                    break;
                                                                                case BETWEEN:
                                                                                    s = 'i';
                                                                                    posSentence++;
                                                                                    if(posSentence != sentence.end()){
                                                                                        valToFind2 = *posSentence;
                                                                                        database1.deleteRowWhereElementIs(nameTab, nameCol, valToFind, valToFind2, s);
                                                                                        posSentence++;
                                                                                    } else {
                                                                                        std::cout << "Parametro mancante: secondo elemento" << std::endl;
                                                                                        statusOk = false;
                                                                                    }
                                                                                    break;
                                                                                case OUTSIDE:
                                                                                    s = 'o';
                                                                                    posSentence++;
                                                                                    if(posSentence != sentence.end()){
                                                                                        valToFind2 = *posSentence;
                                                                                        database1.deleteRowWhereElementIs(nameTab, nameCol, valToFind, valToFind2, s);
                                                                                        posSentence++;
                                                                                    } else {
                                                                                        std::cout << "Parametro mancante: secondo elemento" << std::endl;
                                                                                        statusOk = false;
                                                                                    }
                                                                                    break;
                                                                                case NVOP:
                                                                                    std::cout << "Operatore " << *posSentence << " sconosciuto" << std::endl;
                                                                                    statusOk = false;
                                                                                default:
                                                                                    statusOk = false;
                                                                                    break;
                                                                            }
                                                                        } catch(std::invalid_argument &ex){
                                                                            std::cout << ex.what() << std::endl;
                                                                            statusOk = false;
                                                                        }
                                                                    } else {
                                                                        std::cout << "Parametro mancante: valore elemento" << std::endl;
                                                                        statusOk = false;
                                                                    }
                                                                } else {
                                                                    std::cout << "Parametro mancante: operatore" << std::endl;
                                                                    statusOk = false;
                                                                }
                                                            } else {
                                                                std::cout << "Parametro mancante: nome colonna" << std::endl;
                                                                statusOk = false;
                                                            }
                                                        } else if((toKeyword(*posSentence) != COL) && (toKeyword(*posSentence) != NVKEY)){
                                                            std::cout << "Parola chiave " << *posSentence << " non valida" << std::endl;
                                                            statusOk = false;
                                                        } else {
                                                            std::cout << "Parola chiave " << *posSentence << " sconosciuta" << std::endl;
                                                            statusOk = false;
                                                        }
                                                    } else {
                                                        std::cout << "Parametro mancante: colonna" << std::endl;
                                                        statusOk = false;
                                                    }
                                                } else if((toKeyword(*posSentence) != ELEMENT) && (toKeyword(*posSentence) != NVKEY)){
                                                    std::cout << "Parola chiave " << *posSentence << " non valida" << std::endl;
                                                    statusOk = false;
                                                } else {
                                                    std::cout << "Parola chiave " << *posSentence << " sconosciuta" << std::endl;
                                                    statusOk = false;
                                                }
                                            } else {
                                                std::cout << "Parametro mancante: 'elemento'" << std::endl;
                                                statusOk = false;
                                            }
                                        } else if((toKeyword(*posSentence) != WHERE) && (toKeyword(*posSentence) != NVKEY)){
                                            std::cout << "Parola chiave " << *posSentence << " non valida" << std::endl;
                                            statusOk = false;
                                        } else {
                                            std::cout << "Parola chiave " << *posSentence << " sconosciuta" << std::endl;
                                            statusOk = false;
                                        }
                                    } else {
                                        std::cout << "Parametro mancante: 'dove'" << std::endl;
                                        statusOk = false;
                                    }
                                } else {
                                    std::cout << "Nessuna tabella selezionata" << std::endl;
                                    statusOk = false;
                                }
                                break;
                            case ELEMENT:
                                //cancella elemento elem1 eleme2
                                if(!nameCol.empty()){
                                    posSentence++;
                                    if(posSentence != sentence.end()){
                                        try{
                                            while(posSentence != sentence.end()){
                                                valToDelete = *posSentence;
                                                database1.deleteElement(nameTab, nameCol, valToDelete);
                                                posSentence++;
                                            }
                                        } catch(std::invalid_argument &ex){
                                            std::cout << ex.what() << std::endl;
                                            statusOk = false;
                                        }
                                    } else {
                                        std::cout << "Parametro mancante: valore elemento" << std::endl;
                                        statusOk = false;
                                    }
                                } else {
                                    std::cout << "Nessuna colonna selezionata" << std::endl;
                                    statusOk = false;
                                }
                                break;
                            case NAME:
                                std::cout << "Impossibile cancellare un singolo nome" << std::endl;
                                statusOk = false;
                                break;
                            case WHERE:
                                std::cout << "Impossibile cancellare 'dove'" << std::endl;
                                statusOk = false;
                                break;
                            case NVKEY:
                                std::cout << "Parola chiave " << *posSentence << " sconosciuta" << std::endl;
                                statusOk = false;
                                break;
                            default:
                                statusOk = false;
                                break;
                        }
                    } else {
                        std::cout << "Nessun parametro per il comando cancella" << std::endl;
                        statusOk = false;
                    }
                    break;
                case UPDATE:
                    posSentence++;
                    if(posSentence != sentence.end()){
                        switch(toKeyword(*posSentence)){
                            case DATAB:
                                std::cout << "Impossibile aggiornare database" << std::endl;
                                statusOk = false;
                                break;
                            case TAB:
                                posSentence++;
                                if(posSentence != sentence.end()){
                                    while(posSentence != sentence.end()){
                                        nameTab = *posSentence;
                                        posSentence++;
                                        if(posSentence != sentence.end()){
                                            newTab = *posSentence;
                                            database1.updateTab(nameTab, newTab);
                                            posSentence++;
                                        } else {
                                            std::cout << "Parametro mancante: nuovo nome da aggiornare" << std::endl;
                                            statusOk = false;
                                        }
                                    }
                                } else {
                                    std::cout << "Parametro mancante: tabella da aggiornare" << std::endl;
                                    statusOk = false;
                                }
                                break;
                            case COL:
                                //aggiorna colonna test val1 val2
                                if(!nameTab.empty()){
                                    posSentence++;
                                    if(posSentence != sentence.end()){
                                        nameCol = *posSentence;
                                        if(database1.colIsPresent(nameTab, nameCol)){
                                            posSentence++;
                                            if(posSentence != sentence.end()){
                                                database1.flushColumnWhereTabIs(nameTab, nameCol);
                                                while(posSentence != sentence.end()){
                                                    valToInsert = *posSentence;
                                                    database1.updateColumnVals(nameTab, nameCol, valToInsert);
                                                    posSentence++;
                                                }
                                                database1.fillFieldsOf(nameTab);
                                            } else {
                                                std::cout << "Parametro mancante: valori da aggiornare" << std::endl;
                                                statusOk = false;
                                            }
                                        } else {
                                            std::cout << "Colonna " << nameCol << " non presente" << std::endl;
                                            statusOk = false;
                                        }
                                    } else {
                                        std::cout << "Parametro mancante: colonna da aggiornare" << std::endl;
                                        statusOk = false;
                                    }
                                } else {
                                    std::cout << "Nessuna tabella selezionata" << std::endl;
                                    statusOk = false;
                                }
                                break;
                            case ROW:
                                //aggiorna riga dove elemento colonna test = val
                                if(!nameTab.empty()){
                                    posSentence++;
                                    if(posSentence != sentence.end()){
                                        if(toKeyword(*posSentence) == WHERE){
                                            posSentence++;
                                            if(posSentence != sentence.end()){
                                                if(toKeyword(*posSentence) == ELEMENT){
                                                    posSentence++;
                                                    if(posSentence != sentence.end()){
                                                        if(toKeyword(*posSentence) == COL){
                                                            posSentence++;
                                                            if(posSentence != sentence.end()){
                                                                nameCol = *posSentence;
                                                                posSentence++;
                                                                if(posSentence != sentence.end()){
                                                                    if(toOperator(*posSentence) == EQUAL){
                                                                        posSentence++;
                                                                        if(posSentence != sentence.end()){
                                                                            valToFind = *posSentence;
                                                                            posSentence++;
                                                                            try{
                                                                                if(database1.elemIsPresent(nameTab, nameCol, valToFind)){
                                                                                    s = 'e';
                                                                                    std::cout << "Riga selezionata:" << std::endl;
                                                                                    database1.printTabWhereElementIs(nameTab, nameCol, valToFind, s);
                                                                                    std::cout << "Riga da inserire:" << std::endl;
                                                                                    std::getline(std::cin, rowLine);
                                                                                    rowVals = splitWords(rowLine, delim);
                                                                                    if(rowVals.size() < database1.getTabSize(nameTab)){
                                                                                        std::cout << "Numero elementi da inserire minore del numero di colonne" << std::endl;
                                                                                        statusOk = false;
                                                                                    } else if(rowVals.size() > database1.getTabSize(nameTab)) {
                                                                                        std::cout << "Numero elementi da inserire maggiore del numero di colonne" << std::endl;
                                                                                        statusOk = false;
                                                                                    } else {
                                                                                        database1.updateTabRowWhere(nameTab, nameCol, valToFind, rowVals, s);
                                                                                    }
                                                                                    rowVals.clear();
                                                                                    rowLine.clear();
                                                                                } else {
                                                                                    std::cout << "Elemento " << valToFind << " non presente" << std::endl;
                                                                                    statusOk = false;
                                                                                }
                                                                            } catch(std::invalid_argument &ex){
                                                                                std::cout << ex.what() << std::endl;
                                                                                statusOk = false;
                                                                            }
                                                                        } else {
                                                                            std::cout << "Parametro mancante: valore elemento" << std::endl;
                                                                            statusOk = false;
                                                                        }
                                                                    } else if((toOperator(*posSentence) != EQUAL) && (toOperator(*posSentence) != NVOP)) {
                                                                        std::cout << "Operatore " << *posSentence << " non valido" << std::endl;
                                                                        statusOk = false;
                                                                    } else {
                                                                        std::cout << "Operatore " << *posSentence << " sconosciuto" <<std::endl;
                                                                        statusOk = false;
                                                                    }
                                                                } else {
                                                                    std::cout << "Parametro mancante: operatore" << std::endl;
                                                                    statusOk = false;
                                                                }
                                                            } else {
                                                                std::cout << "Parametro mancante: nome colonna" << std::endl;
                                                                statusOk = false;
                                                            }
                                                        } else if((toKeyword(*posSentence) != COL) && (toKeyword(*posSentence) != NVKEY)){
                                                            std::cout << "Parola chiave " << *posSentence << " non valida" << std::endl;
                                                            statusOk = false;
                                                        } else {
                                                            std::cout << "Parola chiave " << *posSentence << " sconosciuta" << std::endl;
                                                            statusOk = false;
                                                        }
                                                    } else {
                                                        std::cout << "Parametro mancante: colonna" << std::endl;
                                                        statusOk = false;
                                                    }
                                                } else if((toKeyword(*posSentence) != ELEMENT) && (toKeyword(*posSentence) != NVKEY)){
                                                    std::cout << "Parola chiave " << *posSentence << " non valida" << std::endl;
                                                    statusOk = false;
                                                } else {
                                                    std::cout << "Parola chiave " << *posSentence << " sconosciuta" << std::endl;
                                                    statusOk = false;
                                                }
                                            } else {
                                                std::cout << "Parametro mancante: elemento" << std::endl;
                                                statusOk = false;
                                            }
                                        } else if((toKeyword(*posSentence) != WHERE) && (toKeyword(*posSentence) != NVKEY)){
                                            std::cout << "Parola chiave " << *posSentence << " non valida" << std::endl;
                                            statusOk = false;
                                        } else {
                                            std::cout << "Parola chiave " << *posSentence << " sconosciuta" << std::endl;
                                            statusOk = false;
                                        }
                                    } else {
                                        std::cout << "Parametro mancante: dove" << std::endl;
                                        statusOk = false;
                                    }
                                } else {
                                    std::cout << "Nessuna tabella selezionata" << std::endl;
                                    statusOk = false;
                                }
                                break;
                            case ELEMENT:
                                //aggiorna elemento x newElem
                                //controllo su newElem present
                                if(!nameCol.empty()){
                                    posSentence++;
                                    if(posSentence != sentence.end()){
                                        valToFind = *posSentence;
                                        try{
                                            if(database1.elemIsPresent(nameTab, nameCol, valToFind)){
                                                posSentence++;
                                                if(posSentence != sentence.end()){
                                                    valToInsert = *posSentence;
                                                    database1.updateColumnElem(nameTab, nameCol, valToFind, valToInsert);
                                                    posSentence++;
                                                } else {
                                                    std::cout << "Parametro mancante: elemento da sostituire" << std::endl;
                                                    statusOk = false;
                                                }
                                            } else {
                                                std::cout << "Elemento " << valToFind << " non presente" << std::endl;
                                                statusOk = false;
                                            }
                                        } catch(std::invalid_argument &ex){
                                            std::cout << ex.what() << std::endl;
                                            statusOk = false;
                                        }
                                    } else {
                                        std::cout << "Parametro mancante: elemento da aggiornare" << std::endl;
                                        statusOk = false;
                                    }
                                } else {
                                    std::cout << "Nessuna colonna selezionata" << std::endl;
                                    statusOk = false;
                                }
                                break;
                            case NAME:
                                //aggiorna il nome di una colonna
                                //aggiorna nome colonna test1 test2 esempio1 esempio2
                                if(!nameTab.empty()){
                                    posSentence++;
                                    if(posSentence != sentence.end()){
                                        if(toKeyword(*posSentence) == COL){
                                            posSentence++;
                                            if(posSentence != sentence.end()){
                                                while(posSentence != sentence.end()){
                                                    nameCol = *posSentence;
                                                    posSentence++;
                                                    if(posSentence != sentence.end()){
                                                        newCol = *posSentence;
                                                        database1.updateColName(nameTab, nameCol, newCol);
                                                        posSentence++;
                                                    } else {
                                                        std::cout << "Parametro mancante: nuovo nome colonna" << std::endl;
                                                        statusOk = false;
                                                    }
                                                }
                                            } else {
                                                std::cout << "Parametro mancante: nome colonna" << std::endl;
                                                statusOk = false;
                                            }
                                        } else if((toKeyword(*posSentence) != COL) && (toKeyword(*posSentence) != NVKEY)){
                                            std::cout << "Parola chiave " << *posSentence << " non valida" << std::endl;
                                            statusOk = false;
                                        } else {
                                            std::cout << "Parola chiave " << *posSentence << " sconosciuta" << std::endl;
                                            statusOk = false;
                                        }
                                    } else {
                                        std::cout << "Parametro mancante: colonna" << std::endl;
                                        statusOk = false;
                                    }
                                } else {
                                    std::cout << "Nessuna tabella selezionata" << std::endl;
                                    statusOk = false;
                                }
                                break;
                            case WHERE:
                                std::cout << "Impossibile aggiornare 'dove'" << std::endl;
                                statusOk = false;
                                break;
                            case NVKEY:
                                std::cout << "Parola chiave " << *posSentence << " sconosciuta" << std::endl;
                                statusOk = false;
                                break;
                            default:
                                statusOk = false;
                                break;
                        }
                    } else {
                        std::cout << "Nessun parametro per il comando aggiorna" << std::endl;
                        statusOk = false;
                    }
                    break;
                case CREATE:
                    posSentence++;
                    if(posSentence != sentence.end()){
                        switch(toKeyword(*posSentence)){
                            case DATAB:
                                std::cout << "Impossibile creare un database: gia esistente" << std::endl;
                                statusOk = false;
                                break;
                            case TAB:
                                posSentence++;
                                if(posSentence != sentence.end()){
                                    while(posSentence != sentence.end()){
                                        newTab = *posSentence;
                                        database1.reserveSpace(newTab, TABLE());
                                        posSentence++;
                                    }
                                } else {
                                    std::cout << "Parametro mancante: nome tabella" << std::endl;
                                    statusOk = false;
                                }
                                break;
                            case COL:
                                if(!nameTab.empty()){
                                    posSentence++; //crea colonna esempio tipo, esempio2 tipo2
                                    if(posSentence != sentence.end()){
                                        while(posSentence != sentence.end()){
                                            newCol = *posSentence;
                                            posSentence++;
                                            if(posSentence != sentence.end()){
                                                newType = *posSentence;
                                                database1.getTab(nameTab).reserveSpace(newCol, newType);
                                                posSentence++;
                                            } else {
                                                std::cout << "Parametro mancante: tipo colonna per colonna '" << newCol << "'" << std::endl;
                                                statusOk = false;
                                            }
                                        }
                                    } else {
                                        std::cout << "Parametro mancante: nome colonna" << std::endl;
                                        statusOk = false;
                                    }
                                } else {
                                    std::cout << "Nessuna tabella selezionata" << std::endl;
                                    statusOk = false;
                                }
                                break;
                            case ROW:
                                if(!nameTab.empty()){
                                    posSentence++;
                                    if(posSentence == sentence.end()){
                                        std::cout << "Colonne tabella " << nameTab << " : ";
                                        database1.printFields(nameTab);
                                        std::cout << "Nuova riga per  " << nameTab << " : ";
                                        std::getline(std::cin, rowLine);
                                        rowVals = splitWords(rowLine, delim);
                                        if(rowVals.size() < database1.getTabSize(nameTab)){
                                            std::cout << "Numero elementi da inserire minore del numero di colonne" << std::endl;
                                            statusOk = false;
                                        } else if(rowVals.size() > database1.getTabSize(nameTab)){
                                            std::cout << "Numero elementi da inserire maggiore del numero di colonne" << std::endl;
                                            statusOk = false;
                                        } else {
                                            database1.insertRow(nameTab, rowVals);
                                        }
                                        rowVals.clear();
                                        rowLine.clear();
                                    } else {
                                        std::cout << "Parametri in eccesso per 'inserisci riga'" << std::endl;
                                        statusOk = false;
                                    }
                                } else {
                                    std::cout << "Nessuna tabella selezionata" << std::endl;
                                    statusOk = false;
                                }
                                break;
                            case ELEMENT:
                                if(!nameTab.empty()){
                                    if(!nameCol.empty()){
                                        posSentence++;
                                        if(posSentence != sentence.end()){
                                            try{
                                                foundExcp = 0;
                                                while(posSentence != sentence.end()){
                                                    valToInsert = *posSentence;
                                                    database1.insertLast(nameTab, nameCol, valToInsert);
                                                    posSentence++;
                                                    foundExcp++;
                                                }
                                            } catch(std::invalid_argument &ex){
                                                std::cout << ex.what() << std::endl;
                                                for(int i = 0; i < foundExcp; i++){
                                                    posSentence--;
                                                    database1.deleteElement(nameTab, nameCol, *posSentence);
                                                }
                                                statusOk = false;
                                            }
                                        } else {
                                            std::cout << "Parametro mancante: elemento" << std::endl;
                                            statusOk = false;
                                        }
                                    } else {
                                        std::cout << "Nessuna colonna selezionata" << std::endl;
                                        statusOk = false;
                                    }
                                } else {
                                    std::cout << "Nessuna tabella selezionata" << std::endl;
                                    statusOk = false;
                                }
                                break;
                            case NAME:
                                std::cout << "Impossibile creare nome" << std::endl;
                                statusOk = false;
                                break;
                            case WHERE:
                                std::cout << "Impossibile creare 'dove'" << std::endl;
                                statusOk = false;
                                break;
                            case NVKEY:
                                std::cout << "Parola chiave " << *posSentence << " sconosciuta" << std::endl;
                                statusOk = false;
                                break;
                            default:
                                statusOk = false;
                                break;
                        }
                    } else {
                        std::cout << "Nessun parametro per il comando crea" << std::endl;
                        statusOk = false;
                    }
                    break;
                case SAVE:
                    posSentence++;
                    if(posSentence != sentence.end()){
                        switch(toKeyword(*posSentence)){
                            case DATAB:
                                posSentence++;
                                if(posSentence == sentence.end()){
                                    fptr.open("Save_file.txt", std::ios::in | std::ios::out);
                                    fptr_tmp.open("Temp_file.txt", std::ios::in | std::ios::out | std::ios::trunc);
                                    if(fptr.is_open() && fptr_tmp.is_open()){
                                        database1.saveDatabase(fptr, fptr_tmp);
                                    } else {
                                        std::cout << "Files not opened" << std::endl;
                                        statusOk = false;
                                    }
                                    fptr.close();
                                    fptr_tmp.close();
                                    if(std::remove("Save_file.txt") == 0){
                                        if(std::rename("Temp_file.txt", "Save_file.txt") != 0){
                                            std::cout << "Error in renaming file" << std::endl;
                                            statusOk = false;
                                        }
                                    } else {
                                        std::cout << "Error in deleting file" << std::endl;
                                        statusOk = false;
                                    }
                                } else {
                                    std::cout << "Impossibile inserire piu di un parametro" << std::endl;
                                    statusOk = false;
                                }
                                break;
                            case TAB:
                                posSentence++;
                                if(posSentence != sentence.end()){
                                    while(posSentence != sentence.end()){
                                        if(database1.tabIsPresent(*posSentence)){
                                            tabsToSave.push_back(*posSentence);
                                        } else {
                                            std::cout << "Tabella " << *posSentence << " non presente" << std::endl;
                                        }
                                        posSentence++;
                                    }
                                    fptr.open("Save_file.txt", std::ios::in | std::ios::out);
                                    fptr_tmp.open("Temp_file.txt", std::ios::in | std::ios::out | std::ios::trunc);
                                    if(fptr.is_open() && fptr_tmp.is_open()){
                                        database1.saveTabs(fptr, fptr_tmp, tabsToSave);
                                    } else {
                                        std::cout << "Files not opened" << std::endl;
                                        statusOk = false;
                                    }
                                    fptr.close();
                                    fptr_tmp.close();
                                    if(std::remove("Save_file.txt") == 0){
                                        if(std::rename("Temp_file.txt", "Save_file.txt") != 0){
                                            std::cout << "Error in renaming file" << std::endl;
                                            statusOk = false;
                                        }
                                    } else {
                                        std::cout << "Error in deleting file" << std::endl;
                                        statusOk = false;
                                    }
                                    tabsToSave.clear();
                                } else {
                                    std::cout << "Parametro mancante: nome tabella" << std::endl;
                                    statusOk = false;
                                }
                                break;
                            case COL:
                                std::cout << "Impossibile salvare una singola colonna" << std::endl;
                                statusOk = false;
                                break;
                            case ROW:
                                std::cout << "Impossibile salvare una riga" << std::endl;
                                statusOk = false;
                                break;
                            case ELEMENT:
                                std::cout << "Impossibile salvare una singola colonna" << std::endl;
                                statusOk = false;
                                break;
                            case NAME:
                                std::cout << "Impossibile salvare un singolo nome" << std::endl;
                                statusOk = false;
                                break;
                            case WHERE:
                                std::cout << "Impossibile salvare 'dove'" << std::endl;
                                statusOk = false;
                                break;
                            case NVKEY:
                                std::cout << "Parola chiave " << *posSentence << " sconosciuta" << std::endl;
                                statusOk = false;
                                break;
                            default:
                                statusOk = false;
                                break;
                        }
                    } else {
                        std::cout << "Nessun parametro per il comando salva" << std::endl;
                        statusOk = false;
                    }
                    break;
                case LOAD:
                    posSentence++;
                    if(posSentence != sentence.end()){
                        switch(toKeyword(*posSentence)){
                            case DATAB:
                                posSentence++;
                                if(posSentence == sentence.end()){
                                    fptr.open("Save_file.txt", std::ios::in);
                                    if(fptr.is_open()){
                                        database1.loadDatabase(fptr);
                                    } else {
                                        std::cout << "Error in opening the file" << std::endl;
                                        statusOk = false;
                                    }
                                    fptr.close();
                                } else {
                                    std::cout << "Impossibile inserire piu di un parametro" << std::endl;
                                    statusOk = false;
                                }
                                break;
                            case TAB:
                                posSentence++;
                                if(posSentence != sentence.end()){
                                    while(posSentence != sentence.end()){
                                        if(!database1.tabIsPresent(*posSentence)){
                                            tabsToLoad.push_back(*posSentence);
                                        } else {
                                            std::cout << "Tabella gia presente in database" << std::endl;
                                        }
                                        posSentence++;
                                    }
                                    fptr.open("Save_file.txt", std::ios::in);
                                    if(fptr.is_open()){
                                        database1.loadTabs(fptr, tabsToLoad);
                                    } else {
                                        std::cout << "Error in opening file" << std::endl;
                                        statusOk = false;
                                    }
                                    fptr.close();
                                    tabsToLoad.clear();
                                } else {
                                    std::cout << "Parametro mancante: nome tabella" << std::endl;
                                    statusOk = false;
                                }
                                break;
                            case COL:
                                std::cout << "Impossibile caricare una singola colonna" << std::endl;
                                statusOk = false;
                                break;
                            case ROW:
                                std::cout << "Impossibile caricare una singola riga" << std::endl;
                                statusOk = false;
                                break;
                            case ELEMENT:
                                std::cout << "Impossibile caricare una singolo elemento" << std::endl;
                                statusOk = false;
                                break;
                            case NAME:
                                std::cout << "Impossibile caricare un singolo nome" << std::endl;
                                statusOk = false;
                                break;
                            case WHERE:
                                std::cout << "Impossibile salvare 'dove'" << std::endl;
                                statusOk = false;
                                break;
                            case NVKEY:
                                std::cout << "Parola chiave " << *posSentence << " sconosciuta" << std::endl;
                                statusOk = false;
                                break;
                            default:
                                statusOk = false;
                                break;
                        }
                    } else {
                        std::cout << "Nessun parametro per il comando carica" << std::endl;
                        statusOk = false;
                    }
                    break;
                case QUIT:
                    quitProgram = true;
                    break;
                default:
                    statusOk = false;
                    break;
            }
        }
    }
    std::cout << "Chiusura programma effettuata con successo";
    return 0;
}

std::vector<std::string> splitWords(std::string& line, std::string& toDelim){
    std::vector<std::string> toReturn;
    std::string word;
    size_t pos = 0;
    do{
        pos = line.find(toDelim);
        word = line.substr(0, pos);
        if(!word.empty()){ //same as pos != 0
            toReturn.push_back(word);
        }
        line.erase(0,pos + toDelim.length());
    } while(pos != std::string::npos);
    return toReturn;
}
