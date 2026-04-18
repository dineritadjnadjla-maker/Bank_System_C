#include "bank_types.h"

/* --- (T) Deposit: إضافة مبلغ للحساب --- */
void depositMoney() {
    int id, amount;
    printf("\n--- Deposit (T) ---\n");
    printf("Enter Client ID: "); scanf("%d", &id);
    int idx = findAccountByClientId(id);
    if (idx == -1) { printf("[ERROR] Account not found.\n"); return; }

    printf("Enter amount: "); scanf("%d", &amount);
    if (amount > 0) {
        accounts[idx].balance += amount;
        printf("[OK] New Balance: %d DZD\n", accounts[idx].balance);
    }
}

/* --- (V) Transfer: تحويل من حساب لآخر --- */
void transferMoney() {
    int idFrom, idTo, amount;
    printf("\n--- Transfer (V) ---\n");
    printf("From Client ID: "); scanf("%d", &idFrom);
    printf("To Client ID: ");   scanf("%d", &idTo);
    int idxFrom = findAccountByClientId(idFrom);
    int idxTo = findAccountByClientId(idTo);

    if (idxFrom == -1 || idxTo == -1) { printf("[ERROR] One/both accounts not found.\n"); return; }
    if (accounts[idxFrom].blocked) { printf("[ERROR] Source account is BLOCKED.\n"); return; }

    printf("Amount to transfer: "); scanf("%d", &amount);
    if (amount > 0 && amount <= accounts[idxFrom].balance) {
        accounts[idxFrom].balance -= amount;
        accounts[idxTo].balance += amount;
        printf("[OK] Transfer successful.\n");
    } else printf("[ERROR] Insufficient funds or invalid amount.\n");
}

/* --- (R) Withdrawal: سحب مبلغ --- */
void withdrawMoney() {
    int id, amount;
    printf("\n--- Withdrawal (R) ---\n");
    printf("Enter Client ID: "); scanf("%d", &id);
    int idx = findAccountByClientId(id);
    if (idx == -1) { printf("[ERROR] Account not found.\n"); return; }
    if (accounts[idx].blocked) { printf("[ERROR] Account is BLOCKED.\n"); return; }

    printf("Enter amount: "); scanf("%d", &amount);
    if (amount > 0 && amount <= accounts[idx].balance) {
        accounts[idx].balance -= amount;
        printf("[OK] Remaining Balance: %d DZD\n", accounts[idx].balance);
    } else printf("[ERROR] Operation failed.\n");
}

/* --- (M) Modification: تغيير نوع الحساب --- */
void modifyAccountType() {
    int id;
    char newType;
    printf("\n--- Modify Account Type (M) ---\n");
    printf("Enter Client ID: ");
    scanf("%d", &id);

    int idx = findAccountByClientId(id);
    if (idx == -1) {
        printf("[ERROR] No account found for ID %d.\n", id);
        return;
    }

    printf("Current Account Type: %c\n", accounts[idx].accountType);

    do {
        printf("Enter New Type (P=Individual / M=Minor / C=Commercial): ");
        scanf(" %c", &newType);
        newType = toupper(newType);

        if (newType != 'P' && newType != 'M' && newType != 'C') {
            printf("[ERROR] Invalid type! Please use only P, M, or C.\n");
        }
    } while (newType != 'P' && newType != 'M' && newType != 'C');

    accounts[idx].accountType = newType;
    printf("[OK] Account type successfully updated to %c.\n", accounts[idx].accountType);
}

/* --- (C) Account Inquiry: تفاصيل الحساب فقط --- */
void accountInquiry() {
    int id;
    printf("\n--- Account Inquiry (C) ---\n");
    printf("Enter Client ID: "); scanf("%d", &id);
    int idx = findAccountByClientId(id);
    if (idx == -1) { printf("[ERROR] Account not found.\n"); return; }

    printf("\n--- Financial Status ---\n");
    printf("  Client ID: %d\n", accounts[idx].clientId);
    printf("  Type     : %c\n", accounts[idx].accountType);
    printf("  Balance  : %d DZD\n", accounts[idx].balance);
    printf("  Status   : %s\n", accounts[idx].blocked ? "BLOCKED" : "ACTIVE");
}

/* القائمة الكاملة لـ LAB 02 */
void accountMenu() {
    char choice;
    do {
        printf("\n======= BANK OPERATIONS (LAB 02) =======\n");
        printf("T - Deposit (Verser)\n");
        printf("V - Transfer (Virement)\n");
        printf("R - Withdrawal (Retirer)\n");
        printf("M - Modification (Type)\n");
        printf("C - Account Inquiry (Consultation)\n");
        printf("Q - Back\n");
        printf("Choice: "); scanf(" %c", &choice);
        choice = toupper(choice);

        switch(choice) {
            case 'T': depositMoney(); break;
            case 'V': transferMoney(); break;
            case 'R': withdrawMoney(); break;
            case 'M': modifyAccountType(); break;
            case 'C': accountInquiry(); break;
            case 'Q': break;
            default: printf("[ERROR] Invalid option.\n");
        }
    } while(choice != 'Q');
}
