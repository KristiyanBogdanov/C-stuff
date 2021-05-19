#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 32
#define FILE_NAME "dll_file.bin"


typedef struct Node {
    int key;
    int num;
    char str[MAX];
    struct Node* next;
    struct Node* prev;
} Node;

bool insert_after(Node** head, Node** last, int pos, int key, char* str, int num);
void insert_first(Node** head, Node** last, int key, char* str, int num);
void insert_last(Node** last, int key, char* str, int num);

Node* delete_first(Node** head, Node** last);
Node* delete_last(Node** head, Node** last);
Node* delete(Node** head, Node** last, int key);
Node* concatenate(Node* head, Node* head2, Node** head3, Node** last3);

void print_length(Node* head);
void display_forward(Node* head);
void display_backward(Node* last);

void write_bfile(Node* head);
void read_bfile();


void main() {
    Node* head = NULL;
    Node* last = NULL;

    Node* head2 = NULL;
    Node* last2 = NULL;

    Node* head3 = NULL;
    Node* last3 = NULL;

// -------------------------------

    printf("Filling list one...\n");
    insert_first(&head, &last, 1, "one", 1);
    insert_first(&head, &last, 2, "two", 2);
    insert_first(&head, &last, 3, "three", 3);
    insert_first(&head, &last, 4, "four", 4);
    insert_first(&head, &last, 5, "five", 5);

    insert_last(&last, 0, "zero", 0);
    insert_after(&head, &last, 5, -1, "add", -1);

    delete_first(&head, &last);
    delete_last(&head, &last);
    delete(&head, &last, -1);

    display_forward(head);
    display_backward(last);

    print_length(head);

    printf("\n[WRITE]: Write list one to file...\n");
    write_bfile(head);
    printf("[READ]: Read list one from file:");
    read_bfile();

    printf("\nFilling list two...\n");
    insert_first(&head2, &last2, 5, "five", 5);
    insert_first(&head2, &last2, 6, "six", 6);
    insert_first(&head2, &last2, 7, "seven", 7);
    insert_first(&head2, &last2, 8, "eight", 8);
    insert_first(&head2, &last2, 9, "nine", 9);
    display_forward(head2);

    printf("\n[CONCATENATE]: Merge list one and list two into list three...\n");
    concatenate(head, head2, &head3, &last3);

    display_forward(head3);
    print_length(head3);
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
        printf("%d: STR: %s; NUM: %d\n", ptr->key, ptr->str, ptr->num);
        ptr = ptr->next;
    }
}

void display_backward(Node* last) {
    Node* ptr = last;

    printf("\nDisplay Backward:\n");
    while (ptr != NULL) {
        printf("%d: STR: %s; NUM: %d\n", ptr->key, ptr->str, ptr->num);
        ptr = ptr->prev;
    }
}

void insert_first(Node** head, Node** last, int key, char* str, int num) {
    Node* link = (Node*)malloc(sizeof(Node));
    link->key = key;
    strcpy(link->str, str);
    link->num = num;

    if ((*head) == NULL){
        (*last) = link;
    } else {
        (*head)->prev = link;
    }

    link->next = (*head);
    (*head) = link;

    printf("[INSERT FIRST]: New el.: STR: '%s'; NUM: %d\n", str, num);
}

void insert_last(Node** last, int key, char* str, int num) {
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

    printf("[INSERT LAST]: New el.: STR: '%s'; NUM: %d\n", str, num);
}

bool insert_after(Node** head, Node** last, int pos, int key, char* str, int num) {
    Node* current = (*head);

    if ((*head) == NULL){
        return false;
    }

    while (current->key != pos) {
        if (current->next == NULL){
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

    printf("[INSERT AFTER]: New el.: STR: '%s'; NUM: %d\n", str, num);

    return true;
}

Node* delete_first(Node** head, Node** last) {
   Node* temp_link = (*head);

   if ((*head)->next == NULL) {
      (*last) = NULL;
   } else {
      (*head)->next->prev = NULL;
   }

   (*head) = (*head)->next;

   printf("[DELETE FIRST]: DEL el.: STR: '%s'; NUM: %d\n", temp_link->str, temp_link->num);

   return temp_link;
}

Node* delete_last(Node** head, Node** last) {
   Node* temp_link = (*last);

   if ((*head)->next == NULL) {
      (*head) = NULL;
   } else {
      (*last)->prev->next = NULL;
   }

   (*last) = (*last)->prev;

   printf("[DELETE LAST]: DEL el.: STR: '%s'; NUM: %d\n", temp_link->str, temp_link->num);

   return temp_link;
}

Node* delete(Node** head, Node** last, int key) {
   Node* current = (*head);
   Node* previous = NULL;

   if ((*head) == NULL) {
      return NULL;
   }

   while (current->key != key) {
      if (current->next == NULL) {
         return NULL;
      } else {
         previous = current;
         current = current->next;
      }
   }

   if (current == (*head)) {
      (*head) = (*head)->next;
   } else {
      current->prev->next = current->next;
   }

   if (current == (*last)) {
      (*last) = current->prev;
   } else {
      current->next->prev = current->prev;
   }

   printf("[DELETE]: DEL el.: STR: '%s'; NUM: %d\n", current->str, current->num);

   return current;
}

void write_bfile(Node* head) {
    Node* ptr = head;

    FILE* fp;
    fp = fopen(FILE_NAME, "wb");

    while (ptr != NULL) {
        fwrite(&ptr->num, sizeof(int), 1, fp);
        fwrite(&ptr->key, sizeof(int), 1, fp);
        fwrite(ptr->str, MAX, 1, fp);
        ptr = ptr->next;
    }

    fclose(fp);
}

void read_bfile() {
    // Аз просто ще прочета doubly linked list-а и ще го изпринтя, но няма да правя негова структура, което
    // не е  никак трудно, просто не виждам смисъл в момента.

    int key, num;
    char str[MAX];

    FILE* fp = fopen(FILE_NAME, "rb");

    printf("\n\t------------------------\n");
    while (fread(&num, sizeof(int), 1, fp) > 0) {
        fread(&key, sizeof(int), 1, fp);
        fread(str, MAX, 1, fp);
        printf("\tKEY: %d; NUM: %d; STR: %s\n", key, num, str);
    }
    printf("\t------------------------\n");

    fclose(fp);
}

Node* concatenate(Node* head, Node* head2, Node** head3, Node** last3) {
    Node* link;

    (*head3) = head;
    link = (*head3);

    while(link->next!= NULL) {
      link = link->next;
    }

    link->next = head2;
    head2->prev = link;

    while(link->next != NULL) {
      link = link->next;
    }

    (*last3) = link;
}
