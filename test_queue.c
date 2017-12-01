#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"


int
main(){

  struct queue *q;
  q = malloc(sizeof(struct queue));
  q->read = -1;
  q->write = -1;
  char data[] = {'a','b','c'};
  writen2q(q,data,3);
  char temp = readq(q);
  printf(1," char at head of queue : %c \n ",temp);
  displayQueue(q);
  printf(1,"\nFine so far !!\n");

  exit();

}
