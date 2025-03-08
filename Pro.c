#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITLE 100
#define MAX_AUTHOR 100
#define MAX_BOOKS 100

typedef struct {
    int id;
    char title[MAX_TITLE];
    char author[MAX_AUTHOR];
    int is_borrowed;
} Book;

void add_book();
void view_books();
void borrow_book();
void return_book();
void save_books();
void load_books();

Book books[MAX_BOOKS];
int book_count = 0;

FILE *file;
const char *filename = "library_data.txt";

int main() {
    int choice;
    load_books();
    
    while (1) {
        printf("\nLibrary Management System\n");
        printf("1. Add Book\n2. View Books\n3. Borrow Book\n4. Return Book\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();
        
        switch (choice) {
            case 1: add_book(); break;
            case 2: view_books(); break;
            case 3: borrow_book(); break;
            case 4: return_book(); break;
            case 5: save_books(); exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}

void add_book() {
    if (book_count >= MAX_BOOKS) {
        printf("Library is full!\n");
        return;
    }
    
    books[book_count].id = book_count + 1;
    printf("Enter book title: ");
    fgets(books[book_count].title, MAX_TITLE, stdin);
    strtok(books[book_count].title, "\n");
    
    printf("Enter author: ");
    fgets(books[book_count].author, MAX_AUTHOR, stdin);
    strtok(books[book_count].author, "\n");
    
    books[book_count].is_borrowed = 0;
    book_count++;
    
    printf("Book added successfully!\n");
    save_books();
}

void view_books() {
    printf("\nAvailable Books:\n");
    for (int i = 0; i < book_count; i++) {
        printf("ID: %d | Title: %s | Author: %s | %s\n", books[i].id, books[i].title, books[i].author, books[i].is_borrowed ? "Borrowed" : "Available");
    }
}

void borrow_book() {
    int id;
    printf("Enter Book ID to borrow: ");
    scanf("%d", &id);
    getchar();
    
    if (id < 1 || id > book_count || books[id - 1].is_borrowed) {
        printf("Invalid or already borrowed book!\n");
        return;
    }
    
    books[id - 1].is_borrowed = 1;
    printf("Book borrowed successfully!\n");
    save_books();
}

void return_book() {
    int id;
    printf("Enter Book ID to return: ");
    scanf("%d", &id);
    getchar();
    
    if (id < 1 || id > book_count || !books[id - 1].is_borrowed) {
        printf("Invalid or not borrowed book!\n");
        return;
    }
    
    books[id - 1].is_borrowed = 0;
    printf("Book returned successfully!\n");
    save_books();
}

void save_books() {
    file = fopen(filename, "w");
    if (!file) {
        printf("Error saving books!\n");
        return;
    }
    fwrite(&book_count, sizeof(int), 1, file);
    fwrite(books, sizeof(Book), book_count, file);
    fclose(file);
}

void load_books() {
    file = fopen(filename, "r");
    if (!file) return;
    fread(&book_count, sizeof(int), 1, file);
    fread(books, sizeof(Book), book_count, file);
    fclose(file);
}