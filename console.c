#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

#define VIDEO_GAME_TIME 2
#define MAX_REPORTS 3 // change this if things are taking too long.

int num_reports = 0;

void *thread(void *arg) {
  int thread_num = *(int*)arg;
  printf("Thread %d says it's their turn on the console!\n", thread_num);
  // leave the above outside of any locks.

  /* while (... some condition ...) {
    if (num_reports < MAX_NUM_REPORTS) {
      printf("Sibling %d told your parents!\n", thread_num);
      num_reports++;
    }
    pthread_cond_wait(<sibling cond>, <lock>);
  } */

  printf("Thread %d is on the video game console!\n", thread_num);
  while (1) {
    sleep(VIDEO_GAME_TIME);
    //pthread_mutex_lock(<lock>);
    //pthread_cond_signal(<sibling signal>); force the "report" count to go up!

    // if (check to see if there are too many reports against you) {
    //  printf("Thread %d has been kicked off the PS5!\n", thread_num);
    //  num_reports = 0; // LEAVE THIS! We want to reset the reports for each sibling!
    //  break;
    // }

    printf("Thread %d decides to stay on the PS5 for a bit longer! Daring!\n", thread_num);
  }

}


int main() {
  pthread_t tid[10];
  int i = 0;
  int ids[] = {1, 2, 3, 4, 5};

  pthread_create(&tid[i++], NULL, thread, (void*)&ids[0]);
  pthread_create(&tid[i++], NULL, thread, (void*)&ids[1]);
  sleep(4);
  pthread_create(&tid[i++], NULL, thread, (void*)&ids[2]);
  sleep(2);
  pthread_create(&tid[i++], NULL, thread, (void*)&ids[3]);
  sleep(5);
  pthread_create(&tid[i++], NULL, thread, (void*)&ids[4]);
  sleep(10);

  // don't wait on the last thread to emphasize threads could truly go forever
  for (int j = 0; j < i - 1; j++) {
    pthread_join(tid[j], NULL);
  }
  return 0;
}
