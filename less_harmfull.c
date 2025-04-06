#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SECRET "hackme"
#define SECRET_LEN 6

void vulnerable_function(char *input) {
    char buffer[8];  // small buffer, easy to overflow if not careful

    if (strncmp(input, SECRET, SECRET_LEN) == 0) {
        printf("Welcome, admin!\n");
        strcpy(buffer, input); // vulnerability: input may be longer than buffer
    } else {
        printf("Invalid password.\n");
    }

    printf("buffer: %s\n", buffer);
}

int main() {
    char input[64];
    printf("Enter password: ");
    fgets(input, sizeof(input), stdin);

    // remove trailing newline if present
    input[strcspn(input, "\n")] = 0;

    vulnerable_function(input);
    return 0;
}
