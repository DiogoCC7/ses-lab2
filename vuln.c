#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define SECRET "h@ckm3"
#define SECRET_LEN 6

void dangerous(char *input) {
    char small_buf[10];
    // unsafe copy: overflow if input too long and conditions are met
    strcpy(small_buf, input);
    printf("You shouldn't see this: %s\n", small_buf);
}

int validate(char *input) {
    // requires a complex series of conditions
    if (strlen(input) < 12) return 0;

    if (!isdigit(input[0])) return 0;
    if (input[1] != '-') return 0;
    if (strncmp(&input[2], SECRET, SECRET_LEN) != 0) return 0;

    int sum = 0;
    for (int i = 8; i < 12; i++) {
        if (!isdigit(input[i])) return 0;
        sum += input[i] - '0';
    }

    // tricky branch: only trigger if sum of last 4 digits is 20
    return sum == 20;
}

int main() {
    char input[64];
    printf("Enter input: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0; // remove newline

    if (validate(input)) {
        dangerous(input);  // <--- only reachable through a precise input path
    } else {
        printf("Invalid input format or wrong code.\n");
    }

    return 0;
}
