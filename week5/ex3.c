#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define buffer_size 10

int buffer[buffer_size];

int counter = 0;

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
            printf("Buffer is empty\n");
            //wait until we can write another message
            sleep(60);

            put_to_sleep_consumer();
            wake_up_producer();

            continue;
        }

        printf("Consumed element: %d\n", buffer[counter]);
        //wait until we can write another message
        sleep(60);
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
            printf("Buffer is full\n");
            //wait until we can write another message
            sleep(60);

            put_to_sleep_producer();
            wake_up_consumer();

            continue;
        }

        counter++;
        //filling buffer
        buffer[counter] = counter;
    }
}

int main(){
    pthread_t consumer_thread;
    pthread_t producer_thread;

    pthread_create(&consumer_thread, NULL, consumer_loop, NULL);
    pthread_create(&producer_thread, NULL, producer_loop, NULL);
    
    //endless cycle
    while(1){}

    return 0;
}

