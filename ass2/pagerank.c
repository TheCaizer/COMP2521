//Jackie Cai z5259449
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "graph.h"
#include "readData.h"

#define MAX_CHAR 100

//Functions
double *calculatePageRank(GraphPointer g, double d, double diffPR, int maxIteration);
void order(double *pagerank, char **ListUrl, int out[], int length);

int main(int argc, char *argv[]) {
    // check for 4 arguments
    if(argc != 4){
        printf("You need 4 arguments you supplied %d" ,argc);
        return 0;
    }
    double d = atof(argv[1]);
    double diffPR = atof(argv[2]);
    int maxIterations = atoi(argv[3]);
    //copy paste the GetCollection() function to get the 
    //list and remember the position and hash of url names
    FILE *fp;
    char file[MAX_CHAR];
    char **ListUrl = NULL;
    int CountUrl = 0;
    int i;
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
    //create the graph of the url connections
    GraphPointer g = GetGraph();
    double *pointer = malloc(sizeof(double)*CountNodes(g));
    //calculate page rank and return array of pagerank
    pointer = calculatePageRank(g, d, diffPR, maxIterations);
    //get number of url outlink to print to the file of all nodes
    int OutLinks[CountUrl];
    i = 0;
    while(i < CountUrl){
        OutLinks[i] = PointOut(g, i);
        i++;
    }
    //call sort function to sort the pageRanks in descending order
    //as well write to the file
    order(pointer, ListUrl, OutLinks, CountUrl);
    return 0;
}
//function to calculate pageRank returns pointer to pagerank array
double *calculatePageRank(GraphPointer g, double d, double diffPR, int maxIteration) {
    int N = CountNodes(g);
    //type cast the N to convert int to double
    double Nfloat = (double)N;
    double *pageRank = malloc(sizeof(double)*N);
    //the PR(t) which is needed to calculate difference for diff
    double oldPR[N];
    int h = 0;
    int i;
    int j;
    int u; 
    int k;
    //change the PR to 1/N
    while(h < N){
        pageRank[h] = 1/Nfloat;
        h++;
    }

    int iterations = 0;
    double diff = diffPR; 
    double sumPJ = 0; 
    double wIn = 0;
    double wOut = 0;
    double newDiff = 0; 
    //using the formula in the assignment spec
    while(iterations < maxIteration && diff >= diffPR){
        //reset the new diff value every iteration
        newDiff = 0;
        //upadte the oldPR to caluclate the new diff by
        //finding difference in oldPR and the pagerank
        u = 0;
        while(u < N){
            oldPR[u] = pageRank[u];
            u++;
        }
        i = 0;
        //iterate through the whole urls
        while(i < N){
            //reset the sum of the PJ for every node
            sumPJ = 0; 
            j = 0;
            while(j < N){
                //check if the url j and url i are connected
                //if they are then find the wIN and wOut
                //calculate according to formula
                if(CheckConnect(g, j, i)){
                    wIn = PointTo(g, i)/SumPointTo(g, j);
                    wOut = PointOut(g, i)/SumPointOut(g, j);
                    sumPJ = sumPJ + (oldPR[j]*wIn*wOut); 
                }
                j++;
            }
            pageRank[i] = ((1-d)/Nfloat)+(d*sumPJ);
            i++;
        }
        k = 0;
        while(k < N){
            //needed fabs to absolute a float value and calculate 
            //the new diff value needed for iteration end
            newDiff = newDiff + fabs(pageRank[k] - oldPR[k]);
            k++;
        }
        diff = newDiff;
        iterations++; 
    }
    return pageRank;
}
//sort the list and then print write to the file pageRankList.txt
//bubble sort credit to lecture code
void order(double *pagerank, char **ListUrl, int out[], int length){
    if(pagerank == NULL || ListUrl == NULL || out == NULL){
        printf("One of variables in order is NULL");
        exit(0);
    }
    int i = 0;
    double temp;
    int outTemp; 
    char *string;
    //bubble sort the pagerank in descending order
    while(i < length){
        int j = 0;
        while(j < length - i -1){
            //compares the next vale
            if(pagerank[j] < pagerank[j + 1]){
                //swap the pagerank value in descending order
                temp = pagerank[j];
                pagerank[j] = pagerank[j + 1];
                pagerank[j + 1] = temp;
                //swap the number of out links to make sure all values allign
                outTemp = out[j];
                out[j] = out[j + 1];
                out[j + 1] = outTemp;
                //swap the url names
                string = ListUrl[j];
                ListUrl[j] = ListUrl[j + 1];
                ListUrl[j + 1] = string;
            }
            j++;
        }
        i++;
    }
    //open file for writing
    FILE *fp = fopen("pagerankList.txt", "w");
    int k = 0; 
    //write to file the url name, the number of url out links and the pagerank
    while(k < length){
        fprintf(fp, "%s, %d, %.7f\n", ListUrl[k], out[k], pagerank[k]);
        k++;
    }
    //close file
    fclose(fp);
}
