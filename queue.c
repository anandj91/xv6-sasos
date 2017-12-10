#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"
#include "x86.h"

#define N 100


struct queue{
  int read;
  int write;
  char buff[N];
};


typedef struct queue queue;


void write(queue *q, char data){

  // if buffer is full
  if ((q->read == 0 && q->write == N-1) || (q->read == q->write + 1)){
    printf(1,"Buffer Overlfow \n");
    exit();
  }

  // If buffer is currently empty
  else if (q->read == -1){
    q->read = q->write = 0;
    q->buff[q->write] = data;
  }

  // Wrap around the buffer
  else if( q->write == N-1 && q->read!=0){
    q->write = 0;
    q->buff[q->write] = data;
  }

  else{
    q->write += 1;
    q->buff[q->write] = data;
  }


}

char read(queue *q){

  // No element in the buffer
  if (q->read == -1)
  {
    printf(1,"Buffer Underflow \n");
    exit();
  }

  char data = q->buff[q->read];

  // should the read element be replaced by -1?

  if (q->read == q->write)
  {
    q->read = -1;
    q->write = -1;
  }

  // Wrap around
  else if (q->read == N-1)
    q->read = 0;
  else
    q->read += 1;

  return data;
}


void writen(queue *q, char data[], int n = -1){

  if ( n == -1){
    n = strlen(data);
  }

  if (n < 0){
    printf(1,"Unexpected negative length \n");
    exit();
  }

  // Write n charecters into the buffer
  for(int i = 0; i < n; i++){
    write(q,data[i]);
  }

  return;

}


void readn(queue *q, char data[], int n){

  for(int i = 0; i < n; i++)
    data[i] = read(q);

  return;

}


void displayQueue(queue q)
{
  if (q->read == -1)
  {
    printf(1,"Empty Buffer \n");
    exit();
  }

  printf(1,"Displaying Elements : \n ");

  if (q->write >= q->read)
  {
    for (int i = q->read; i <= q->write; i++)
      printf(1,"%c ",q->buff[i]);
  }
  else
  {
    for (int i = q->read; i < N; i++)
      printf(1,"%c ", q->buff[i]);

    for (int i = 0; i <= q->write; i++)
      printf(1,"%c ", q->buff[i]);
  }

  return;
}
