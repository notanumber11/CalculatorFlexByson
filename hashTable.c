#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashTable.h"

entrytable** hashArray;
entrytable* dummyItem;
int elementsInTheTable;
int sizeTable = 0;
int numberOfKeyWords = 0;

void setNumberOfKeyWords(int number){
    numberOfKeyWords = number;
}

void deleteTable(){
    for(int i=0;i<sizeTable;i++){
        if(hashArray[i] != NULL && hashArray[i]->lexema!=NULL){
            free(hashArray[i]->lexema);
            free(hashArray[i]);
        }
    }
    free(dummyItem->lexema);
    free(dummyItem);
    free(hashArray);
}

void recolocateTable(){
    entrytable** temp = hashArray;
    sizeTable = sizeTable*2;
    hashArray = (entrytable**) malloc(sizeof(entrytable*)*sizeTable);
    for(int i=0;i<sizeTable;i++){
        hashArray[i] = NULL;
    }
    elementsInTheTable = 0;
    for(int i = 0; i < sizeTable/2 ; i++){
        if(temp[i] != NULL && temp[i]->lexema!=NULL){
            insertItem(*temp[i]);
            free(temp[i]->lexema);
            free(temp[i]);
        }
    }
    free(temp);
}

void initTable(int size){
    sizeTable = size;
    dummyItem = (entrytable*) malloc(sizeof(entrytable));
    hashArray = (entrytable**) malloc(sizeof(entrytable*)*sizeTable);
    dummyItem->lexema = (char*)malloc(sizeof(char)*24);
    dummyItem->lexema = NULL;
    for(int i=0;i<sizeTable;i++){
        hashArray[i] = NULL;
    }
    elementsInTheTable = 0;
}

unsigned long
hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}


unsigned long hashCode(unsigned char *str){
    return hash(str)%sizeTable;
}

entrytable *search(char lexema[256]){
    //get the hash
    unsigned long hashIndex = hashCode(lexema);

    //move in array until an empty
    while(hashArray[hashIndex] != NULL){

        if(strcmp(hashArray[hashIndex]->lexema,lexema)==0)
            return hashArray[hashIndex];

        //go to next cell
        ++hashIndex;

        //wrap around the table
        hashIndex %= sizeTable;
    }

    return NULL;
}


void insertItem(entrytable itemInsert){

    if(elementsInTheTable>=(int)(100*sizeTable)){
        recolocateTable();
    }
    entrytable *item = (entrytable*) malloc(sizeof(entrytable));
    item->lexema = (char*)malloc(sizeof(char)*sizeLexema(itemInsert.lexema));
    strcpy(item->lexema,itemInsert.lexema);
    item->lexicalComponent = itemInsert.lexicalComponent;
    item->var = itemInsert.var;
    item->fnctptr = itemInsert.fnctptr;
    //get the hash
    unsigned long hashIndex = hashCode(item->lexema);

    //move in array until an empty or deleted cell
    while(hashArray[hashIndex] != NULL && hashArray[hashIndex]->lexema != NULL){
        //go to next cell
        ++hashIndex;
        //wrap around the table
        hashIndex %= sizeTable;
    }
    elementsInTheTable++;
    hashArray[hashIndex] = item;
}

int deleteItem(entrytable *item){
    char * lexema = item->lexema;

    //get the hash
    unsigned long  hashIndex = hashCode(item->lexema);

    //move in array until an empty
    while(hashArray[hashIndex] != NULL){

        if(strcmp(hashArray[hashIndex]->lexema,lexema)==0){
            free(hashArray[hashIndex]->lexema);
            free(hashArray[hashIndex]);
            elementsInTheTable--;
            //assign a dummy item at deleted position
            hashArray[hashIndex] = dummyItem;
            return 1;
        }

        //go to next cell
        ++hashIndex;

        //wrap around the table
        hashIndex %= sizeTable;
    }

    return 0;
}

void display(){

    int i = 0;
    printf("\n -----------  Hashtable ---------------\n");


    for(i = 0; i<sizeTable; i++) {

        if(hashArray[i] != NULL){
            printf(" \n[ %d ] -- [ %s ] = [ %f ]",hashArray[i]->lexicalComponent,hashArray[i]->lexema,hashArray[i]->var);
            // printf(" (Componente lexico [ %d ] , Lexema = [ %s ],  Lineas [ %d ])",hashArray[i]->lexicalComponent,hashArray[i]->lexema, hashArray[i]->lines[0]);
        }
        else{
           // printf("\n ~~ ");
        }
    }


   // printf("\n\n  -- Elements [ %d ] -- KeyWords [ %d ] -- Identifiers [ %d ] -- \n ",elementsInTheTable,numberOfKeyWords,elementsInTheTable-numberOfKeyWords);

    printf("\n");
}

int sizeLexema(char* lexema){
    int i= 0;
    while(lexema[i]!='\0'){
        i++;
    }
    return i;
}