#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 32


typedef struct Node {
    int key;
    float num;
    char str[MAX];
    struct Node* next;
    struct Node* prev;
} Node;

bool insert_after(Node** head, Node** last, int pos, int key, char* str, float num);
void insert_first(Node** head, Node** last, int key, char* str, float num);
void insert_last(Node** last, int key, char* str, float num);

void print_length(Node* head);
void display_forward(Node* head);
void display_backward(Node* last);

void write_file(Node* head);


void main() {
    Node* head = NULL;
    Node* last = NULL;

    printf("Filling the list...\n");
    insert_first(&head, &last, 1, "one", 1.0);
    insert_first(&head, &last, 2, "two", 2.0);
    insert_first(&head, &last, 3, "three", 3.0);
    insert_first(&head, &last, 4, "four", 4.0);
    insert_first(&head, &last, 5, "five", 5.0);

    insert_last(&last, 0, "zero", 0.0);
    insert_after(&head, &last, 2, 777, "added", 777.00);
    insert_last(&last, -1, "-one", -1.00);

    insert_first(&head, &last, 6, "six", 6.0);

    display_forward(head);
    display_backward(last);

    print_length(head);

    printf("\n[WRITE]: Saving doubly linked list...\n");
    write_file(head);
}

void print_length(Node* head) {
    Node* current;
    int length = 0;

    for (current = head; current != NULL; current = current->next) {
        length++;
    }

    printf("\n[LENGHT]: The doubly linked list have %d el.\n", length);
}

void display_forward(Node* head) {
    Node* ptr = head;

    printf("\nDisplay Forward:\n");
    while (ptr != NULL) {
        printf("%d: STR: %s; NUM: %.2f\n", ptr->key, ptr->str, ptr->num);
        ptr = ptr->next;
    }
}

void display_backward(Node* last) {
    Node* ptr = last;

    printf("\nDisplay Backward:\n");
    while (ptr != NULL){
        printf("%d: STR: %s; NUM: %.2f\n", ptr->key, ptr->str, ptr->num);
        ptr = ptr->prev;
    }
}

void insert_first(Node** head, Node** last, int key, char* str, float num) {
    Node* link = (Node*)malloc(sizeof(Node));
    link->key = key;
    strcpy(link->str, str);
    link->num = num;

    if ((*head) == NULL) {
        (*last) = link;
    } else {
        (*head)->prev = link;
    }

    link->next = (*head);
    (*head) = link;

    printf("[INSERT FIRST]: New el.: STR: '%s'; NUM: %.2f\n", str, num);
}

void insert_last(Node** last, int key, char* str, float num) {
    Node* link = (Node*)malloc(sizeof(Node));
    link->key = key;
    strcpy(link->str, str);
    link->num = num;

    if ((*last) == NULL) {
        (*last) = link;
    } else {
        (*last)->next = link;
        link->prev = (*last);
    }

    (*last) = link;

    printf("[INSERT LAST]: New el.: STR: '%s'; NUM: %.2f\n", str, num);
}

bool insert_after(Node** head, Node** last, int pos, int key, char* str, float num) {
    Node* current = (*head);

    if ((*head) == NULL) {
        return false;
    }

    while (current->key != pos){
        if (current->next == NULL) {
            return false;
        } else {
            current = current->next;
        }
    }

    Node* new_link = (Node*)malloc(sizeof(Node));

    new_link->key = key;
    strcpy(new_link->str, str);
    new_link->num = num;

    if (current == (*last)) {
        new_link->next = NULL;
        (*last) = new_link;
    } else {
        new_link->next = current->next;
        current->next->prev = new_link;
    }

    new_link->prev = current;
    current->next = new_link;

    printf("[INSERT AFTER]: New el.: STR: '%s'; NUM: %.2f\n", str, num);

    return true;
}

void write_file(Node* head) {
    Node* ptr = head;
    char name[MAX];

    printf("Enter file name (like 'file.txt'): ");
    scanf("%s", name);

    FILE* fp;
    fp = fopen(name, "w");

    while (ptr != NULL) {
        fprintf(fp, "%d %s %.2f\n", ptr->key, ptr->str, ptr->num);
        ptr = ptr->next;
    }
    
    fclose(fp);
}
