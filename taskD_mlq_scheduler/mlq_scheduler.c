#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int priority;
    int completion_time;
    int start_time;
    int response_time;
    bool started;
} Process;

typedef struct {
    Process *processes;
    int count;
    int capacity;
    char algorithm[16];
} Queue;

Queue create_queue(char *algo) {
    Queue q;
    q.capacity = 100;
    q.processes = malloc(q.capacity * sizeof(Process));
    q.count = 0;
    strcpy(q.algorithm, algo);
    return q;
}

void add_process(Queue *q, Process p) {
    q->processes[q->count++] = p;
}

void sort_by_burst(Process *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i].burst_time > arr[j].burst_time) {
                Process temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void sort_by_arrival(Process *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i].arrival_time > arr[j].arrival_time) {
                Process temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

int main() {
    printf("=== Multilevel Queue Scheduler ===\n\n");
    
    int num_processes = 5;
    Process input[] = {
        {1, 0, 10, 10, 5},
        {2, 1, 5, 5, 12},
        {3, 2, 8, 8, 15},
        {4, 3, 6, 6, 22},
        {5, 4, 12, 12, 25}
    };
    
    Queue q1 = create_queue("RR");
    Queue q2 = create_queue("SJF");
    Queue q3 = create_queue("FCFS");
    
    for (int i = 0; i < num_processes; i++) {
        Process p = input[i];
        p.completion_time = 0;
        p.start_time = -1;
        p.started = false;
        
        if (p.priority >= 0 && p.priority <= 10) {
            add_process(&q1, p);
        } else if (p.priority > 10 && p.priority <= 20) {
            add_process(&q2, p);
        } else {
            add_process(&q3, p);
        }
    }
    
    sort_by_burst(q2.processes, q2.count);
    sort_by_arrival(q3.processes, q3.count);
    
    printf("Queue 1 (System, RR): %d processes\n", q1.count);
    printf("Queue 2 (Interactive, SJF): %d processes\n", q2.count);
    printf("Queue 3 (Batch, FCFS): %d processes\n", q3.count);
    
    int cpu_time = 0;
    int time_slice = 10;
    int q1_slice = 5;
    int q2_slice = 3;
    int q3_slice = 2;
    int q1_index = 0, q2_index = 0, q3_index = 0;
    int quantum = 2;
    
    printf("\n=== Scheduling Simulation ===\n");
    printf("Time slices: Q1=%ds, Q2=%ds, Q3=%ds\n", q1_slice, q2_slice, q3_slice);
    
    Process all_procs[100];
    int all_count = 0;
    
    while (q1_index < q1.count || q2_index < q2.count || q3_index < q3.count) {
        int elapsed = 0;
        
        while (elapsed < q1_slice && q1_index < q1.count) {
            Process *p = &q1.processes[q1_index];
            if (p->arrival_time <= cpu_time && p->remaining_time > 0) {
                if (!p->started) {
                    p->start_time = cpu_time;
                    p->started = true;
                }
                int run = (p->remaining_time < quantum) ? p->remaining_time : quantum;
                p->remaining_time -= run;
                cpu_time += run;
                elapsed += run;
                printf("Time %d-%d: P%d (Q1-RR)\n", cpu_time - run, cpu_time, p->pid);
                if (p->remaining_time == 0) {
                    p->completion_time = cpu_time;
                    all_procs[all_count++] = *p;
                    q1_index++;
                }
            } else {
                break;
            }
        }
        
        elapsed = 0;
        while (elapsed < q2_slice && q2_index < q2.count) {
            Process *p = &q2.processes[q2_index];
            if (p->arrival_time <= cpu_time && p->remaining_time > 0) {
                if (!p->started) {
                    p->start_time = cpu_time;
                    p->started = true;
                }
                int run = (p->remaining_time < quantum) ? p->remaining_time : quantum;
                p->remaining_time -= run;
                cpu_time += run;
                elapsed += run;
                printf("Time %d-%d: P%d (Q2-SJF)\n", cpu_time - run, cpu_time, p->pid);
                if (p->remaining_time == 0) {
                    p->completion_time = cpu_time;
                    all_procs[all_count++] = *p;
                    q2_index++;
                }
            } else {
                break;
            }
        }
        
        elapsed = 0;
        while (elapsed < q3_slice && q3_index < q3.count) {
            Process *p = &q3.processes[q3_index];
            if (p->arrival_time <= cpu_time && p->remaining_time > 0) {
                if (!p->started) {
                    p->start_time = cpu_time;
                    p->started = true;
                }
                int run = (p->remaining_time < quantum) ? p->remaining_time : quantum;
                p->remaining_time -= run;
                cpu_time += run;
                elapsed += run;
                printf("Time %d-%d: P%d (Q3-FCFS)\n", cpu_time - run, cpu_time, p->pid);
                if (p->remaining_time == 0) {
                    p->completion_time = cpu_time;
                    all_procs[all_count++] = *p;
                    q3_index++;
                }
            } else {
                break;
            }
        }
        
        if (q1_index >= q1.count && q2_index >= q2.count && q3_index >= q3.count) {
            break;
        }
    }
    
    printf("\n=== Results Table ===\n");
    printf("%-5s %-8s %-8s %-8s %-8s %-10s\n", 
           "PID", "Arrival", "Burst", "Wait", "Turnaround", "Response");
    printf("----------------------------------------------\n");
    
    double total_wait = 0, total_turn = 0, total_resp = 0;
    
    for (int i = 0; i < all_count; i++) {
        int waiting = all_procs[i].completion_time - all_procs[i].arrival_time - all_procs[i].burst_time;
        int turnaround = all_procs[i].completion_time - all_procs[i].arrival_time;
        int response = all_procs[i].start_time - all_procs[i].arrival_time;
        
        total_wait += waiting;
        total_turn += turnaround;
        total_resp += response;
        
        printf("%-5d %-8d %-8d %-8d %-10d %-10d\n",
               all_procs[i].pid, all_procs[i].arrival_time, all_procs[i].burst_time,
               waiting, turnaround, response);
    }
    
    printf("\nAverage: Wait=%.2f, Turnaround=%.2f, Response=%.2f\n",
           total_wait / all_count, total_turn / all_count, total_resp / all_count);
    
    free(q1.processes);
    free(q2.processes);
    free(q3.processes);
    
    return 0;
}
