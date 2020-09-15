#include <stdio.h>
#include <string.h>
#include <pthread.h>

#define number_of_threads 10
pthread_mutex_t mutex;

void* print_messages_from_thread (void* id){
  //Print message from thread
  printf("Hello from %ld thread\n", (size_t) id);

  //Print that thread exits
  printf("Tread %ld exits\n", (size_t) id);

  pthread_mutex_unlock(&mutex);

  // Return reference
  void* retval;
  pthread_exit(&retval);

}

void* main_without_sync(){
    pthread_t threads [number_of_threads];

    for (size_t id = 0; id < number_of_threads; ++id){
        //Create the thread
        pthread_create(&threads[id], NULL, print_messages_from_thread, (void *) id);
        //Print that thread is created
        printf("Thread %ld was created\n", id);
    }

    for (size_t id = 0; id < number_of_threads; ++id){
        pthread_join(threads[id], NULL);
    }
}

void* main_with_sync(){
    pthread_t threads [number_of_threads];
    //mitex initialization
    pthread_mutex_init(&mutex, NULL);

    for (size_t id = 0; id < number_of_threads; ++id){
        pthread_mutex_lock(&mutex);
        //Create the thread
        pthread_create(&threads[id], NULL, print_messages_from_thread, (void *) id);
        //Print that thread is created
        printf("Thread %ld was created\n", id);
    }

    for (size_t id = 0; id < number_of_threads; ++id){
        pthread_join(threads[id], NULL);
    }

    //mutex destruction
    pthread_mutex_destroy(&mutex);
}

int main(void){
    printf("Threads without synchronization\n");
    main_without_sync();

    printf("Threads using synchronization\n");
    main_with_sync();

    return 0;
}