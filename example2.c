#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#include "dining.h"
#include "utils.h"

void* student_thread(void* arg) {
  student_t* student = (student_t*)arg;
  student_enter(student);
  // printf("Student entered the dining hall.\n");
  msleep(2000);  // Simulating student eating time
  student_leave(student);
  // printf("Student  left the dining hall.\n");
  return NULL;
}

void* cleaning_thread(void* arg) {
  cleaning_t* cleaning = (cleaning_t*)arg;
  // printf("Cleaning service provider entered the dining hall.\n");
  cleaning_enter(cleaning);
  // printf("Cleaning service provider started cleaning.\n");
  msleep(3000);  // Simulating cleaning time
  cleaning_leave(cleaning);
  // printf("Cleaning service provider left the dining hall.\n");
  return NULL;
}

int main(void) {
  dining_t* d = dining_init(3);

  // Create students
  student_t students[5];
  for (int i = 0; i < 5; i++) {
    students[i] = make_student(i + 1, d);
  }

  // Create cleaners
  cleaning_t cleaning1 = make_cleaning(1, d);
  cleaning_t cleaning2 = make_cleaning(2, d);

  // Students and cleaners enter and leave in a complex sequence
  pthread_t student_threads[5];
  pthread_t cleaning_threads[2];

  pthread_create(&student_threads[0], NULL, student_thread, &students[0]);
  msleep(500);  // To stagger student entry

  pthread_create(&cleaning_threads[0], NULL, cleaning_thread, &cleaning1);
  msleep(500);  // To ensure cleaning thread is blocked

  pthread_create(&student_threads[1], NULL, student_thread, &students[1]);
  msleep(500);

  pthread_create(&cleaning_threads[1], NULL, cleaning_thread, &cleaning2);
  msleep(500);

  pthread_create(&student_threads[2], NULL, student_thread, &students[2]);
  msleep(500);

  pthread_create(&student_threads[3], NULL, student_thread, &students[3]);
  msleep(500);

  pthread_create(&student_threads[4], NULL, student_thread, &students[4]);
  msleep(500);

  // Wait for all threads to finish

  for (int i = 0; i < 2; i++) {
    pthread_join(cleaning_threads[i], NULL);
  }
  for (int i = 0; i < 5; i++) {
    pthread_join(student_threads[i], NULL);
  }

  // Destroy dining hall
  dining_destroy(&d);

  return 0;
}
