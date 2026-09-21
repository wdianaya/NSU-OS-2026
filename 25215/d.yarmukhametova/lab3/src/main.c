#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

void print_uid() {
    printf("real uid: %d\n", getuid());
    printf("effective uid: %d\n", geteuid());
}

int main() {
    printf("before changing uids\n");
    print_uid();
    
    int errno;

    FILE *file;
    file = fopen("file", "r");

    if (file == NULL) {
        perror("error when opening a file");
    }
    fclose(file);

    int flag = setuid(getuid());
    if (flag == -1) {
        perror("error executing setuid");
        return 1;
    }

    printf("after changing uid\n");
    print_uid();

    file = fopen("file", "r");

    if (file == NULL) {
        perror("error when opening a file");
    }
    fclose(file);       

    return 0;
}