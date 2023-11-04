#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <conio.h>
#include "Map.h"
enum sortBy{
    codBanca,codFiliala,codClient
};

typedef struct Operatiune{
    char codBanca[6];
    char codFiliala[4];
    char codClient[11];
    char dataOperatiune[11];
    double sumaOperatiune;
    struct Operatiune *next;
}Operatiune;

void copyUntilSeparator(const char *source, char *destination, int destinationSize, char separator){
    char *pozitieSeparator = strchr(source, separator);

    if (pozitieSeparator != NULL) {
        // Găsim separatorul în șir
        int indexSeparator = pozitieSeparator - source;
        if(indexSeparator<destinationSize){
            memmove(destination, source,  indexSeparator);
            destination[indexSeparator]='\0';
        }
        else{
            /*Dacă dimensiunea destinației e mai mica decât șirul până la separator
             * nu copiem nimic pentru a nu cauza deformarea în memorie a șirului inițial
             */
        }
    }
    else {
        // Dacă separatorul nu este găsit, șirul rămâne neschimbat
    }
}
void removeUntilSeparator(char *sir, char separator) {
    char *pozitieSeparator = strchr(sir, separator);
    if (pozitieSeparator != NULL) {
        // Găsim separatorul în șir
        int indexSeparator = pozitieSeparator - sir;
        memmove(sir, sir + indexSeparator + 1, strlen(sir) - indexSeparator);
    }
    else {
        // Dacă separatorul nu este găsit, șirul rămâne neschimbat
    }
}
void createOperation(const char codBanca[6],const char codFiliala[6], const char codClient[11], const  char dataOperatiune[11], const double sumaOperatiune, Operatiune **head) {
    Operatiune *node = malloc(sizeof(Operatiune));
    if (node == NULL) {
        fputs("Error: Out of memory\n", stderr);
        exit(1);
    } else {
        strcpy(node->codBanca, codBanca);
        strcpy(node->codFiliala, codFiliala);
        strcpy(node->codClient, codClient);
        strcpy(node->dataOperatiune, dataOperatiune);
        node->sumaOperatiune = sumaOperatiune;
        if (*head == NULL) {
            node->next = *head;
            *head = node;
        } else {
            Operatiune *iterr = *(head);
            while (iterr->next != NULL)
                iterr = iterr->next;
            iterr->next = node;
            node->next = NULL;


        }
    }
}
int parseFile(Operatiune **head){
    FILE *fptr;
    fptr = fopen("operations.txt","r");
    char operation[50];
    if(fptr == NULL)
    {
        printf("Error opening the file!");
        getch();
        exit(1);
    }
    char codBanca[6];
    char codFiliala[4];
    char codClient[11];
    char dataOperatiune[11];
    double sumaOperatiune;
    //Citim toate operațiunile din fișier
    while (fgets(operation, sizeof(operation), fptr)){
        if (operation[0] == '\r' || operation[0]=='\n') {
            continue; // Ignoră caracterul '\r' si '\n'
        }
        //Citim fiecare operațiune rând cu rând  în variabila operation apoi extragem din ea datele
        copyUntilSeparator(operation,codBanca,6,';');
        removeUntilSeparator(operation,';');
        copyUntilSeparator(operation,codFiliala,4,';');
        removeUntilSeparator(operation,';');
        copyUntilSeparator(operation,codClient,11,';');
        removeUntilSeparator(operation,';');
        copyUntilSeparator(operation,dataOperatiune,11,';');
        removeUntilSeparator(operation,';');
        //Facem replace la ',' în '.' pentru a putea parsa suma operațiunii
        char *pozitieSeparator = strchr(operation, ',');
        if (pozitieSeparator != NULL) {
            *pozitieSeparator='.';
        }
        sumaOperatiune = strtod(operation, '\0');
        createOperation(codBanca,codFiliala,codClient,dataOperatiune,sumaOperatiune,head);

    }
    fclose(fptr);
    return 0;

}
void print(Operatiune * head){
    int i=0;
    while(head!=NULL){
        printf("\n Opratiune %i ",++i);
        printf("\n Cod banca %s ",head->codBanca);
        printf("\n Cod filiala %s ",head->codFiliala);
        printf("\n Cod client %s ",head->codClient);
        printf("\n Data operatiune %s ",head->dataOperatiune);
        printf("\n Suma operatiune %.3f ",head->sumaOperatiune);
        printf("\n-----------------------------------------------------");
        head=head->next;
    }
}
void Swap(Operatiune * operatiune1, Operatiune *operatiune2)
{
    Operatiune aux;
    Operatiune *next1, *next2;
    next1=operatiune1->next;
    next2=operatiune2->next;
    aux=*operatiune1;
    *operatiune1=*operatiune2;
    *operatiune2=aux;
    operatiune1->next=next1;
    operatiune2->next=next2;
    return;
}
void sort(Operatiune * head,enum sortBy field){
    Operatiune *current = head, *index = NULL;
    if(head == NULL) {
        return ;
    }
    else {
        while(current != NULL) {
            index = current->next;
            while(index != NULL) {
                switch (field) {
                    case codClient:
                        if(strcmp(current->codClient,index->codClient)>0   ) {
                            Swap(current,index);
                        };break;
                    case codBanca:
                        if(strcmp(current->codBanca,index->codBanca)>0   ) {
                            Swap(current,index);
                        };break;
                    case codFiliala:
                        if(strcmp(current->codFiliala,index->codFiliala)>0   ) {
                            Swap(current,index);
                        };break;
                    default:
                        continue;

                }
                index = index->next;
            }
            current = current->next;
        }
    }
}
void writeToFileStatistics(Operatiune *head){

    Map *statistica=new();
    while(head!=NULL){
        statistica->insert(head->codBanca,head->codFiliala,head->codClient,head->sumaOperatiune,statistica);
        head=head->next;
    }
    statistica->print(statistica);
    statistica->saveToFile("output.txt",statistica);


}

int main() {
    Operatiune *head=NULL;
    parseFile(&head);
    print(head);
    getch();
    sort(head,codClient);
    sort(head,codFiliala);
    sort(head,codBanca);
    print(head);
    printf("\n");
    writeToFileStatistics(head);
    getch();
    return 0;
}
