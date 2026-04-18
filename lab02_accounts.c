#include "bank_types.h"

// عملية الإيداع (T)
void deposit() {
    int id, amount;
    printf("\n--- Deposit (T) ---\n");
    printf("Enter Client ID: "); scanf("%d", &id);
    
    int idx = findAccountByClientId(id);
    if (idx != -1) {
        printf("Current Balance: %d DZD\n", accounts[idx].balance);
        printf("Enter amount to deposit: "); scanf("%d", &amount);
        if (amount > 0) {
            accounts[idx].balance += amount;
            printf("[OK] New Balance: %d DZD\n", accounts[idx].balance);
        }
    } else printf("[ERROR] Account not found.\n");
}

// عملية السحب (R)
void withdraw() {
    int id, amount;
    printf("\n--- Withdrawal (R) ---\n");
    printf("Enter Client ID: "); scanf("%d", &id);
    
    int idx = findAccountByClientId(id);
    if (idx != -1) {
        if (accounts[idx].blocked) { printf("[ERROR] Account is blocked!\n"); return; }
        printf("Enter amount to withdraw: "); scanf("%d", &amount);
        if (amount > 0 && amount <= accounts[idx].balance) {
            accounts[idx].balance -= amount;
            printf("[OK] Remaining Balance: %d DZD\n", accounts[idx].balance);
        } else printf("[ERROR] Insufficient funds or invalid amount.\n");
    } else printf("[ERROR] Account not found.\n");
}

// قائمة العمليات المالية لـ LAB 02
void accountMenu() {
    char choice;
    do {
        printf("\n======= BANKING OPERATIONS (LAB 02) =======\n");
        printf("T - Deposit\n");
        printf("R - Withdrawal\n");
        printf("Q - Back\n");
        printf("Choice: "); scanf(" %c", &choice);
        choice = toupper(choice);

        if (choice == 'T') deposit();
        else if (choice == 'R') withdraw();
    } while (choice != 'Q');
}
