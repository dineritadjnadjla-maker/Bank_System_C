#ifndef BANK_TYPES_H
#define BANK_TYPES_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// --- الإعدادات العامة ---
#define MAX_CLIENTS 100
#define MAX_ACCOUNTS 100

// --- تعريف الهياكل (Structs) ---
typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    int id;
    char name[30];
    char firstName[30];
    Date dateOfBirth;
    char address[100];
    char tel[20];
} Client;

typedef struct {
    int clientId;
    char accountType; // P, M, C
    int balance;
    bool blocked;
} Account;

extern Client clients[MAX_CLIENTS];
extern Account accounts[MAX_ACCOUNTS];
extern int clientCount;
extern int accountCount;


// من LAB 01
void clientMenu(void);
int findAccountByClientId(int clientId);
int findClientById(int id);
int isDigitsOnly(const char *str);

// من LAB 02 (يمكنك إضافتها لاحقاً)
void accountMenu(void); 

// من LAB 03
void saveToFile(void);
void loadFromFile(void);

#endif
