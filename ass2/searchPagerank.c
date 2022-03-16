//Jackie Cai z5259449
//Program takes invertedIndex puts the url in an array
//and then sort and prints the array in descending order of PR
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX_CHAR 1000

//Functions
void findPagerank(char **arr, int length);
void removeComma(char *ch);
//
int main(int argc, char *argv[]) {
    if(argc == 1){
        printf("You didn't search for anything");
        return 0;
    }
    //declare and initialise variables/pointers
    int numWords = 0;
    char **ListWords = NULL;
    char **ListUrl = NULL;
    int numURLs = 0;
    char string[MAX_CHAR];
    char newLine[MAX_CHAR];
    int i = 0;
    int j = 0;
    int k;
    // read the comamnd line and put the into an array 
    // as well as comapring them to invertedindex.txt
    while(i < argc-1){
        FILE *fp = fopen("invertedIndex.txt", "r");
        //read the command line arguments into an array
        ListWords = realloc(ListWords, (numWords+1)*sizeof(char*));
        //argv i + 1 skips the function
        ListWords[numWords] = malloc(strlen(argv[i]) + 10);
        //copy the number of words into an array
        strcpy(ListWords[numWords++], argv[i+1]);
        //compares the array to every word in the invertedIndex
        while(fscanf(fp, "%s", string) != EOF){
            if(strcmp(ListWords[i], string) == 0){
                //breaks each line into a token of words
                //where string is the word, newLine is the tabs or space
                while(fscanf(fp, "%99s%99[ \t\n]", string, newLine) != EOF){
                    //puts the url into a list
                    ListUrl = realloc(ListUrl, (numURLs+1)*sizeof(char*));
                    //first url is always put into list
                    if(numURLs == 0){
                        ListUrl[numURLs] = malloc(strlen(string)+1);
                        strcpy(ListUrl[numURLs++], string);
                    }
                    //loops through the list to check if there are 
                    //any duplicate url
                    k = 0;
                    while(k < numURLs){
                        //if there are breaks the loop
                        if(strcmp(string, ListUrl[k]) == 0){
                            break;
                        }
                        k++;
                        //if end of list it adds the new url to the list
                        if(k == numURLs){
                            ListUrl[numURLs] = malloc(strlen(string)+1);
                            strcpy(ListUrl[numURLs++], string);
                        }
                    }
                    //if the newLine is a new line meaning next
                    //word breaks the loop and proceed to next word
                    if(strchr(newLine, '\n')){
                        break;
                    }
                }
            }
        }
        //close file
        fclose(fp);
        i++;
    }
    //sort the ListUrl in descending order depending
    //on the pagerank
    findPagerank(ListUrl, numURLs);
    //determine if there are less than 30 pages to print 
    if(numURLs < 30){
        while(j < numURLs){
            printf("%s\n", ListUrl[j]);
            j++;
        }
    }
    else{
        while(j < 30){
            printf("%s\n", ListUrl[j]);
            j++;
        }   
    }
    return 0;
}

//remove comma in front of the url in page rank
void removeComma(char *ch){
    int i;
    char *temp; 
    char *temp2;
    temp = temp2 = ch;
    while(*temp2){
        *temp = *temp2++;
        //skips the comma or space
        if(*temp != ','  && *temp != ' '){
            temp++;
        }
    }
    *temp = '\0'; 
}
//finds the pagerank of each url and sorts them into a list
//in descending order
void findPagerank(char **arr, int length){
    int i = 0;
    int j = 0;
    char string[MAX_CHAR];
    char newLine[MAX_CHAR];
    double *ListPR = malloc(sizeof(double)*length);
    int numPR = 0;
    double temp; 
    char *swap; 

    //finds the pr of url in pagerankList.txt
    while(i < length){
        FILE *pr = fopen("pagerankList.txt", "r");
        while(fscanf(pr, "%s", string) != EOF){
            //removes the comma in front of url name in pagerankList
            removeComma(string);
            //if URL is found, keep reading until pagerank is found
            if(strcmp(string, arr[i]) == 0){
                while (fscanf ( pr, "%99s%99[ \t\n]", string, newLine) != EOF){
                    //since the pr is next to a newline in the file search for the
                    //new line and copy the string next to it to the array
                    if(strchr(newLine, '\n')){
                        //convert string value of pagerank to float and store in ListPR
                        ListPR[numPR++] = atof(string);
                        break;
                    }
                }   
            }
        }
        i++;
    }
    //use same bubble sort in pagerank
    //copy and paste
    i = 0;
    while(i < numPR){
        int j = 0;
        while(j < numPR - i - 1){
            if(ListPR[j] < ListPR[j + 1]){
                temp = ListPR[j];
                ListPR[j] = ListPR[j + 1];
                ListPR[j + 1] = temp;
                swap = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = swap;  
            }
            j++;
        }
        i++;
    }
}
