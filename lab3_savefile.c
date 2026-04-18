#include "bank_types.h"

// 1. دالة حفظ البيانات في ملفات (Save)
void saveToFile() {
    // حفظ العملاء
    FILE *fClients = fopen("clients.dat", "wb"); // wb تعني كتابة ثنائية
    if (fClients != NULL) {
        fwrite(&clientCount, sizeof(int), 1, fClients); // حفظ العدد أولاً
        fwrite(clients, sizeof(Client), clientCount, fClients); // حفظ المصفوفة كاملة
        fclose(fClients);
    }

    // حفظ الحسابات
    FILE *fAccounts = fopen("accounts.dat", "wb");
    if (fAccounts != NULL) {
        fwrite(&accountCount, sizeof(int), 1, fAccounts);
        fwrite(accounts, sizeof(Account), accountCount, fAccounts);
        fclose(fAccounts);
    }
    printf("\n[SUCCESS] All data has been saved to files.\n");
}

// 2. دالة استرجاع البيانات عند تشغيل البرنامج (Load)
void loadFromFile() {
    // تحميل العملاء
    FILE *fClients = fopen("clients.dat", "rb"); // rb تعني قراءة ثنائية
    if (fClients != NULL) {
        fread(&clientCount, sizeof(int), 1, fClients);
        fread(clients, sizeof(Client), clientCount, fClients);
        fclose(fClients);
    }

    // تحميل الحسابات
    FILE *fAccounts = fopen("accounts.dat", "rb");
    if (fAccounts != NULL) {
        fread(&accountCount, sizeof(int), 1, fAccounts);
        fread(accounts, sizeof(Account), accountCount, fAccounts);
        fclose(fAccounts);
    }
}
