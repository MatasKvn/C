/*

This program reads no more than 255 symbols from each line from a .txt file and removes all palindomes, writes it into the output file

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 256

// functions:
char* removePalindrome(char *word); // returns "" is the parameter is a palindrome, else return the parameter
void getLineNoPalindromes(char *buffer, char *bufferOut); // converts line (*buffer) into a line that contains no Palindromes (*bufferOut)
int extractWord(char *buffer, int index, char *wordOut); // extracts a word from *buffer at index, places it into *wordOut
int insertWord(char *string, int index, char *word); // inserts *word into *string at index
void clearArray(char array[], int length);// sets all char array elements to '\0' to avoid clashes with leftover data

int main(int argc, char *argv[])
{
    //temporary, for easier testing
    //argv[1] = "input.txt";
    //argv[2] = "output.txt";

    if(argv[1] == NULL){
        printf("Input file not found!\n");
        return 1;
    }
    if(argv[2] == NULL){
        printf("Output file not found!\n");
        return 1;
    }

    FILE *inFile;
    inFile = fopen(argv[1], "r");
    FILE *outFile;
    outFile = fopen(argv[2], "w");

    if(outFile == NULL){
        printf("Unable to open output file!\n");
        return 1;
    }
 
    char *buffer = malloc(MAX_LENGTH*sizeof(char));
    char *bufferOut = malloc(MAX_LENGTH*sizeof(char));

    char c;
    
    while(fgets(buffer, MAX_LENGTH, inFile))    // main cycle
    {
        getLineNoPalindromes(buffer, bufferOut);
        fprintf(outFile, "%s", bufferOut);

        if(buffer[strlen(buffer)-1] != '\n'){   // If the line doesn't end with '\n'(there are more than 255 symbols), reads until start of next line
            c = fgetc(inFile);
            while(c != '\n' && c != '\0' && c != EOF)
            {
                c = fgetc(inFile);
            }
        }

        if(c != EOF)    //ends line for next output
        {
            fprintf(outFile, "\n");
        }

        clearArray(bufferOut, MAX_LENGTH); // clears bufferOut to avoid leftover data
    }

    // ===//END//===
    free(buffer);
    free(bufferOut);
    fclose(inFile);
    fclose(outFile);

    return 0;
}

void getLineNoPalindromes(char *buffer, char *bufferOut)
{
    int outLength=0;
    int temp;
    char tempWord[MAX_LENGTH];
    int i;
    for(i=0; i < MAX_LENGTH; ++i)
    {
        if(buffer[i] == '\n' || buffer[i] == '\0'){ // breaks the cycle if text ends
            break; 
        }
        if(buffer[i] == ' '){ // processes 'space' symbols

            bufferOut[outLength] = ' ';
            ++outLength;
            
        }else{ // processes words
            temp = extractWord(buffer, i, tempWord); // extracts word
            i += temp-1; // sets buffer index to after the word

            temp = insertWord(bufferOut, outLength, removePalindrome(tempWord)); // inserts the word into bufferOut
            outLength+=temp; // sets bufferOut index to after the word
        }
    }
}

int insertWord(char *string, int index, char *word)
{
    int length = strlen(word);
    int i;
    for(i=index; i < index+length; ++i){
        string[i] = word[i-index];
    }
    string[index+length] = '\0';
    return length;
}

int extractWord(char *buffer, int index, char *wordOut)
{
    int length; // word length
    char temp[MAX_LENGTH];

    int i;
    length = 0;
    for(i=index; !isspace(buffer[i]) && buffer[i] != '\0'; ++i)
    {
        ++length;
        wordOut[i-index] = buffer[i];
    }
    wordOut[length] = '\0';

    return length;
}

char* removePalindrome(char *word)
{
    int n = strlen(word);

    for(int i=0; i<n; ++i)
    {
        if(word[i] != word[n-1-i] || word[i] == ' ')
        {
            return word;
        }
    }
    return "";
}

void clearArray(char array[], int length)
{
    int i;
    for(i=0; i<length; ++i)
    {
        array[i] = '\0';
    }
}
