#include <stdio.h>
#include <stdlib.h>

struct process
{
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

int compare(const void* a, const void* b){
    return ((*(struct process*)a).arrival_time - (*(struct process*)b).arrival_time);
}


int main(){
    struct process processes[100];
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

    qsort(processes, number_of_processes, sizeof(struct process), compare);

    printf("P#\tAT\tBT\tCT\tTAT\tWT\n\n");
    for (size_t i = 0; i < number_of_processes; i++)
    {
        if (i == 0){
            processes[i].completion_time = processes[i].burst_time + processes[i].arrival_time;
            processes[i].turnaround_time = processes[i].burst_time;
            processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
        }
        else{
            if (processes[i].arrival_time > processes[i-1].completion_time){
                processes[i].completion_time = processes[i].arrival_time + processes[i].burst_time;
            }
            else{
                processes[i].completion_time = processes[i-1].completion_time + processes[i].burst_time;
            }
            processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
            processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
        }

        printf("P%ld\t%d\t%d\t%d\t%d\t%d\n", i+1, processes[i].arrival_time, processes[i].burst_time, processes[i].completion_time, processes[i].turnaround_time, processes[i].waiting_time);

        average_turnaround_time += processes[i].turnaround_time;
        average_waiting_time += processes[i].waiting_time;
    }

    average_turnaround_time /= number_of_processes;
    average_waiting_time /= number_of_processes;

    printf("\n");
    printf("Average Turnaround Time = %lf\n", average_turnaround_time);
    printf("Average Waiting Time = %lf\n", average_waiting_time);

    return 0;
}