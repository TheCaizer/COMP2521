//Jackie Cai z5259449
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "graph.h"
#include "readData.h"

#define MAX_CHAR 100
//function to build graph from collection.txt
//combined both function GetCollection and
//GetGraph since cant return array
GraphPointer GetGraph(){
    //open collection
    FILE *fp;
    char file[MAX_CHAR];
    char temp[MAX_CHAR];
    char check[3] = "url";
    char URL[MAX_CHAR]; 
    char extension[MAX_CHAR] = ".txt";
    char **ListUrl = NULL;
    int CountUrl = 0;
    int i = 0;
    fp = fopen("collection.txt", "r");
    //get a set(list) of url in collection.txt
    while(fscanf(fp, "%s", file) != EOF){
        //continue increasing the size of array while scanning
        ListUrl = realloc(ListUrl, (CountUrl+1)*sizeof(char*));
        //malloc a string into the array and copy into the array
        ListUrl[CountUrl] = malloc(strlen(file)+1);
        //as well as counting the number of url vertices needed
        strcpy(ListUrl[CountUrl++], file);
    }
    //close file
    fclose(fp);
    //create new graph with number of url as the nV
    GraphPointer g = createGraph(CountUrl);
    //open url and attach graph with the url they contain
    while(i < CountUrl){
        //copy the url name to another string and then append
        //the .txt to the url
        strcpy(URL, ListUrl[i]);
        char *txt = strcat(URL, extension);
        fp = fopen(txt, "r");
        while(fscanf(fp, "%s", temp)!=EOF){
            //check the word starts with url since we are looking for url
            if(prefix(check, temp) == 0){
                //check that the url itself is not a self vertice
                if(strcmp(URL, temp) != 0){
                    int w = GetHash(temp, CountUrl, ListUrl);
                    newEdge(g, i, w, 1);
                }
            }
        }
        //close file
        fclose(fp);
        i++;
    }
    return g;
}
//compares the url name and then returns the hash of the url in order to put into
//the graph in the right order of v,w edge
int GetHash(char *name, int length, char **ListUrl){
    int i = 0;
    while(i < length){
        //loop through the list of url and find the hash
        //of the url and return it
        if(strcmp(name, ListUrl[i]) == 0){
            return i; 
        }
        i++;
    }
    return 0; 
}
//Check if the words start with the string "url"
int prefix(const char *pre, const char *str){
    return strncmp(pre, str, 3);
}