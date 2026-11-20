#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define MAX_NAME 100
#define BUFFER_SIZE 1024

void create_file();
void write_file();
void read_file();
void append_file();
void copy_file();
void rename_file();
void delete_file();
void change_permissions();

int main() {
    int choice;
    char tmp[16];
    while (1) {
        printf("\n====== File Management System ======\n");
        printf("1. Create File\n");
        printf("2. Write to File\n");
        printf("3. Read File\n");
        printf("4. Append to File\n");
        printf("5. Copy File\n");
        printf("6. Rename File\n");
        printf("7. Delete File\n");
        printf("8. Change Permissions (chmod)\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) break;
        getchar();
        switch (choice) {
            case 1: create_file(); break;
            case 2: write_file(); break;
            case 3: read_file(); break;
            case 4: append_file(); break;
            case 5: copy_file(); break;
            case 6: rename_file(); break;
            case 7: delete_file(); break;
            case 8: change_permissions(); break;
            case 9: printf("Exiting...\n"); return 0;
            default: printf("Invalid choice (1-9).\n"); break;
        }
        printf("\nPress Enter to continue...");
        fgets(tmp, sizeof(tmp), stdin);
    }
    return 0;
}

void create_file() {
    char name[MAX_NAME];
    int fd;
    printf("\n--- Create File ---\n");
    printf("Enter file name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';
    if (strlen(name) == 0) {
        printf("Empty name not allowed.\n");
        return;
    }
    fd = open(name, O_CREAT | O_EXCL | O_WRONLY, 0644);
    if (fd < 0) {
        perror("create_file");
        return;
    }
    close(fd);
    printf("File '%s' created successfully.\n", name);
}

void write_file() {
    char name[MAX_NAME], content[BUFFER_SIZE];
    int fd, n;
    printf("\n--- Write to File ---\n");
    printf("Enter file name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';
    fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("write_file");
        return;
    }
    printf("Enter text content (single line): ");
    fgets(content, sizeof(content), stdin);
    content[strcspn(content, "\n")] = '\0';
    n = write(fd, content, strlen(content));
    if (n < 0) {
        perror("write");
    } else {
        printf("Written %d bytes to '%s'.\n", n, name);
    }
    close(fd);
    struct stat st;
    if (stat(name, &st) == 0) {
        printf("File size after write: %ld bytes\n", (long)st.st_size);
    }
}

void read_file() {
    char name[MAX_NAME], buf[BUFFER_SIZE];
    int fd, n;
    printf("\n--- Read File ---\n");
    printf("Enter file name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';
    fd = open(name, O_RDONLY);
    if (fd < 0) {
        perror("read_file");
        return;
    }
    printf("Contents of '%s':\n", name);
    while ((n = read(fd, buf, sizeof(buf) - 1)) > 0) {
        buf[n] = '\0';
        printf("%s", buf);
    }
    if (n < 0) perror("read");
    printf("\n--- End of File ---\n");
    close(fd);
}

void append_file() {
    char name[MAX_NAME], content[BUFFER_SIZE];
    int fd, n;
    printf("\n--- Append to File ---\n");
    printf("Enter file name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';
    fd = open(name, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0) {
        perror("append_file");
        return;
    }
    printf("Enter text to append (single line): ");
    fgets(content, sizeof(content), stdin);
    content[strcspn(content, "\n")] = '\0';
    n = write(fd, content, strlen(content));
    if (n < 0) {
        perror("write");
    } else {
        printf("Appended %d bytes to '%s'.\n", n, name);
    }
    close(fd);
    struct stat st;
    if (stat(name, &st) == 0) {
        printf("File size after append: %ld bytes\n", (long)st.st_size);
    }
}

void copy_file() {
    char src[MAX_NAME], dst[MAX_NAME], buf[BUFFER_SIZE];
    int sfd, dfd, n;
    printf("\n--- Copy File ---\n");
    printf("Enter source file name: ");
    fgets(src, sizeof(src), stdin);
    src[strcspn(src, "\n")] = '\0';
    printf("Enter destination file name: ");
    fgets(dst, sizeof(dst), stdin);
    dst[strcspn(dst, "\n")] = '\0';
    sfd = open(src, O_RDONLY);
    if (sfd < 0) {
        perror("copy_file src");
        return;
    }
    dfd = open(dst, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dfd < 0) {
        perror("copy_file dst");
        close(sfd);
        return;
    }
    while ((n = read(sfd, buf, sizeof(buf))) > 0) {
        if (write(dfd, buf, n) < 0) {
            perror("write");
            break;
        }
    }
    if (n < 0) perror("read");
    close(sfd);
    close(dfd);
    printf("'%s' copied to '%s' successfully.\n", src, dst);
}

void rename_file() {
    char oldn[MAX_NAME], newn[MAX_NAME];
    printf("\n--- Rename File ---\n");
    printf("Enter current file name: ");
    fgets(oldn, sizeof(oldn), stdin);
    oldn[strcspn(oldn, "\n")] = '\0';
    printf("Enter new file name: ");
    fgets(newn, sizeof(newn), stdin);
    newn[strcspn(newn, "\n")] = '\0';
    if (rename(oldn, newn) != 0) {
        perror("rename_file");
        return;
    }
    printf("File renamed from '%s' to '%s' successfully.\n", oldn, newn);
}

void delete_file() {
    char name[MAX_NAME];
    printf("\n--- Delete File ---\n");
    printf("Enter file name to delete: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';
    if (unlink(name) != 0) {
        perror("delete_file");
        return;
    }
    printf("File '%s' deleted successfully.\n", name);
}

void change_permissions() {
    char name[MAX_NAME];
    mode_t mode;
    int perm;
    printf("\n--- Change Permissions (chmod) ---\n");
    printf("Enter file name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';
    printf("Enter permission (octal, e.g. 644): ");
    scanf("%o", &perm);
    getchar();
    mode = (mode_t)perm;
    if (chmod(name, mode) != 0) {
        perror("chmod");
        return;
    }
    printf("Permissions of '%s' changed to %o successfully.\n", name, perm);
}
