#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct process
{
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int is_done;
    int remaining_execution_time;
};

struct process processes[100];

int compare_by_arrival_time(const void* a, const void* b){
    struct process processA = *(struct process*)a;
    struct process processB = *(struct process*)b;

    if (processA.is_done)
        return 1;

    if (processB.is_done)
        return -1;

    return (processA.arrival_time - processB.arrival_time);
}

int get_index_of_last_arrived_process_to_the_time(int current_time, int number_of_procosses){
    for (int i = number_of_procosses - 1; i > -1; i--)
    {
        if (processes[i].arrival_time <= current_time && !processes[i].is_done)
            return i;
    }
    
    return -1;
}

int main(){
    double average_turnaround_time = 0;
    double average_waiting_time = 0;

    printf("Enter number of processes: ");
    int number_of_processes;
    scanf("%d",&number_of_processes);

    printf("Enter quantum size: ");
    int quant;
    scanf("%d", &quant);

    printf("Enter Arrival time and Burst time for each process: \n");
    for (size_t i = 0; i < number_of_processes; i++)
    {
        printf("Arrival time of process[%ld]: ", i+1);
        scanf("%d", &(processes[i].arrival_time));

        printf("Burst time of process[%ld]: ", i+1);
        scanf("%d", &(processes[i].burst_time));

        processes[i].is_done = 0;
        processes[i].remaining_execution_time = processes[i].burst_time;
    }

    qsort(processes, number_of_processes, sizeof(struct process), compare_by_arrival_time);
    int current_time = 0;
    int index_of_last_arrived_process_by_this_time;

    int done_process_counter = 0;
    int i = 0;

    printf("P#\tAT\tBT\tCT\tTAT\tWT\n\n");
    while (1)
    {
        qsort(processes, number_of_processes, sizeof(struct process), compare_by_arrival_time);

        if (processes[0].is_done)
            break;


        index_of_last_arrived_process_by_this_time = get_index_of_last_arrived_process_to_the_time(current_time, number_of_processes);

        while (index_of_last_arrived_process_by_this_time == -1)
        {
            current_time++;
            index_of_last_arrived_process_by_this_time = get_index_of_last_arrived_process_to_the_time(current_time, number_of_processes);
        }
        
        if (i > index_of_last_arrived_process_by_this_time)
            i = 0;

        if (quant >= processes[i].remaining_execution_time){
            current_time += processes[i].remaining_execution_time;

            processes[i].remaining_execution_time = 0;
            processes[i].completion_time = current_time;
            processes[i].turnaround_time = current_time - processes[i].arrival_time;
            processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
            processes[i].is_done = 1;

            average_turnaround_time += processes[i].turnaround_time;
            average_waiting_time += processes[i].waiting_time;

            done_process_counter++;
            printf("P%d\t%d\t%d\t%d\t%d\t%d\n", done_process_counter, processes[i].arrival_time, processes[i].burst_time, processes[i].completion_time, processes[i].turnaround_time, processes[i].waiting_time);
        }
        else{
            current_time += quant;

            processes[i].remaining_execution_time -= quant;
            
            i++;
        }
    }

    average_waiting_time /= number_of_processes;
    average_turnaround_time /= number_of_processes;

    printf("\n");
    printf("Average Turnaround Time = %lf\n", average_turnaround_time);
    printf("Average Waiting Time = %lf\n", average_waiting_time);

    return 0;
}

/*
number of processes: 3
quantum size: 2 (For the RR algorithm)
Arrival time of process[1]: 0
Burst time of process[1]: 4
Arrival time of process[2]: 1
Burst time of process[2]: 4
Arrival time of process[3]: 2
Burst time of process[3]: 6

FCFS output:

SJN output:

RR output:
P#      AT      BT      CT      TAT     WT

P1      0       4       8       8       4
P2      1       4       10      9       5
P3      2       6       14      12      6

Average Turnaround Time = 9.666667
Average Waiting Time = 5.000000
*/