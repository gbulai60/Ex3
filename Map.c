//
// Created by user on 01.11.2023.
//

#include "Map.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <conio.h>
Map *new(){
    Map *map = malloc(sizeof(Map));
    if (map == NULL) {
        fputs("Error: Out of memory\n", stderr);
        exit(1);
    }
    else {
        map->size = 0;
        map->insert = &insertMap;
        map->getIndex = &getIndexMap;
        map->print = &printMap;
        map->saveToFile=&saveToFileMap;
        return map;
    }
}
void saveToFileMap(char fileName[],Map *map){
    FILE *fptr;
    fptr = fopen(fileName,"w");
    if(fptr == NULL)
    {
        printf("Error opening the file!");
        getch();
        exit(1);
    }
    for (int i = 0; i < map->size; i++) {
        fprintf(fptr,"%s;%s;%03.0f;%012.3f\n", map->keys[i][0],map->keys[i][1],map->values[i][0],map->values[i][1]);
    }
    fclose(fptr);
}
void insertMap(char key1[],char key2[],char key3[],double value,Map *map){
    int index =map->getIndex(key1,key2,key3,map);
    if (index == -1) { // Key not found
        strcpy(map->keys[map->size][0], key1);
        strcpy(map->keys[map->size][1], key2);
        strcpy(map->keys[map->size][2], key3);
        map->values[map->size][0]=1;
        map->values[map->size][1] = value;
        map->size++;
    }
    else if(index >= MAX_SIZE) { // Key found
        map->values[index-MAX_SIZE][1]+= value;
        map->values[index-MAX_SIZE][0]++;
        strcpy(map->keys[index-MAX_SIZE][2], key3);
    }
    else if(index < MAX_SIZE && index > -1){
        map->values[index][1]+=value;
    }

}
int getIndexMap(char key1[],char key2[],char key3[],Map *map){
    if(map!=NULL) {
        for (int i = 0; i < map->size; i++)
        {
            if (strcmp(map->keys[i][0], key1) == 0 && strcmp(map->keys[i][1], key2) == 0  ) {
                if(strcmp(map->keys[i][2], key3) == 0) return i;
                else return i+MAX_SIZE;
            }
        }
    }
    return -1; // Key not found
}

void printMap(Map * map){
    for (int i = 0; i < map->size; i++) {
        printf("key:%s; key:%s; value1:%03.0f; value2:%012.3f\n", map->keys[i][0],map->keys[i][1],map->values[i][0],map->values[i][1]);
    }
}

