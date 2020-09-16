#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#define buffer_size 10

clock_t number_of_clocks_on_last_message;
double elapsed_time_since_last_message;

int buffer[buffer_size];

int counter = 0;
int number_of_iterations = 0;

//Flags
int producer_is_sleeping = 0;
int consumer_is_sleeping = 1;

//Functions to change flags's value
void wake_up_consumer(){
    consumer_is_sleeping = 0;
}

void wake_up_producer(){
    producer_is_sleeping = 0;
}

void put_to_sleep_consumer(){
    consumer_is_sleeping = 1;
}

void put_to_sleep_producer(){
    producer_is_sleeping = 1;
}

void* consumer_loop(){
    while (1) {
        if (consumer_is_sleeping)
        //wating then producer wakes up consumer
            continue;

        if (counter == 0){
            put_to_sleep_consumer();
            wake_up_producer();

            continue;
        }

        if (counter <= buffer_size/2){
            wake_up_producer();
        }

        //reducing buffer
        counter--;
    }
}

void* producer_loop(){
    while (1) {
        if (producer_is_sleeping)
        //wating then consumer wakes up consumer
            continue;

        if (counter >= buffer_size){
            //write message if a minute has passed since the last message
            elapsed_time_since_last_message = (double)(clock() - number_of_clocks_on_last_message) / CLOCKS_PER_SEC;
            if (elapsed_time_since_last_message >= 60){
                printf("Buffer is full %d times\n", number_of_iterations);
                number_of_clocks_on_last_message = clock();
            }
            
            number_of_iterations++;

            put_to_sleep_producer();
            wake_up_consumer();

            continue;
        }

        if (counter >= buffer_size/2){
            wake_up_consumer();
        }

        counter++;
        //filling buffer
        buffer[counter] = counter;
    }
}

int main(){
    number_of_clocks_on_last_message = clock();

    pthread_t consumer_thread;
    pthread_t producer_thread;

    pthread_create(&consumer_thread, NULL, consumer_loop, NULL);
    pthread_create(&producer_thread, NULL, producer_loop, NULL);
    
    //endless cycle
    while(1){}

    return 0;
}

