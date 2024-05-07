#include "dining.h"

#include <pthread.h>
#include <stdlib.h>

typedef struct dining {
  // TODO: Add your variables here
  int capacity;
  int num_students;
} dining_t;

dining_t *dining_init(int capacity) {
  // TODO: Initialize necessary variables
  dining_t *dining = malloc(sizeof(dining_t));
  dining->capacity = capacity;
  dining->num_students = 0; //Starting number of students present at dining hall
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
  /*
  void dining_student_enter(dining_t* dining) is called when a student at the reception wants to enter the dining hall. 
  If there is a room in the dining hall, this function returns. 
  If students cannot enter the dining hall, this function blocks until it becomes possible to enter.
  */
  //Need to check capacity
  if (dining->num_students == dining.capacity){
    //We need to block
    
  } 
}

void dining_student_leave(dining_t *dining) {
  // TODO: Your code goes here
}

void dining_cleaning_enter(dining_t *dining) {
  // TODO: Your code goes here
}

void dining_cleaning_leave(dining_t *dining) {
  // TODO: Your code goes here
}
