//Jackie Cai z5259449
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "invertedIndex.h"

#define MAX_WORD 100
//Function Part 1
char *normaliseWord(char *str);
InvertedIndexBST generateInvertedIndex(char *collectionFilename);
void printInvertedIndex(InvertedIndexBST tree);
//Function Part 2
TfIdfList calculateTfIdf(InvertedIndexBST tree, char *searchWord, int D);
TfIdfList retrieve(InvertedIndexBST tree, char *searchWords[], int D);
//Other Functions
void normalWord(char *str);
char *readFile(char *collectionFilename);
InvertedIndexBST createIINode(char *Word);
FileList createLNode(char *FileName);
InvertedIndexBST createFirstNode(char *Word, char *FileName);
void checkFileName(InvertedIndexBST Tree, char *FileName, char *Word);
void InsertFileAlpha(InvertedIndexBST Tree, char *FileName);
int SearchTree(InvertedIndexBST Tree, char *Word);
InvertedIndexBST InsertTree(InvertedIndexBST Tree, char *Word, char *FileName);
void AdjustTF(char *FileName, int WordCount, InvertedIndexBST Tree);
void traverseInOrder(InvertedIndexBST tree);
InvertedIndexBST SearchTree2(InvertedIndexBST Tree, char *Word);
void testPrint(InvertedIndexBST tree);
int numberOfFiles(FileList list);
TfIdfList createtfidf(char *filename, double sum);
TfIdfList Inserttfidf(TfIdfList list, char *filename, double tfidf);
int checkFileList(TfIdfList list, char *filename, double tfidf);
void Sort(TfIdfList list);
void swapData(TfIdfList a, TfIdfList b);


//This function calls normalWord on string and tolower
//all the letters and returns the string back
char *normaliseWord(char *str){
    //normalises the word by removing white space and punctuation mark
    normalWord(str);
    //find length of string
    int length = strlen(str);
    int i = 0;
    //lower case the string
    while (i <= length)
    {
        str[i] = tolower(str[i]);
        i++;
    }
    return str;
}
//This function removes leading and trailing white space
//as well as remove punctuation marks at the end
void normalWord(char *str)
{
    int i = 0;
    int index = 0;
    //Checks for leading white space trails
    while (str[index] == ' ' || str[index] == '\t' || str[index] == '\n')
    {
        index++;
    }
    //replace the start with i which is the first letter
    while (str[i + index] != '\0')
    {
        str[i] = str[i + index];
        i++;
    }
    //sets the end to null terminator
    str[i] = '\0';
    i = 0;
    index = 0;
    //goes through the string until the end
    while (str[i] != '\0')
    {
        //goes through word until finds whitespace
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
        {
            index = i;
        }
        i++;
    }
    //replace the end with null terminator after the first white space unless puncuation mark is at the end
    if (str[index] == '.' || str[index] == '?' || str[index] == ';' || str[index] == ',')
    {
        str[index] = '\0';
    }
    else
    {
        str[index + 1] = '\0';
    }
}
//generates a inverted BST
InvertedIndexBST generateInvertedIndex(char *collectionFilename)
{
    FILE *fp;
    FILE *fp2;
    char file[MAX_WORD];
    char word[MAX_WORD];
    int FirstNode = 0;
    InvertedIndexBST head = NULL;

    // Opens files
    fp = fopen(collectionFilename, "r");
    // Scan the list of files
    while (fscanf(fp, "%s", file) != EOF)
    {
        //opens the file with the name
        fp2 = fopen(file, "r");
        //Count the number of words in the files
        int WordCount = 0;
        //loops through the words
        while (fscanf(fp2, "%s", word) != EOF)
        {
            normaliseWord(word);
            //if its the first node makes a new node
            //and initalises the head
            if (FirstNode == 0)
            {
                head = createFirstNode(word, file);
                FirstNode = 1;
            }
            else
            {
                int InTree = -1;
                //checks if the word is in the tree
                InTree = SearchTree(head, word);
                //if it is then check if the file is in the tree
                if (InTree == 1)
                {
                    //if it is add 1 to tf if not insert into filelist
                    checkFileName(head, file, word);
                }
                //If not in tree insert in tree
                else if (InTree == 0)
                {
                    InsertTree(head, word, file);
                }
            }
            WordCount++;
        }
        //Have to traverse through the tree and divide tf by WordCount
        AdjustTF(file, WordCount, head);
        //Close File
        fclose(fp2);
    }
    // Close the file
    fclose(fp);
    return head;
}
//Creates a InvertedIndex Node
InvertedIndexBST createIINode(char *Word)
{
    InvertedIndexBST new = malloc(sizeof(struct InvertedIndexNode));
    if (new == NULL)
    {
        printf("Not Enough Memory");
        return NULL;
    }
    char *copy = malloc(sizeof(char) * 1000);
    strcpy(copy, Word);
    new->word = copy;
    new->fileList = NULL;
    new->left = NULL;
    new->right = NULL;
    return new;
}
//Creates a FileList node
FileList createLNode(char *FileName)
{
    FileList new = malloc(sizeof(struct FileListNode));
    if (new == NULL)
    {
        printf("Not Enough Memory");
        return NULL;
    }
    char *copy = malloc(sizeof(char) * 1000);
    strcpy(copy, FileName);
    new->filename = copy;
    new->next = NULL;
    new->tf = 1.0;
    return new;
}
//Creates the first node of the list of text with both InvertedIndex and Filelist
InvertedIndexBST createFirstNode(char *Word, char *FileName)
{
    InvertedIndexBST node = createIINode(Word);
    FileList file = createLNode(FileName);
    node->fileList = file;
    return node;
}
//Check if the filename is in the linked list
void checkFileName(InvertedIndexBST Tree, char *FileName, char *Word)
{
    //search the tree for the word node
    InvertedIndexBST found = SearchTree2(Tree, Word);
    FileList curr = found->fileList;
    while (curr != NULL)
    {
        //In the file therefore add 1 to tf
        if (strcmp(FileName, curr->filename) == 0)
        {
            curr->tf = curr->tf + 1;
            return;
        }
        //Iterate through the list
        else
        {
            curr = curr->next;
        }
    }
    //If there is no file Insert into file alphabetically
    if (curr == NULL)
    {
        InsertFileAlpha(found, FileName);
    }
}
//If not in linked list insert aplhabetically
void InsertFileAlpha(InvertedIndexBST Tree, char *FileName)
{
    FileList new = createLNode(FileName);
    FileList curr = Tree->fileList;
    FileList prev = NULL;
    while (curr != NULL)
    {
        //if the first word is  in front of the filename
        if (strcmp(FileName, curr->filename) < 0 && prev == NULL)
        {
            //sets the new first one as new node
            Tree->fileList = new;
            //sets the next node as the linked list
            new->next = curr;
            return;
        }
        //found that curr is in front of the filename therefore insert between
        else if (strcmp(FileName, curr->filename) < 0 && prev != NULL)
        {
            prev->next = new;
            new->next = curr;
            return;
        }
        else
        {
            prev = curr;
            curr = curr->next;
        }
    }
    //NULL means new is the last therefore you can insert at end
    if (curr == NULL)
    {
        prev->next = new;
        return;
    }
}
//Search BST for a word, return 1 if its in 0 if not
//Credit to the psudeo code in lecture
int SearchTree(InvertedIndexBST Tree, char *Word)
{
    //Base Case
    if (Tree == NULL)
    {
        return 0;
    }
    //less than the word therefore go left
    else if (strcmp(Tree->word, Word) > 0)
    {
        return SearchTree(Tree->left, Word);
    }
    //opposite way
    else if (strcmp(Tree->word, Word) < 0)
    {
        return SearchTree(Tree->right, Word);
    }
    //found the node in tree
    else
    {
        return 1;
    }
}
//After finding out the word is not in the tree you insert into tree
//Alphabetically used a bit of psudeo code from lecture
InvertedIndexBST InsertTree(InvertedIndexBST Tree, char *Word, char *FileName)
{
    //base case
    if (Tree == NULL)
    {
        return createFirstNode(Word, FileName);
    }
    else if (strcmp(Tree->word, Word) > 0)
    {
        Tree->left = InsertTree(Tree->left, Word, FileName);
        return Tree;
    }
    else if (strcmp(Tree->word, Word) < 0)
    {
        Tree->right = InsertTree(Tree->right, Word, FileName);
        return Tree;
    }
    //if you found the node you can return it
    else
    {
        return Tree;
    }
}
//search tree and returns the node locationinstead of 0/1
InvertedIndexBST SearchTree2(InvertedIndexBST Tree, char *Word)
{
    if (Tree == NULL)
    {
        return NULL;
    }
    else if (strcmp(Tree->word, Word) > 0)
    {
        return SearchTree2(Tree->left, Word);
    }
    else if (strcmp(Tree->word, Word) < 0)
    {
        return SearchTree2(Tree->right, Word);
    }
    else
    {
        return Tree;
    }
}
//Adjust TF values after going through files
void AdjustTF(char *FileName, int WordCount, InvertedIndexBST Tree)
{
    FileList curr = NULL;
    //base case
    if (Tree == NULL)
    {
        return;
    }
    else
    {
        curr = Tree->fileList;
        while (curr != NULL)
        {
            //found the file to divide 
            if (strcmp(curr->filename, FileName) == 0)
            {
                curr->tf = curr->tf / WordCount;
                curr = curr->next;
            }
            else
            {
                curr = curr->next;
            }
        }
        //recursion through the tree
        AdjustTF(FileName, WordCount, Tree->left);
        AdjustTF(FileName, WordCount, Tree->right);
    }
}

void printInvertedIndex(InvertedIndexBST tree)
{
    //base case
    if (tree == NULL)
    {
        return;
    }
    //Inorder printing
    printInvertedIndex(tree->left);
    FILE *fp;
    FileList curr = tree->fileList;

    fp = fopen("invertedIndex.txt", "a");
    //print word
    fprintf(fp, "%s ", tree->word);
    curr = tree->fileList;
    while (curr != NULL)
    //while loop through file list
    {
        fprintf(fp, "%s ", curr->filename);
        curr = curr->next;
    }
    fprintf(fp, "\n");
    fclose(fp);
    //recusrion thorugh the right
    printInvertedIndex(tree->right);
}
//Just a test function to print the tree in main
void testPrint(InvertedIndexBST tree)
{
    if (tree == NULL)
    {
        return;
    }
    testPrint(tree->left);
    printf("%s ", tree->word);
    testPrint(tree->right);
}
//calculate tfidf of the tree and word
TfIdfList calculateTfIdf(InvertedIndexBST tree, char *searchWord, int D){
    InvertedIndexBST found = SearchTree2(tree, searchWord);
    FileList curr = found->fileList;
    //number of files
    double fileCount = numberOfFiles(curr);
    TfIdfList result = NULL;
    int firstTime = 0;
    double tfidf = 0;
    //finding idf
    double idf = log10(D / fileCount);

    while(curr != NULL){
        //calculating tfidf every iteration
        tfidf = curr->tf * idf;
        //first node
        if(firstTime == 0){
            result = createtfidf(curr->filename, tfidf);
            firstTime = 1;
        }
        else{
            //insert into the list
            result = Inserttfidf(result, curr->filename, tfidf);
        }
        curr = curr->next;
    }
    return result;
}
//Function that finds the number of files in an word
int numberOfFiles(FileList list){
    if(list == NULL){
        return 0;
    }
    //iterate through list
    int fileCount = 0;
    while(list != NULL){
        fileCount++;
        list = list->next;
    }
    return fileCount;
}
//creat a tfidf node
TfIdfList createtfidf(char *filename, double sum){
    TfIdfList new = malloc(sizeof(struct TfIdfNode));
    if(new == NULL){
        printf("Not Enough Memory");
        return NULL;
    }
    char *copy = malloc(sizeof(char) * 1000);
    strcpy(copy, filename);
    new->filename = copy;
    new->tfIdfSum = sum;
    new->next = NULL;
    return new;
}
//insert tfidf
TfIdfList Inserttfidf(TfIdfList list, char *filename, double tfidf){
    TfIdfList new = createtfidf(filename, tfidf);
    TfIdfList curr = list;
    TfIdfList prev = NULL;
    while(curr != NULL){
        //insert between nodes in descending order
        if(prev != NULL && curr->tfIdfSum < tfidf){
            prev->next = new;
            new->next = curr;
            return list;
        }
        //list is in alphabeticall order so it auto insert
        //in alphabetical order if there is equal tfidf
        //insert in front of the list
        else if(prev == NULL && curr->tfIdfSum < tfidf){
            new->next = list;
            list = new;
            return list;
        }
        else{
            prev = curr;
            curr = curr->next;
        }
    }
    //if at end of list
    if(curr == NULL){
        prev->next = new;
        return list;
    }
    return list;
}
//This function returns an ordered list where each node contains a filename and the summation 
//of tf-idf values of all the matching searchWords for that file.
TfIdfList retrieve(InvertedIndexBST tree, char *searchWords[], int D){
    int i = 0;
    TfIdfList head = NULL;
    TfIdfList temp = NULL;
    int FirstNode = 0;

    while(searchWords[i] != NULL){
        //iterate through the list of words and stores the tfidf in a temporary list
        temp = calculateTfIdf(tree, searchWords[i], D);
        while(temp != NULL){
            //initailizes the first node for head
            if(FirstNode == 0){
                head = createtfidf(temp->filename, temp->tfIdfSum);
                FirstNode = 1;
                temp = temp->next;
            }
            else{
                //check if the files is in the list
                int inFile = -1;
                inFile = checkFileList(head, temp->filename, temp->tfIdfSum);
                if(inFile == 0){
                    head = Inserttfidf(head, temp->filename, temp->tfIdfSum);
                }
                temp = temp->next;
            }
        }
        i++;
    }
    //sorts the list in descending order
    Sort(head);
    return head;
}
//checks if a filename is in the list if it is adds tfidf to the file, 0 for no, 1 for yes
int checkFileList(TfIdfList list, char *filename, double tfidf){
    if(list == NULL){
        return 0;
    }
    TfIdfList curr = list;
    while(curr != NULL){
        //adds the tfidf together if you find the file
        if(strcmp(filename, curr->filename) == 0){
            curr->tfIdfSum = curr->tfIdfSum + tfidf;
            return 1;
        }
        curr = curr->next;
    }
    return 0;
}
//Sort the list in descending order
void Sort(TfIdfList list){
    int check = 1; 
    TfIdfList curr; 
    TfIdfList prev = NULL; 
  
    //check for empty list
    if (list == NULL){
        return; 
    }
    //starts the loop as long as its looping 
    while(check == 1){ 
        check = 0;
        //resets the curr pointer to the start of the list 
        curr = list; 
        //as long as the next node isnt a node where you swapped already
        //as they are already in order or NULL
        while (curr->next != prev){
            //if the next sum is greater than the current sum swap them 
            if (curr->tfIdfSum < curr->next->tfIdfSum){  
                swapData(curr, curr->next);
                //allows the loop to continue 
                check = 1; 
            }
            //if the sum are equal then check for alphabeticality
            else if(curr->tfIdfSum == curr->next->tfIdfSum){
                if(strcmp(curr->filename, curr->next->filename) > 0){
                    //if not alphabetically correct swap them
                    swapData(curr, curr->next); 
                    check = 1; 
                }
            }
            //iterate through the loop 
            curr = curr->next; 
        }
        //sets a point where you swapped already 
        prev = curr; 
    }  
}
//swaps two nodes data
void swapData(TfIdfList a, TfIdfList b){
    //swap tfIdf values
    double temp = a->tfIdfSum; 
    a->tfIdfSum = b->tfIdfSum; 
    b->tfIdfSum = temp;
    //swaps the filenames
    char *temp2 = a->filename;
    a->filename = b->filename;
    b->filename = temp2;
}
