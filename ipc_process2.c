#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"


char *argv[] = {"ipc_process1",0};

int
main(int argc, char *argv[])
{

  //int pid;

  // for parent to write and child to read
  int ip[2] = {3,4};

  // for child to write and parent to read
  int op[2] = {5,6};



  int count = atoi(argv[1]);
  // Write and read variable
  int buf_size = 7;
  //char buffer[20] = "2000000";
  char readbuff[20];
  int readnum;

  //printf(1," in ipc 2 \n");

  for(int i = 0; i < count; i++){

    if(read(ip[0], readbuff, buf_size) != buf_size ){
      printf(1,"error in read for child !!!!");
      exit();
    }


    readnum = atoi(readbuff);

    //printf(1,"Number is(c) : %d \n", readnum);

    readnum++;

    itoa(readnum, readbuff, 10);

    if(write(op[1], readbuff, buf_size) != buf_size ){
      printf(1,"error in write for child !!!!");
      exit();
    }
  }
  
  exit();

}
