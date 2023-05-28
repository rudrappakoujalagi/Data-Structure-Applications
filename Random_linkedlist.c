#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

void print_linked_list(Node* head);
void read_linked_list(Node** head, int n);
void bubble_sort(Node* head);
void selection_sort(Node* head);
void rand_numbers(int n, int lower, int upper, FILE* fp);
void read_linked_list_file(Node** head, FILE* fp);
void print_num_file(Node* head, FILE* fp);
void free_linked_list(Node* head);

void bubble_sort(Node* head) {
    int swapped;
    Node* ptr1;
    Node* lptr = NULL;

    if (head == NULL)
        return;

    do {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (ptr1->data > ptr1->next->data) {
                int temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

void selection_sort(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* min = current;
        Node* temp = current->next;

        while (temp != NULL) {
            if (temp->data < min->data) {
                min = temp;
            }
            temp = temp->next;
        }

        int swap = current->data;
        current->data = min->data;
        min->data = swap;

        current = current->next;
    }
}

void print_linked_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
}

void read_linked_list(Node** head, int n) {
    srand(time(NULL));
    *head = NULL;
    for (int i = 0; i < n; i++) {
        int num = rand() % 1000;
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->data = num;
        newNode->next = *head;
        *head = newNode;
    }
}

void rand_numbers(int n, int lower, int upper, FILE* fp) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        int num = lower + rand() % (upper - lower + 1);
        fprintf(fp, "%d ", num);
    }
}

void read_linked_list_file(Node** head, FILE* fp) {
    *head = NULL;
    int num;
    while (fscanf(fp, "%d", &num) != EOF) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->data = num;
        newNode->next = *head;
        *head = newNode;
    }
}

void print_num_file(Node* head, FILE* fp) {
    Node* current = head;
    while (current != NULL) {
        fprintf(fp, "%d ", current->data);
        current = current->next;
    }
}

void free_linked_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
}

int main() {
    Node* head = NULL;
    FILE* fp;
    FILE* fp1;
    FILE* fp2;

    fp = fopen("input.txt", "w");
    rand_numbers(10, 40, 100, fp);
    fclose(fp);

    fp1 = fopen("input.txt", "r");
    read_linked_list_file(&head, fp1);
    fclose(fp1);

    print_linked_list(head);

    bubble_sort(head);
    selection_sort(head);

    printf("\n");
    print_linked_list(head);

    fp2 = fopen("output.txt", "w");
    print_num_file(head, fp2);
    fclose(fp2);

    free_linked_list(head);

    return 0;
}

