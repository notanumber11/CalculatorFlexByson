

#ifndef COMPILADORES_HASHTABLE_H_H
#define COMPILADORES_HASHTABLE_H_H


struct  entryStruct{
    char *lexema;
    int lexicalComponent;
    double var;
    double (*fnctptr)();
};


typedef struct entryStruct entrytable;

// IN ORDER TO PRINT THE NUMBER OF KEYWORDS IN THE TABLE
void setNumberOfKeyWords(int number);

void initTable(int size);

void deleteTable();

void display();

void insertItem(entrytable item);

entrytable *search(char lexema[256]);

int deleteItem(entrytable *item);

int sizeLexema(char* lexema);

#endif //COMPILADORES_HASHTABLE_H_H