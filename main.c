#include "bank_types.h"

Client  clients[MAX_CLIENTS];
Account accounts[MAX_ACCOUNTS];
int     clientCount  = 0;
int     accountCount = 0;

void loadFromFile();
void saveToFile();
void clientMenu();
void accountMenu();

int main() {
    loadFromFile();

    int choice;
    do {
        printf("\n========================================");
        printf("\n|      CENTRAL BANK SYSTEM (OUARGLA)   |");
        printf("\n========================================");
        printf("\n| 1. Client Management (LAB 01)        |");
        printf("\n| 2. Banking Operations (LAB 02)       |");
        printf("\n| 3. Exit and Save Data (LAB 03)       |");
        printf("\n========================================");
        printf("\nChoice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                clientMenu();
                break;
            case 2:
                accountMenu();
                break;
            case 3:
                saveToFile();
                printf("\n[INFO] Data saved successfully. Goodbye!\n");
                break;
            default:
                printf("\n[ERROR] Invalid choice, try again.\n");
        }
    } while (choice != 3);

    return 0;
}
