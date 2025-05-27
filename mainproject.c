#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include "project.h"

#define TABLE_SIZE 1000
#define MAX_TOKENS 1000
#define MAX_LINE_LENGTH 1024
#define MAX_WORD_LENGTH 100

int main() {
    HashTable *ht = createHashTable();

    char file1[512], file2[512];
    char file1Content[4096] = {0};  // Increased size for larger files
    char file2Content[4096] = {0};  // Increased size for larger files

    // Print usage instructions
    printUsage();

    // Get file names from user
    printf("Enter the name of the first file: ");
    scanf("%512s", file1);
    printf("Enter the name of the second file: ");
    scanf("%512s", file2);

    // Read first file and build hash table
    printf("Reading file: %s\n", file1);
    readFile(file1, ht);

    // Display summary for the first file
    printf("\nDisplaying file summary for %s:\n", file1);
    FILE *file1Handle = fopen(file1, "r");
    
    displayTokens(ht);
    
    if (file1Handle)
    {
        fread(file1Content, 1, sizeof(file1Content) - 1, file1Handle);
        fclose(file1Handle);
        displayFileSummary(file1Content);
    } 
    else 
    {
        handleFileError(file1);
    }

    // Compare with the second file
    printf("\nComparing with file: %s\n", file2);
    int matchingTokens = compareFiles(ht, file2);


    // Count unique tokens in the hash table for the first file
    int totalUniqueTokens1 = 0;
    for (int i = 0; i < TABLE_SIZE; i++) 
    {
        Node *current = ht->table[i];
        while (current) 
        {
            totalUniqueTokens1++;
            current = current->next;
        }
    }

    // Read second file and count unique tokens
    HashTable *ht2 = createHashTable();
    printf("\nReading file: %s\n", file2);
    FILE *file2Handle = fopen(file2, "r");
    if (file2Handle) 
    {
        fread(file2Content, 1, sizeof(file2Content) - 1, file2Handle);
        fclose(file2Handle);
        readFile(file2, ht2);
    } 
    else 
    {
        handleFileError(file2);
    }

    int totalUniqueTokens2 = 0;
    for (int i = 0; i < TABLE_SIZE; i++) 
    {
        Node *current = ht2->table[i];
        while (current) 
        {
            totalUniqueTokens2++;
            current = current->next;
        }
    }

    // Calculate similarity
    double similarity = calcSimilarity(totalUniqueTokens1, totalUniqueTokens2, matchingTokens);
    printf("\nMatching Tokens: %d\n", matchingTokens);
    printf("Total Unique Tokens in %s: %d\n", file1, totalUniqueTokens1);
    printf("Total Unique Tokens in %s: %d\n", file2, totalUniqueTokens2);
    printf("Similarity: %.2f%%\n", similarity);


    // Highlight plagiarized tokens in the second file
    if (isPlagiarised(similarity)) 
    {
        printf("\nPlagiarism detected!\n");

        // Highlight plagiarized tokens in the second file
        printf("\nHighlighting plagiarized tokens in %s:\n", file2);
        highlightPlagiarizedTokens(file2Content, ht);

        // Ask if the user wants to replace plagiarized text
        printf("\nDo you want to replace plagiarized text in %s? (y/n): ", file2);
        char choice;
        scanf(" %c", &choice);
        if (choice == 'y' || choice == 'Y') 
        {
            replacePlagiarizedText(file2Content, ht, file2, totalUniqueTokens1, totalUniqueTokens2, matchingTokens);
        }
    } 
    else 
    {
        printf("No plagiarism detected.\n");
    }

    // Display statistics for the second file
    printf("\nDisplaying statistics for %s:\n", file2);
    displayStatistics(file2Content);

    // Free memory
		      printf("\033[1;34m------------------------------------------------------------------------------------------------------------------------------------------------------------\033[0m\n");
		      printf("\033[1;33m*************************************************************CLEARING HASH TABLES ************************************************************************\033[0m\n");
			printf("\033[1;34m------------------------------------------------------------------------------------------------------------------------------------------------------------\033[0m\n");
    freeHashTable(ht);
    freeHashTable(ht2);

    return 0;
}

