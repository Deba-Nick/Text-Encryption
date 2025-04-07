#include <stdio.h>
#include <string.h>

#define MAX_TEXT_LENGTH 100

void encrypt(char text[], int key, char ciphertext[]);
void decrypt(char ciphertext[], int key, char plaintext[]);

int main() {
    char text[MAX_TEXT_LENGTH];
    int key;
    char ciphertext[MAX_TEXT_LENGTH];
    char decrypted_text[MAX_TEXT_LENGTH];

    printf("Enter plaintext: ");
    fgets(text, MAX_TEXT_LENGTH, stdin);
    text[strcspn(text, "\n")] = '\0';

    printf("Enter key (integer): ");
    scanf("%d", &key);

    encrypt(text, key, ciphertext);
    printf("Encrypted text: %s\n", ciphertext);

    decrypt(ciphertext, key, decrypted_text);
    printf("Decrypted text: %s\n", decrypted_text);

    return 0;
}

void encrypt(char text[], int key, char ciphertext[]) {
    int length = strlen(text);
    int i, j, index = 0;

    for (i = 0; i < key; i++) {
        for (j = i; j < length; j += key) {
            ciphertext[index++] = text[j];
        }
    }
    ciphertext[index] = '\0';
}

void decrypt(char ciphertext[], int key, char plaintext[]) {
    int length = strlen(ciphertext);
    int rows = length / key;
    int extra = length % key;
    if (extra != 0) {
        rows += 1;
    }

    char matrix[rows][key];
    int i, j, pos = 0;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < key; j++) {
            matrix[i][j] = '\0';
        }
    }

    for (j = 0; j < key; j++) {
        int current_column_height = rows;
        if (j >= extra && extra != 0) {
            current_column_height -= 1;
        }

        for (i = 0; i < current_column_height && pos < length; i++) {
            matrix[i][j] = ciphertext[pos++];
        }
    }

    int index = 0;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < key; j++) {
            if (matrix[i][j] != '\0') {
                plaintext[index++] = matrix[i][j];
            }
        }
    }
    plaintext[index] = '\0';
}

