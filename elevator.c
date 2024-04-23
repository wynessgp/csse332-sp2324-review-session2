#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include <pthread.h>

#define MAX_ELEVATOR_CAPACITY 4
#define GROUND_FLOOR_TRAVEL_TIME 2
#define SECOND_FLOOR_TRAVEL_TIME 3 

#define GROUND_FLOOR 0
#define SECOND_FLOOR 1

int cur_floor = GROUND_FLOOR;

// you'll need to update these yourself to ensure that the scenarios validate correctly
int total_trips = 0; // meant to be the number of times the elevator goes up OR down
int total_passengers = 0; // total number of passengers who got on the elevator

void *ground_floor(void *arg) {
  unsigned long long tid = (unsigned long long) arg;
  printf("Ground floor customer %llu arrived!\n", tid);

  // TODO: Use this print to indicate a customer gets on the elevator
  // printf("Ground floor customer %llu is on the elevator!\n", tid);

  // TODO: Uncomment and print these when the time is right!
  // printf("Elevator is leaving the ground floor...\n");
  // printf("\nElevator has reached the second floor, and everyone is off!\n\n")

  // TODO: Increment total_trips, total_passengers when the time is right!

  sleep(GROUND_FLOOR_TRAVEL_TIME);

  printf("Ground floor customer %llu is leaving the elevator!\n", tid);

  return NULL;
}

void *second_floor(void *arg) {
  unsigned long long tid = (unsigned long long) arg;
  printf("Second floor customer %llu arrived!\n", tid);

  // TODO: Use this print to indicate a customer gets on the elevator
  // printf("Second floor customer %llu is on the elevator!\n", tid);

  // TODO: Uncomment me when the time is right!
  // printf("Elevator is leaving the second floor...\n");
  // printf("\nElevator has reached the ground floor, and everyone is off!\n\n")

  // TODO: Increment total_trips, total_passengers when the time is right!
  sleep(SECOND_FLOOR_TRAVEL_TIME);

  printf("Second floor customer %llu is leaving the elevator!\n", tid);

  return NULL;
}

void scenario_one(void);
void scenario_two(void);
void scenario_three(void);

static void (*test_funcs[])(void) = {
  scenario_one,
  scenario_two,
  scenario_three,
};

int main(int argc, char **argv) {
  int scenario = 1;

  if (argc > 1)
    scenario = atoi(argv[1]);

  if (scenario < 1 || scenario > 3) {
    printf("proper usage: ./elevator.bin [1, 3]\n");
    exit(999);
  }

  printf("===== Running scenario %d =====\n", scenario);
  test_funcs[scenario - 1]();

  exit(0);
}

void scenario_one(void) {
  unsigned long long i;
  const int num_per_floor = 4;
  pthread_t ground_floor_thr[num_per_floor];
  pthread_t second_floor_thr[num_per_floor];
  for (i = 0; i < num_per_floor; i++) {
    pthread_create(&second_floor_thr[i], 0, second_floor, (void*)(i+1));
  }

  sleep(3);

  for (i = 0; i < num_per_floor; i++) {
    pthread_create(&ground_floor_thr[i], 0, ground_floor, (void*)(i+1));
  }


  for (i = 0; i < num_per_floor; i++) {
    pthread_join(ground_floor_thr[i], 0);
    pthread_join(second_floor_thr[i], 0);
  } 

  printf("\n===== [Scenario 1] Everything finished =====\n");
  printf("Should have 8 passengers making 2 trips, elevator at ground floor. \n\nVerification:\n");
  
  if (total_trips == 2) {
    printf("Trips: PASSED\n");
  } else {
    printf("Trips: FAILED. Yours: %d\n", total_trips);
  }

  if (total_passengers == 8) {
    printf("Passengers: PASSED\n");
  } else {
    printf("Passengers: FAILED. Yours: %d\n", total_passengers);
  }

  if (cur_floor == GROUND_FLOOR) {
    printf("Elevator position: PASSED\n");
  } else {
    printf("Elevator position: FAILED. Yours: %d\n", cur_floor);
  } 
}

void scenario_two(void) {
  unsigned long long i = 0;
  const int num_per_floor = 8;
  pthread_t threads[num_per_floor * 2]; // elevator will go up twice, down twice.

  // force the elevator to go to the second floor
  pthread_create(&threads[i], 0, ground_floor, (void*)i+1); i++;
  pthread_create(&threads[i], 0, ground_floor, (void*)i+1); i++;
  pthread_create(&threads[i], 0, ground_floor, (void*)i+1); i++;
  pthread_create(&threads[i], 0, ground_floor, (void*)i+1); i++;

  // let some other people arrive too
  pthread_create(&threads[i], 0, second_floor, (void*)i+1); i++;
  pthread_create(&threads[i], 0, second_floor, (void*)i+1); i++;
  pthread_create(&threads[i], 0, ground_floor, (void*)i+1); i++;

  sleep(4); // ensure the elevator is stuck trying to go down from the second floor.
  
  // release the elevator from the second floor
  pthread_create(&threads[i], 0, second_floor, (void*)i+1); i++;
  pthread_create(&threads[i], 0, second_floor, (void*)i+1); i++;

  // let two more people arrive on the ground floor
  pthread_create(&threads[i], 0, ground_floor, (void*)i+1); i++;
  pthread_create(&threads[i], 0, ground_floor, (void*)i+1); i++;

  // make sure we make it to the ground floor
  sleep(4);

  // make a bunch of second floor people arrive first
  for (int j = 0; j < 3; j++) {
    pthread_create(&threads[i], 0, second_floor, (void*)i+1);
    i++;
  }

  // last ground floor person arrives
  pthread_create(&threads[i], 0, ground_floor, (void*)i+1); i++;

  // wait a little longer
  sleep(2);

  // last second floor person arrives
  pthread_create(&threads[i], 0, second_floor, (void*)i+1); i++;

  // do our joins before we check
  for (int j = 0; j < num_per_floor * 2; j++) {
    pthread_join(threads[j], 0);
  }
  
  printf("\n===== [Scenario 2] Everything finished =====\n");
  printf("Should have 16 passengers making 4 trips, elevator at ground floor.  \n\nVerification:\n");
  
  if (total_trips == 4) {
    printf("Trips: PASSED\n");
  } else {
    printf("Trips: FAILED. Yours: %d\n", total_trips);
  }

  if (total_passengers == 16) {
    printf("Passengers: PASSED\n");
  } else {
    printf("Passengers: FAILED. Yours: %d\n", total_passengers);
  }

  if (cur_floor == GROUND_FLOOR) {
    printf("Elevator position: PASSED\n");
  } else {
    printf("Elevator position: FAILED. Yours: %d\n", cur_floor);
  }
}

void scenario_three(void) {
  unsigned long long i = 0;
  const int num_floor_passengers = 8;
  pthread_t threads[num_floor_passengers * 2];

  // all of the second floor passengers arrive at once, but will be blocked
  for (i = 0; i < num_floor_passengers; i++) {
    pthread_create(&threads[i], 0, second_floor, (void*)(i+1));
  }

  // artifical delay
  sleep(2);

  // make enough ground floor passengers arrive to make the elevator move
  for (; i < num_floor_passengers + 5; i++) {
    pthread_create(&threads[i], 0, ground_floor, (void*)(i+1));
  }

  sleep(5); // artificial delay; elevator should go up and then come back down
  // note that there should still be second floor passengers waiting at this point

  // make the last ground floor passengers arrive.
  for (; i < num_floor_passengers * 2; i++) {
    pthread_create(&threads[i], 0, ground_floor, (void*)(i+1));
  }

  // second floor trip should happen downwards after this as well
  for (i = 0; i < num_floor_passengers * 2; i++) {
    pthread_join(threads[i], 0);
  }

  printf("\n===== [Scenario 3] Everything finished =====\n");
  printf("Should have 16 passengers making 4 trips, elevator at ground floor.  \n\nVerification:\n");
  
  if (total_trips == 4) {
    printf("Trips: PASSED\n");
  } else {
    printf("Trips: FAILED. Yours: %d\n", total_trips);
  }

  if (total_passengers == 16) {
    printf("Passengers: PASSED\n");
  } else {
    printf("Passengers: FAILED. Yours: %d\n", total_passengers);
  }

  if (cur_floor == GROUND_FLOOR) {
    printf("Elevator position: PASSED\n");
  } else {
    printf("Elevator position: FAILED. Yours: %d\n", cur_floor);
  }
}
