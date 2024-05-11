#include "dining.h"

#include <pthread.h>
#include <stdlib.h>

typedef struct dining {
  // TODO: Add your variables here

  int capacity;
  int num_students;
  int come_in_status;
} dining_t;

dining_t *dining_init(int capacity) {
  // TODO: Initialize necessary variables
  dining_t *dining = malloc(sizeof(dining_t));
  dining->capacity = capacity;
  dining->num_students = 0; //Starting number of students present at dining hall
  dining->come_in_status = 0;
  return dining;
}
void dining_destroy(dining_t **dining) {
  // TODO: Free dynamically allocated memory
  //Need to free students?
  
  free(*dining);
  *dining = NULL;
}

void dining_student_enter(dining_t *dining) {//Need to have threads in here? 
//will have case of capacity == 0?
//We can only have one thread operate on the dining hall at a time, must lock the dining hall

  /*
  void dining_student_enter(dining_t* dining) is called when a student at the reception wants to enter the dining hall. 
  If there is a room in the dining hall, this function returns. 
  If students cannot enter the dining hall, this function blocks until it becomes possible to enter.
  */
  //Need to check capacity
  if(dining->capacity > 0){//If capacity is zero no students can enter and no cleaning is occuring
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
    pthread_mutex_lock(&mutex);
    while(dining->come_in_status == 1){//No new students can come in
      pthread_cond_wait(&cond, &mutex);
    }
    pthread_mutex_unlock(&mutex);

    pthread_mutex_lock(&mutex);
    while(dining->num_students == dining->capacity){// 0 1 2 - two students 
      pthread_cond_wait(&cond, &mutex);
    }
    dining->num_students++;//Increase number of students present at dining hall
    pthread_mutex_unlock(&mutex);
  }
}

void dining_student_leave(dining_t *dining) {
  if(dining->num_students > 0){//Must have atleast one student
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    pthread_mutex_lock(&mutex);
    dining->num_students--;//Decrease number of student present at dining hall
    pthread_mutex_unlock(&mutex);
  }
  // TODO: Your code goes here
}
/*
Sometimes, the cleaning service provider comes in to clean the dining hall and 
calls void dining_cleaning_enter(dining_t* dining). Because they use chemicals during the process, 
students cannot be in the dining hall while the cleaning is taking place. The function blocks until all students leave. 
Once the cleaning has begun, students cannot enter the dining hall. 
Only one cleaning service provider can work in the dining hall at a time.
*/
//Need to wait till all students leave
//No new students can come in
void dining_cleaning_enter(dining_t *dining) {//Block students and new cleaners
  dining->come_in_status = 1;//Students can not come in

  pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
  pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
  pthread_mutex_lock(&mutex);

  if(dining->come_in_status == 1){
    pthread_cond_broadcast(&cond);
  }
  while(dining->num_students != 0){
    pthread_cond_wait(&cond, &mutex);
  }
  
  pthread_mutex_unlock(&mutex);
}

void dining_cleaning_leave(dining_t *dining) {
  dining->come_in_status = 0;//Students can come int
   pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
  pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
  pthread_mutex_lock(&mutex);
  if(dining->come_in_status == 0){
    pthread_cond_broadcast(&cond);
  }
  pthread_mutex_unlock(&mutex);
}
