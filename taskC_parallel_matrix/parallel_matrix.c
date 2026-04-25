#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

#define MAX_ROWS 1000
#define MAX_COLS 1000

typedef struct {
    int thread_id;
    int start_row;
    int end_row;
    int cols;
    int **matrix_a;
    int **matrix_b;
    int **result;
} ThreadData;

int **create_matrix(int rows, int cols) {
    int **matrix = malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        matrix[i] = calloc(cols, sizeof(int));
    }
    return matrix;
}

void init_matrix(int **matrix, int rows, int cols, int seed) {
    srand(seed);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % 100;
        }
    }
}

void *add_matrix_rows(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    
    for (int i = data->start_row; i < data->end_row; i++) {
        for (int j = 0; j < data->cols; j++) {
            data->result[i][j] = data->matrix_a[i][j] + data->matrix_b[i][j];
        }
    }
    
    return NULL;
}

double get_time_ms() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000.0 + tv.tv_usec / 1000.0;
}

int main(int argc, char *argv[]) {
    int rows = 100;
    int cols = 100;
    int num_threads = 4;
    
    if (argc > 1) {
        num_threads = atoi(argv[1]);
    }
    if (argc > 2) {
        rows = atoi(argv[2]);
    }
    if (argc > 3) {
        cols = atoi(argv[3]);
    }
    
    if (num_threads < 1) num_threads = 1;
    if (rows < 1) rows = 1;
    if (cols < 1) cols = 1;
    
    printf("=== Parallel Matrix Adder ===\n");
    printf("Matrix size: %d x %d\n", rows, cols);
    printf("Number of threads: %d\n", num_threads);
    
    int **matrix_a = create_matrix(rows, cols);
    int **matrix_b = create_matrix(rows, cols);
    int **result = create_matrix(rows, cols);
    
    init_matrix(matrix_a, rows, cols, 42);
    init_matrix(matrix_b, rows, cols, 123);
    
    pthread_t threads[num_threads];
    ThreadData thread_data[num_threads];
    int rows_per_thread = rows / num_threads;
    int remainder = rows % num_threads;
    
    double start_time = get_time_ms();
    
    for (int t = 0; t < num_threads; t++) {
        thread_data[t].thread_id = t;
        thread_data[t].start_row = t * rows_per_thread;
        thread_data[t].end_row = (t + 1) * rows_per_thread;
        if (t == num_threads - 1) {
            thread_data[t].end_row += remainder;
        }
        thread_data[t].cols = cols;
        thread_data[t].matrix_a = matrix_a;
        thread_data[t].matrix_b = matrix_b;
        thread_data[t].result = result;
        
        pthread_create(&threads[t], NULL, add_matrix_rows, &thread_data[t]);
    }
    
    for (int t = 0; t < num_threads; t++) {
        pthread_join(threads[t], NULL);
    }
    
    double end_time = get_time_ms();
    double elapsed = end_time - start_time;
    
    printf("Computation time: %.2f ms\n", elapsed);
    printf("\nSample results (first 3x3):\n");
    for (int i = 0; i < 3 && i < rows; i++) {
        for (int j = 0; j < 3 && j < cols; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
    
    for (int i = 0; i < rows; i++) {
        free(matrix_a[i]);
        free(matrix_b[i]);
        free(result[i]);
    }
    free(matrix_a);
    free(matrix_b);
    free(result);
    
    return 0;
}
