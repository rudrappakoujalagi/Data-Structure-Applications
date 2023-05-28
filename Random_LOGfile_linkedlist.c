#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

void generate_input_file(char* filename, int X) {
    FILE* file = fopen(filename, "w");
    srand(time(NULL));
    for (int i = 0; i < X; i++) {
        fprintf(file, "%d\n", rand() % 1000);
    }
    fclose(file);
}

void read_input_file(char* filename, Node** head, int X) {
    FILE* file = fopen(filename, "r");
    Node* current = NULL;
    for (int i = 0; i < X; i++) {
        int num;
        fscanf(file, "%d", &num);
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->data = num;
        newNode->next = NULL;
        if (current == NULL) {
            *head = newNode;
            current = newNode;
        } else {
            current->next = newNode;
            current = current->next;
        }
    }
    fclose(file);
}

void log_sorting_time(char* sorting_technique, int X, double time) {
    FILE* file = fopen("log.txt", "a");
    fprintf(file, "Sorting technique: %s, X: %d, time: %f seconds\n", sorting_technique, X, time);
    fclose(file);
}

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

void free_linked_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
}

int main() {
    int X = 10000;
    char* filename = "input.txt";
    generate_input_file(filename, X);

    Node* head = NULL;
    read_input_file(filename, &head, X);

    clock_t start, end;
    double time_taken;

    start = clock();
    bubble_sort(head);
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    log_sorting_time("Bubble sort", X, time_taken);

    free_linked_list(head);

    head = NULL;
    read_input_file(filename, &head, X);

    start = clock();
    selection_sort(head);
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    log_sorting_time("Selection sort", X, time_taken);

    free_linked_list(head);

    return 0;
}
