#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"


int
main(){

  int ut1,ut2,ut;

  char *argv[] = {"hello_world2",0};

  forkexec("hello_world2",argv);
  ut1 = uptime();
  for(int i = 0; i < 10000; i++)
    printf(2,"hello world\n");

  ut2 = uptime();

  ut = ut2 - ut1;
  printf(1,"The number of ticks is : %d \n ",ut);

  wait();
  exit();
}
