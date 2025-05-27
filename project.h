
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
void handleFileError(const char *filename);
void toLowercaseAndRemovePunctuation(char *str);
int countUniqueWords(char *text);
void clearHashTable(HashTable *ht);
void displayStatistics(char *content);
void saveToFile(const char *filename, const char *content);
void changeText(char *file2Content, const char *filename);
void addTextToFile(const char *filename, const char *text);
void displayFileSummary(char *content);
void printUsage();
void highlightPlagiarizedTokens(char *file2Content, HashTable *ht);
int isStopWord(const char *word);
void replacePlagiarizedText(char *file2Content, HashTable *ht, const char *filename, 
                            int totalUniqueTokens1, int totalUniqueTokens2, int matchingTokens);
void displayTokens(HashTable *ht);
