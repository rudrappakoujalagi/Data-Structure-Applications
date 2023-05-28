#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Structure for a queue node
struct Node {
    int data;
    struct Node* next;
};

// Structure for the queue
typedef struct {
    struct Node* front;
    struct Node* rear;
} Queue;

// Function to create an empty queue
Queue* createQueue()
{
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

// Function to check if the queue is empty
int isEmpty(Queue* queue)
{
    return (queue->front == NULL);
}

// Function to enqueue an element
void enqueue(Queue* queue, int data)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;

    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
    }
    else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

// Function to dequeue an element
int dequeue(Queue* queue)
{
    if (isEmpty(queue)) {
        printf("Queue is empty.\n");
        return -1;
    }

    struct Node* temp = queue->front;
    int data = temp->data;
    queue->front = queue->front->next;

    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    free(temp);
    return data;
}

// Function to print the elements in the queue
void print_queue(Queue* queue)
{
    struct Node* current = queue->front;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Function to generate random numbers and write them to a file
void rand_numbers(int n, int lower, int upper, FILE* fp)
{
    srand(time(NULL));
    int num;
    for (int i = 0; i < n; i++) {
        num = lower + rand() % (upper - lower + 1);
        fprintf(fp, "%d ", num);
    }
}

// Function to read numbers from a file into a queue
void read_queue_file(Queue* queue, FILE* fp)
{
    int num;
    while (fscanf(fp, "%d", &num) != EOF) {
        enqueue(queue, num);
    }
}

// Function to write the elements in the queue to a file
void print_num_file(Queue* queue, FILE* fp)
{
    struct Node* current = queue->front;
    while (current != NULL) {
        fprintf(fp, "%d ", current->data);
        current = current->next;
    }
}

// Bubble sort using a queue
void bubble_sort(Queue* queue)
{
    int swapped;
    struct Node* current;
    struct Node* last = NULL;

    if (isEmpty(queue))
        return;

    do {
        swapped = 0;
        current = queue->front;

        while (current->next != last) {
            if (current->data > current->next->data) {
                int temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;
                swapped = 1;
            }
            current = current->next;
        }
        last = current;
    } while (swapped);
}

// Selection sort using a queue
void selection_sort(Queue* queue)
{
    struct Node* current;
    struct Node* smallest;
    struct Node* prev_smallest;
    struct Node* temp;

    if (isEmpty(queue))
        return;

    current = queue->front;

    while (current != NULL) {
        smallest = current;
        prev_smallest = NULL;
        temp = current->next;

        while (temp != NULL) {
            if (temp->data < smallest->data) {
                smallest = temp;
                prev_smallest = current;
            }
            temp = temp->next;
        }

        if (smallest != current) {
            if (prev_smallest != NULL)
                prev_smallest->next = current;

            temp = current->next;
            current->next = smallest->next;
            smallest->next = temp;

            if (current == queue->front)
                queue->front = smallest;
            if (current == queue->rear)
                queue->rear = current;
        }

        current = current->next;
    }
}

int main()
{
    FILE* fp;
    FILE* fp2;
    Queue* queue = createQueue();

    fp = fopen("input.txt", "w");
    rand_numbers(10, 40, 100, fp);
    fclose(fp);

    fp = fopen("input.txt", "r");
    read_queue_file(queue, fp);
    fclose(fp);

    printf("Input: ");
    print_queue(queue);

    bubble_sort(queue);

    printf("Sorted: ");
    print_queue(queue);

    selection_sort(queue);

    printf("Sorted: ");
    print_queue(queue);

    fp2 = fopen("output.txt", "w");
    print_num_file(queue, fp2);
    fclose(fp2);

    return 0;
}
