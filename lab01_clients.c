#include "bank_types.h"

// UTILITY FUNCTIONS

int calculateAge(Date dob) {
    return 2026 - dob.year;
}

int hasAccount(int clientId) {
    for (int i = 0; i < accountCount; i++)
        if (accounts[i].clientId == clientId)
            return 1;
    return 0;
}

int findClientById(int id) {
    for (int i = 0; i < clientCount; i++)
        if (clients[i].id == id)
            return i;
    return -1;
}

int findAccountByClientId(int clientId) {
    for (int i = 0; i < accountCount; i++)
        if (accounts[i].clientId == clientId)
            return i;
    return -1;
}

int isDigitsOnly(const char *str) {
    if (*str == '\0') return 0;
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] < '0' || str[i] > '9')
            return 0;
    return 1;
}

int isLettersOnly(const char *str) {
    if (*str == '\0') return 0;
    for (int i = 0; str[i] != '\0'; i++) {
        char ch = str[i];
        if (!((ch >= 'a' && ch <= 'z') ||
              (ch >= 'A' && ch <= 'Z') ||
               ch == '-'))
            return 0;
    }
    return 1;
}

void readClientInfo(Client *c) {
    do {
        printf("  Family Name      : "); scanf("%29s", c->name);
        if (!isLettersOnly(c->name))
            printf("  [ERROR] Family name must contain letters only.\n");
    } while (!isLettersOnly(c->name));

    /* --- First Name : letters only --- */
    do {
        printf("  First Name       : "); scanf("%29s", c->firstName);
        if (!isLettersOnly(c->firstName))
            printf("  [ERROR] First name must contain letters only.\n");
    } while (!isLettersOnly(c->firstName));

    /* --- Day : must be between 1 and 31 --- */
    do {
        printf("    Day   (1-31)   : "); scanf("%d", &c->dateOfBirth.day);
        if (c->dateOfBirth.day < 1 || c->dateOfBirth.day > 31)
            printf("    [ERROR] Day must be between 1 and 31.\n");
    } while (c->dateOfBirth.day < 1 || c->dateOfBirth.day > 31);

    /* --- Month : must be between 1 and 12 --- */
    do {
        printf("    Month (1-12)   : "); scanf("%d", &c->dateOfBirth.month);
        if (c->dateOfBirth.month < 1 || c->dateOfBirth.month > 12)
            printf("    [ERROR] Month must be between 1 and 12.\n");
    } while (c->dateOfBirth.month < 1 || c->dateOfBirth.month > 12);

    /* --- Year --- */
    printf("    Year           : "); scanf("%d", &c->dateOfBirth.year);

    /* --- Address : no special characters like quotes --- */
    do {
        printf("  Address          : "); scanf(" %[^\n]", c->address);
        int valid = 1;
        for (int i = 0; c->address[i] != '\0'; i++) {
            char ch = c->address[i];
            if (ch == '\'' || ch == '"') { valid = 0; break; }
        }
        if (!valid)
            printf("  [ERROR] Address must not contain quotes.\n");
        else break;
    } while (1);

    /* --- Phone : digits only --- */
    do {
        printf("  Phone Number     : "); scanf("%19s", c->tel);
        if (!isDigitsOnly(c->tel))
            printf("  [ERROR] Phone number must contain digits only (0-9).\n");
    } while (!isDigitsOnly(c->tel));
}

// ADD
void addClient(void) {
    if (clientCount >= MAX_CLIENTS) {
        printf("[ERROR] Client database is full.\n");
        return;
    }

    Client  newClient;
    Account newAccount;

    printf("\n=== Add New Client ===\n");

    /* Auto-generate ID = clientCount + 1 */
    newClient.id = clientCount + 1;
    printf("  [INFO] Auto-generated Client ID : %d\n", newClient.id);

    readClientInfo(&newClient);

    /* ID is auto-generated so duplicates are impossible */

    /* Calculate age once — used for type validation */
    int age = calculateAge(newClient.dateOfBirth);

    /* Choose account type */
    printf("  Account Type (P=Individual / M=Minor / C=Commercial) : ");
    scanf(" %c", &newAccount.accountType);
    newAccount.accountType = (char)toupper((unsigned char)newAccount.accountType);

    /* Enforce conditions per type */
    if (newAccount.accountType == 'P') {
        /* Individual: must be at least 18 years old */
        if (age < 18) {
            printf("[ERROR] Individual account requires age >= 18. (Age = %d)\n", age);
            return;
        }

    } else if (newAccount.accountType == 'M') {
        /* Minor: age must be less than 18 */
        if (age >= 18) {
            printf("[ERROR] Minor account requires age < 18. (Age = %d)\n", age);
            printf("        Use Individual (P) or Commercial (C) instead.\n");
            return;
        }
        /* Guardian must already have an account in this bank */
        int guardianId;
        printf("  Guardian's Client ID : ");
        scanf("%d", &guardianId);
        if (!hasAccount(guardianId)) {
            printf("[ERROR] Guardian (ID %d) has no account in this bank.\n", guardianId);
            return;
        }

    } else if (newAccount.accountType == 'C') {
        /* Commercial: no extra condition */
        printf("  [INFO] Commercial account — no age restriction.\n");

    } else {
        printf("[ERROR] Invalid account type '%c'.\n", newAccount.accountType);
        return;
    }

    /* Initial balance */
    printf("  Initial Balance (DZD) : ");
    scanf("%d", &newAccount.balance);
    if (newAccount.balance < 0) {
        printf("[ERROR] Balance cannot be negative.\n");
        return;
    }

    newAccount.clientId = newClient.id;
    newAccount.blocked  = 0;

    clients[clientCount++]   = newClient;
    accounts[accountCount++] = newAccount;

    printf("[OK] Client and account created successfully.\n");
}

// SEARCH
void searchClient(void) {
    int id;
    printf("\n=== Search Client ===\n");
    printf("Enter Client ID : ");
    scanf("%d", &id);

    int ci = findClientById(id);
    if (ci == -1) { printf("[NOT FOUND] No client with ID %d.\n", id); return; }

    Client *c = &clients[ci];
    printf("\n--- Client Info ---\n");
    printf("  ID           : %d\n",   c->id);
    printf("  Name         : %s %s\n", c->name, c->firstName);
    printf("  Date of Birth: %02d/%02d/%04d\n",
           c->dateOfBirth.day, c->dateOfBirth.month, c->dateOfBirth.year);
    printf("  Address      : %s\n",   c->address);
    printf("  Phone        : %s\n",   c->tel);

    int ai = findAccountByClientId(id);
    if (ai != -1) {
        Account *a = &accounts[ai];
        printf("\n--- Account Info ---\n");
        printf("  Type         : %c\n",     a->accountType);
        printf("  Balance      : %d DZD\n", a->balance);
        printf("  Status       : %s\n",     a->blocked ? "BLOCKED" : "ACTIVE");
    }
}

// MODIFY
void modifyClient(void) {
    int id;
    printf("\n=== Modify Client ===\n");
    printf("Enter Client ID to modify : ");
    scanf("%d", &id);

    int ci = findClientById(id);
    if (ci == -1) { printf("[NOT FOUND] No client with ID %d.\n", id); return; }

    int savedId = clients[ci].id;
    readClientInfo(&clients[ci]);
    clients[ci].id = savedId;

    printf("[OK] Client information updated.\n");
}

// DELETE
void deleteClient(void) {
    int id;
    printf("\n=== Delete Client ===\n");
    printf("Enter Client ID to delete : ");
    scanf("%d", &id);

    int ci = findClientById(id);
    if (ci == -1) { printf("[NOT FOUND] No client with ID %d.\n", id); return; }

    for (int i = ci; i < clientCount - 1; i++)
        clients[i] = clients[i + 1];
    clientCount--;

    int ai = findAccountByClientId(id);
    if (ai != -1) {
        for (int i = ai; i < accountCount - 1; i++)
            accounts[i] = accounts[i + 1];
        accountCount--;
    }

    printf("[OK] Client (and account) deleted.\n");
}

// LIST
void listClients(void) {
    printf("\n=== Client List (%d registered) ===\n", clientCount);
    if (clientCount == 0) { printf("  No clients yet.\n"); return; }

    for (int i = 0; i < clientCount; i++) {
        Client *c  = &clients[i];
        int     ai = findAccountByClientId(c->id);
        printf("  [%d] %-15s %-15s | DOB: %02d/%02d/%04d | Tel: %-12s",
               c->id, c->name, c->firstName,
               c->dateOfBirth.day, c->dateOfBirth.month, c->dateOfBirth.year,
               c->tel);
        if (ai != -1)
            printf(" | %c | %d DZD | %s",
                   accounts[ai].accountType,
                   accounts[ai].balance,
                   accounts[ai].blocked ? "BLOCKED" : "ACTIVE");
        printf("\n");
    }
}

// CLIENT MENU
void clientMenu(void) {
    char choice;
    do {
        printf("\n+-------------------------------+\n");
        printf("|      CLIENT MANAGEMENT        |\n");
        printf("|         (LAB 01)              |\n");
        printf("+-------------------------------+\n");
        printf("| A - Add client                |\n");
        printf("| S - Search client             |\n");
        printf("| U - Update client             |\n");
        printf("| D - Delete client             |\n");
        printf("| L - List all clients          |\n");
        printf("| Q - Back                      |\n");
        printf("+-------------------------------+\n");
        printf("Choice : ");
        scanf(" %c", &choice);

        switch ((char)toupper((unsigned char)choice)) {
            case 'A': addClient();    break;
            case 'S': searchClient(); break;
            case 'U': modifyClient(); break;
            case 'D': deleteClient(); break;
            case 'L': listClients();  break;
            case 'Q': break;
            default : printf("[ERROR] Unknown option.\n");
        }
    } while ((char)toupper((unsigned char)choice) != 'Q');
}
