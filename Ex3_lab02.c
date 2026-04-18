#include <stdio.h>
char findFirstUpper(char *str) {
    if (*str == '\0') {
        return '\0';
    }

    if (*str >= 'A' && *str <= 'Z') {
        return *str;
    }

    return findFirstUpper(str + 1);
}

int main() {
    char text[100];
    char result;

    printf("Enter a string: ");
    scanf("%s", text);

    result = findFirstUpper(text);

    if (result != '\0') {
        printf("Output: %c\n", result);
    } else {
        printf("No uppercase letter found.\n");
    }

    return 0;
}
