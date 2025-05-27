#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TABLE_SIZE 1000

typedef struct Node {
    char *token;
    struct Node *next;
} Node;

typedef struct HashTable {
    Node **table;
} HashTable;

// Function prototypes
HashTable* createHashTable();
unsigned int hashFn(const char *token);
void insertWord(HashTable *ht, const char *token);
int searchWord(HashTable *ht, const char *token);
void readFile(const char *filename, HashTable *ht);
void tokenizeText(const char *text, HashTable *ht);
int compareFiles(HashTable *ht, const char *filename);
double calcSimilarity(int totalUniqueTokens1, int totalUniqueTokens2, int matchingTokens);
int isPlagiarised(double similarity);
void freeHashTable(HashTable *ht);
void displayUniqueTokens(HashTable *ht);
void handleFileError(const char *filename);
void toLowercaseAndRemovePunctuation(char *str);

int main() {
    HashTable *ht = createHashTable();
    
    char file1[256], file2[256];
    
    // Get file names from user
    printf("Enter the name of the first file: ");
    scanf("%255s", file1);
    printf("Enter the name of the second file: ");
    scanf("%255s", file2);

    // Read first file and build hash table
    printf("Reading file: %s\n", file1);
    readFile(file1, ht);
    
    // Compare with the second file
    printf("Comparing with file: %s\n", file2);
    int matchingTokens = compareFiles(ht, file2);
    
    // Count unique tokens in the hash table
    int totalUniqueTokens1 = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node *current = ht->table[i];
        while (current) {
            totalUniqueTokens1++;
            current = current->next;
        }
    }

    // Display unique tokens in the first file
    printf("Unique tokens in %s:\n", file1);
    displayUniqueTokens(ht);

    // Assume totalUniqueTokens2 is counted from the second file
    HashTable *ht2 = createHashTable();
    printf("Reading file: %s\n", file2);
    readFile(file2, ht2);
    int totalUniqueTokens2 = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node *current = ht2->table[i];
        while (current) {
            totalUniqueTokens2++;
            current = current->next;
        }
    }

    // Calculate similarity
    double similarity = calcSimilarity(totalUniqueTokens1, totalUniqueTokens2, matchingTokens);
    printf("Matching Tokens: %d\n", matchingTokens);
    printf("Total Unique Tokens in %s: %d\n", file1, totalUniqueTokens1);
    printf("Total Unique Tokens in %s: %d\n", file2, totalUniqueTokens2);
    printf("Similarity: %.2f%%\n", similarity);

    if (isPlagiarised(similarity)) {
        printf("Plagiarism detected!\n");
    } else {
        printf("No plagiarism detected.\n");
    }
    
    // Free memory
    freeHashTable(ht);
    freeHashTable(ht2);
    
    return 0;
}

HashTable* createHashTable() {
    HashTable *ht = malloc(sizeof(HashTable));
    ht->table = malloc(TABLE_SIZE * sizeof(Node *));
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->table[i] = NULL;
    }
    return ht;
}

unsigned int hashFn(const char *token) {
    unsigned int hash = 0;
    while (*token) {
        hash = (hash << 5) + *token++;
    }
    return hash % TABLE_SIZE;
}

void insertWord(HashTable *ht, const char *token) {
    unsigned int index = hashFn(token);
    Node *newNode = malloc(sizeof(Node));
    newNode->token = strdup(token);
    newNode->next = ht->table[index];
    ht->table[index] = newNode;
}

int searchWord(HashTable *ht, const char *token) {
    unsigned int index = hashFn(token);
    Node *current = ht->table[index];
    while (current) {
        if (strcmp(current->token, token) == 0) {
            return 1; // Found
        }
        current = current->next;
    }
    return 0; // Not found
}

void readFile(const char *filename, HashTable *ht) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        handleFileError(filename);
        return;
    }
    
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        tokenizeText(buffer, ht);
    }
    
    fclose(file);
}

void tokenizeText(const char *text, HashTable *ht) {
    char *str = strdup(text);
    toLowercaseAndRemovePunctuation(str);
    
    char *token = strtok(str, " ");
    while (token) {
        if (strlen(token) > 0) {
            insertWord(ht, token);
        }
        token = strtok(NULL, " ");
    }
    
    free(str);
}

void toLowercaseAndRemovePunctuation(char *str) {
    char *rest = str;
    while (*rest) {
        if (ispunct((unsigned char)*rest)) {
            *rest = ' ';
        } else {
            *rest = tolower((unsigned char)*rest);
        }
        rest++;
    }
}

int compareFiles(HashTable *ht, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        handleFileError(filename);
        return 0;
    }
    
    char buffer[1024];
    int matchingTokens = 0;

    while (fgets(buffer, sizeof(buffer), file)) {
        char *str = strdup(buffer);
        toLowercaseAndRemovePunctuation(str);

        char *token = strtok(str, " ");
        while (token) {
            if (strlen(token) > 0 && searchWord(ht, token)) {
                matchingTokens++;
            }
            token = strtok(NULL, " ");
        }

        free(str);
    }

    fclose(file);
    return matchingTokens;
}

double calcSimilarity(int totalUniqueTokens1, int totalUniqueTokens2, int matchingTokens) {
    double unionCount = totalUniqueTokens1 + totalUniqueTokens2 - matchingTokens;
    return (unionCount > 0) ? (matchingTokens / unionCount) * 100.0 : 0;
}

int isPlagiarised(double similarity) {
    return similarity > 75.0;
}

void freeHashTable(HashTable *ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node *current = ht->table[i];
        while (current) {
            Node *temp = current;
            current = current->next;
            free(temp->token);
            free(temp);
        }
    }
    free(ht->table);
    free(ht);
}

void displayUniqueTokens(HashTable *ht) {
    printf("Unique Tokens:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node *current = ht->table[i];
        while (current) {
            //printf("%s\n", current->token);
            current = current->next;
        }
    }
}

void handleFileError(const char *filename) {
    perror("Error opening file");
    printf("Could not open file: %s\n", filename);
    exit(EXIT_FAILURE);
}

