#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
    int     id;
    char    name;
    int     order;
};

struct HashType
{
    struct RecordType **records;  //Array of pointers to RecordType
    int size;                     //Size of the hash table
};

int hash(int x, int tableSize)
{
    return x % tableSize;
}

// Parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
    FILE* inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(-1);
        }
        for (i = 0; i < dataSz; ++i)
        {
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, "%c ", &c);
            pRecord->name = c;
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
        }

        fclose(inFile);
    }

    return dataSz;
}

//prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
    int i;
    printf("\nRecords:\n");
    for (i = 0; i < dataSz; ++i)
    {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n\n");
}

//Display records in the hash structure
void displayRecordsInHash(struct HashType *hashTable)
{
    int i;

    for (i = 0; i < hashTable->size; ++i)
    {
        if (hashTable->records[i] != NULL)
        {
            printf("index %d -> %d, %c, %d\n", i, hashTable->records[i]->id, hashTable->records[i]->name, hashTable->records[i]->order);
        }
    }
}

int main(void)
{
    struct RecordType *pRecords;
    int recordSz = 0;
    int hashSize = 10;

    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);

    //Initialize hash table
    struct HashType hashTable;
    hashTable.size = hashSize;
    hashTable.records = (struct RecordType**) calloc(hashSize, sizeof(struct RecordType*));

    // Insert records into hash table
    for (int i = 0; i < recordSz; ++i)
    {
        int idx = hash(pRecords[i].id, hashSize);
        hashTable.records[idx] = &pRecords[i];  //Directly store pointers in the hash table
    }

    // Display hash table
    displayRecordsInHash(&hashTable);

    return 0;
}
