#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"


int
main(){

  int ut1,ut2,ut;

  /*
  char *argv[] = {"hello_world2",0};

  forkexec("hello_world2",argv);
  ut1 = uptime();
  for(int i = 0; i < 10000; i++)
    printf(2,"hello world\n");

  ut2 = uptime();

  ut = ut2 - ut1;
  printf(1,"The number of ticks is : %d \n ",ut);

  */

  char *argv[] = {"test",0};

  ut1 = uptime();

  forkexec("matrix_multiply1",argv);

  forkexec("matrix_multiply2",argv);

  forkexec("matrix_multiply3",argv);

  forkexec("matrix_multiply4",argv);

  wait();
  wait();
  wait();
  wait();

  ut2 = uptime();

  ut = ut2 - ut1;

  printf(1,"The time takes in ticks is : %d \n ",ut);

  exit();
}
