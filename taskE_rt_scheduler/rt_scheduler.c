#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

typedef struct {
    int id;
    int period;
    int execution_time;
    int deadline;
    int arrival_time;
    int remaining_time;
    bool ready;
    int absolute_deadline;
} Task;

double rm_bound(int n) {
    return n * (pow(2.0, 1.0 / n) - 1.0);
}

int select_rm_task(Task *tasks, int n) {
    int best_task = -1;
    int highest_priority = 999999;
    
    for (int i = 0; i < n; i++) {
        if (tasks[i].ready && tasks[i].remaining_time > 0) {
            if (tasks[i].period < highest_priority) {
                highest_priority = tasks[i].period;
                best_task = i;
            }
        }
    }
    return best_task;
}

int select_edf_task(Task *tasks, int n) {
    int best_task = -1;
    int earliest_deadline = 999999;
    
    for (int i = 0; i < n; i++) {
        if (tasks[i].ready && tasks[i].remaining_time > 0) {
            if (tasks[i].absolute_deadline < earliest_deadline) {
                earliest_deadline = tasks[i].absolute_deadline;
                best_task = i;
            }
        }
    }
    return best_task;
}

void simulate_sched(Task *tasks, int n, char *mode) {
    int hyper_period = 60;
    
    printf("\n=== %s Simulation ===\n", mode);
    printf("Hyper Period: %d\n", hyper_period);
    
    for (int t = 0; t < hyper_period; t++) {
        for (int i = 0; i < n; i++) {
            if (t % tasks[i].period == 0) {
                tasks[i].ready = true;
                tasks[i].remaining_time = tasks[i].execution_time;
                tasks[i].absolute_deadline = t + tasks[i].deadline;
            }
        }
        
        int selected = -1;
        if (strcmp(mode, "EDF") == 0) {
            selected = select_edf_task(tasks, n);
        } else {
            selected = select_rm_task(tasks, n);
        }
        
        if (selected >= 0) {
            printf("Time %2d: Task %d executing (deadline=%d)\n", 
                   t, tasks[selected].id, tasks[selected].absolute_deadline);
            tasks[selected].remaining_time--;
            
            if (t + 1 > tasks[selected].absolute_deadline) {
                printf("  WARNING: Deadline missed for Task %d at time %d!\n",
                       tasks[selected].id, t + 1);
            }
            
            if (tasks[selected].remaining_time == 0) {
                tasks[selected].ready = false;
            }
        }
    }
}

int main() {
    printf("=== Real-Time Scheduler & Schedulability Analyzer ===\n\n");
    
    Task tasks[] = {
        {1, 5, 2, 5, 0, 2, false, 0},
        {2, 10, 4, 10, 0, 4, false, 0},
        {3, 20, 1, 20, 0, 1, false, 0}
    };
    int n = 3;
    
    printf("Task Set:\n");
    printf("Task  Period  Exec  Deadline\n");
    printf("----  ------  ----  --------\n");
    for (int i = 0; i < n; i++) {
        printf("%d     %d       %d     %d\n",
               tasks[i].id, tasks[i].period, tasks[i].execution_time, tasks[i].deadline);
    }
    
    double total_util = 0.0;
    for (int i = 0; i < n; i++) {
        total_util += (double)tasks[i].execution_time / tasks[i].period;
    }
    double bound = rm_bound(n);
    
    printf("\n=== Schedulability Analysis ===\n");
    printf("RM Test: Utilization U=%.2f, Bound=%.2f\n", total_util, bound);
    printf("EDF Test: Utilization U=%.2f, Bound=1.0\n", total_util);
    
    printf("\nRM is %s\n", total_util <= bound ? "feasible" : "NOT guaranteed feasible");
    printf("EDF is %s\n", total_util <= 1.0 ? "feasible" : "NOT guaranteed feasible");
    
    printf("\nNote: For n=3, RM bound is %.3f, total utilization is 0.85 > 0.779\n", bound);
    printf("So RM is inconclusive - running simulation to check.\n\n");
    
    Task tasks_rm[] = {
        {1, 5, 2, 5, 0, 2, false, 0},
        {2, 10, 4, 10, 0, 4, false, 0},
        {3, 20, 1, 20, 0, 1, false, 0}
    };
    simulate_sched(tasks_rm, n, "RM");
    
    Task tasks_edf[] = {
        {1, 5, 2, 5, 0, 2, false, 0},
        {2, 10, 4, 10, 0, 4, false, 0},
        {3, 20, 1, 20, 0, 1, false, 0}
    };
    simulate_sched(tasks_edf, n, "EDF");
    
    printf("\n=== Summary ===\n");
    printf("With U=0.85:\n");
    printf("- RM (bound 0.779): May fail - run simulation to check\n");
    printf("- EDF (bound 1.0): Guaranteed feasible\n");
    
    return 0;
}
