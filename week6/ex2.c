#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define max(a,b) (((a)>(b))?(a):(b))

struct process
{
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

struct process processes[100];

int compare_by_arrival_time(const void* a, const void* b){
    return (((struct process*)a)->arrival_time - ((struct process*)b)->arrival_time);
}

int compare_by_burst_time(const void* a, const void* b){
    return (((struct process*)a)->burst_time - ((struct process*)b)->burst_time);
}

int get_index_of_last_arrived_process_to_the_time(int current_time, int number_of_procosses){
    for (int i = number_of_procosses - 1; i > -1; i--)
    {
        if (processes[i].arrival_time <= current_time)
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

    printf("Enter Arrival time and Burst time for each process: \n");
    for (size_t i = 0; i < number_of_processes; i++)
    {
        printf("Arrival time of process[%ld]: ", i+1);
        scanf("%d", &(processes[i].arrival_time));

        printf("Burst time of process[%ld]: ", i+1);
        scanf("%d", &(processes[i].burst_time));
    }

    qsort(processes, number_of_processes, sizeof(struct process), compare_by_arrival_time);
    int current_time = 0;
    int index_of_last_arrived_process_by_this_time;

    printf("P#\tAT\tBT\tCT\tTAT\tWT\n\n");
    for (size_t i = 0; i < number_of_processes; i++)
    {
        qsort(processes, number_of_processes, sizeof(struct process), compare_by_arrival_time);
        index_of_last_arrived_process_by_this_time = get_index_of_last_arrived_process_to_the_time(current_time, number_of_processes);

        while (index_of_last_arrived_process_by_this_time == -1)
        {
            current_time++;
            index_of_last_arrived_process_by_this_time = get_index_of_last_arrived_process_to_the_time(current_time, number_of_processes);
        }
        

        qsort(processes, index_of_last_arrived_process_by_this_time + 1, sizeof(struct process), compare_by_burst_time);

        current_time = processes[0].burst_time + max(processes[0].arrival_time, current_time);
        processes[0].completion_time = current_time;
        processes[0].turnaround_time = current_time - processes[0].arrival_time;
        processes[0].waiting_time = processes[0].turnaround_time - processes[0].burst_time;

        printf("P%ld\t%d\t%d\t%d\t%d\t%d\n", i+1, processes[0].arrival_time, processes[0].burst_time, processes[0].completion_time, processes[0].turnaround_time, processes[0].waiting_time);

        average_turnaround_time += processes[0].turnaround_time;
        average_waiting_time += processes[0].waiting_time;
        
        processes[0].arrival_time = INT_MAX;
        processes[0].burst_time = INT_MAX;
    }

    average_waiting_time /= number_of_processes;
    average_turnaround_time /= number_of_processes;

    printf("\n");
    printf("Average Turnaround Time = %lf\n", average_turnaround_time);
    printf("Average Waiting Time = %lf\n", average_waiting_time);

    return 0;
}