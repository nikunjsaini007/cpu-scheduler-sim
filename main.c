#include <stdio.h>
#include <windows.h>

#define RESET "\033[0m"

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define CYAN "\033[1;36m"
#define MAGENTA "\033[1;35m"
#define WHITE "\033[1;37m"

typedef struct
{
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
} Process;

typedef struct
{
    int id;
    int busy;
    int current_process;
} Core;

typedef struct
{
    int items[100];
    int front;
    int rear;
} Queue;

Process processes[100];
Core cpu_cores[10];
Queue ready_queue;

int process_count = 0;

void enqueue(Queue *q, int process_index)
{
    if (q->rear < 99)
    {
        q->rear++;
        q->items[q->rear] = process_index;
    }
}

int dequeue(Queue *q)
{
    int item = q->items[q->front];
    q->front++;
    return item;
}

int isEmpty(Queue *q)
{
    return q->front > q->rear;
}

int main()
{
    FILE *file = fopen("input.txt", "r");

    if (file == NULL)
    {
        printf("Error Opening File!\n");
        return 1;
    }

    int time = 0;
    int completed = 0;
    char algo[20];
    int cores;

    int timeline[10000];
    int t_index = 0;

    fscanf(file, "%s", algo);
    fscanf(file, "%d", &cores);

    ready_queue.front = 0;
    ready_queue.rear = -1;

    for (int i = 0; i < cores; i++)
    {
        cpu_cores[i].id = i + 1;
        cpu_cores[i].busy = 0;
        cpu_cores[i].current_process = -1;
    }

    printf("\033[2J\033[H");

    printf(CYAN "\n====================================================\n" RESET);
    printf(CYAN "        SYSTEM TASK MANAGER :: CPU CORE VIEW\n" RESET);
    printf(CYAN "====================================================\n\n" RESET);

    printf(YELLOW ">> EXECUTION PROFILE : " RESET "%s\n", algo);
    printf(YELLOW ">> ACTIVE PROCESSORS : " RESET "%d CORES\n\n", cores);

    int pid, arrival, burst;

    while (fscanf(file, "%d %d %d", &pid, &arrival, &burst) == 3)
    {
        processes[process_count].pid = pid;
        processes[process_count].arrival_time = arrival;
        processes[process_count].burst_time = burst;
        processes[process_count].remaining_time = burst;
        processes[process_count].completion_time = 0;
        process_count++;
    }

    fclose(file);

    if (process_count == 0)
    {
        printf("No processes found.\n");
        return 0;
    }

    while (completed < process_count)
    {
        for (int i = 0; i < process_count; i++)
        {
            if (processes[i].arrival_time == time)
            {
                enqueue(&ready_queue, i);
            }
        }

        for (int i = 0; i < cores; i++)
        {
            if (cpu_cores[i].busy == 0 && !isEmpty(&ready_queue))
            {
                int p = dequeue(&ready_queue);
                cpu_cores[i].current_process = p;
                cpu_cores[i].busy = 1;
            }

            if (cpu_cores[i].busy == 1)
            {
                int p = cpu_cores[i].current_process;

                processes[p].remaining_time--;
                timeline[t_index++] = p;

                printf(GREEN "[SYSTEM TIME %d ms] " RESET, time);
                printf(BLUE "CORE-%d ACTIVE " RESET, cpu_cores[i].id);
                printf(WHITE ">> EXECUTING " RESET);
                printf(MAGENTA "PROCESS P%d\n" RESET, processes[p].pid);

                if (processes[p].remaining_time == 0)
                {
                    processes[p].completion_time = time + 1;
                    completed++;

                    cpu_cores[i].busy = 0;
                    cpu_cores[i].current_process = -1;
                }
            }
        }

        time++;
    }

    printf(CYAN "\n====================================================\n" RESET);
    printf(CYAN "        PROCESS EXECUTION TIMELINE MAP\n" RESET);
    printf(CYAN "====================================================\n\n" RESET);

    for (int i = 0; i < t_index; i++)
    {
        printf("| P%-2d ", processes[timeline[i]].pid);
    }
    printf("|\n");

    for (int i = 0; i < t_index; i++)
    {
        printf("+-----");
    }
    printf("+\n");

    for (int i = 0; i < t_index; i++)
    {
        printf("|  ██  ");
    }
    printf("|\n");

    for (int i = 0; i < t_index; i++)
    {
        printf("+-----");
    }
    printf("+\n");

    printf("0");
    for (int i = 0; i < t_index; i++)
    {
        printf("     %d", i + 1);
    }
    printf("\n");

    int total_time = time;

    printf(MAGENTA "\n\n====================================================\n" RESET);
    printf(MAGENTA "        PROCESS PERFORMANCE SNAPSHOT\n" RESET);
    printf(MAGENTA "====================================================\n\n" RESET);

    double total_wt = 0, total_tat = 0;

    for (int i = 0; i < process_count; i++)
    {
        processes[i].turnaround_time =
            processes[i].completion_time - processes[i].arrival_time;

        processes[i].waiting_time =
            processes[i].turnaround_time - processes[i].burst_time;

        total_wt += processes[i].waiting_time;
        total_tat += processes[i].turnaround_time;

        printf("PROCESS P%d | CT=%d | TAT=%d | WT=%d\n",
               processes[i].pid,
               processes[i].completion_time,
               processes[i].turnaround_time,
               processes[i].waiting_time);
    }

    printf(YELLOW "\n====================================================\n" RESET);
    printf(YELLOW "        SYSTEM PERFORMANCE METRICS\n" RESET);
    printf(YELLOW "====================================================\n\n" RESET);

    printf("AVG WAIT TIME      : %.2f ms\n", total_wt / process_count);
    printf("AVG TURNAROUND TIME: %.2f ms\n", total_tat / process_count);
    printf("THROUGHPUT         : %.2f proc/unit\n",
           (float)process_count / total_time);
    printf("CPU UTILIZATION    : %.2f%%\n",
           ((float)t_index / total_time) * 100);

    printf(GREEN "\n====================================================\n" RESET);
    printf(GREEN "        SYSTEM SHUTDOWN :: EXECUTION COMPLETE\n" RESET);
    printf(GREEN "====================================================\n" RESET);

    return 0;
}