#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void generate_input_file(char* filename, int X) {
    FILE* file = fopen("RUDRA.txt", "w");
    srand(time(NULL));
    for (int i = 0; i < X; i++) {
        fprintf(file, "%d\n", rand()%1000);
    }
    fclose(file);
}


void read_input_file(char* filename, int X, int* arr) {
    FILE* file = fopen("RUDRA.txt", "r");
    for (int i = 0; i < X; i++) {
        fscanf(file, "%d", &arr[i]);
    }
    fclose(file);
}


void log_sorting_time(char* sorting_technique, int X, double time) {
    FILE* file = fopen("log.txt", "a");
    fprintf(file, "Sorting technique: %s, X: %d, time: %f seconds\n", sorting_technique, X, time);
    fclose(file);
}


void bubble_sort(int* arr, int X) {
    for (int i = 0; i < X-1; i++) {
        for (int j = 0; j < X-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}


void selection_sort(int* arr, int X) {
    for (int i = 0; i < X-1; i++) {
        int min_idx = i;
        for (int j = i+1; j < X; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = temp;
    }
}

int main() {
    int X = 10000;
    char* filename = "input.txt";
    generate_input_file(filename, X);

    int arr[X];
    read_input_file(filename, X, arr);

    clock_t start, end;
    double time_taken;


    start = clock();
    bubble_sort(arr, X);
    end = clock();
    time_taken = ((double) (end - start)) / CLOCKS_PER_SEC;
    log_sorting_time("Bubble sort", X, time_taken);


    read_input_file(filename, X, arr);
    start = clock();
    selection_sort(arr, X);
    end = clock();
    time_taken = ((double) (end - start)) / CLOCKS_PER_SEC;
    log_sorting_time("Selection sort", X, time_taken);

    return 0;
}
