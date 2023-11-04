//
// Created by user on 01.11.2023.
//

#ifndef EX3_MAP_H
#define EX3_MAP_H
#define MAX_SIZE                                           \
    100 // Maximum number of elements in the map
typedef struct Map{
    int size; // Current number of key1 in the map
    char keys[MAX_SIZE][3][100]; // Array to store the keys
    double values[MAX_SIZE][2];
    void (*print)(struct Map *);
    void (*insert)(char[],char[],char[],double ,struct Map *);
    int (*getIndex)(char [],char[],char[],struct Map *);
    void (*saveToFile)(char[],struct Map *);
} Map;
Map *new();
void insertMap(char[],char[],char[],double ,Map *);
int getIndexMap(char [],char[],char[],Map *);
void printMap(Map *);
void saveToFileMap(char [],Map *);

#endif //EX3_MAP_H
