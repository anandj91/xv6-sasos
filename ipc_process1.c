#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"


char *argvc[] = {"ipc_process2",0};

int
main(int argc, char *argv[])
{

  //int pid;
  int ut1;
  int ut2;
  int ut;
  // for parent to write and child to read
  int ip[2] = {3,4};

  // for child to write and parent to read
  int op[2] = {5,6};


  int count = atoi(argv[1]);
  int buf_size = 7;
  char buffer[15] = "0000000";
  char readbuff[20];
  int readnum;

  //printf(1,"in ipc 1 \n");

  // Creating pipes
  if(pipe(ip) == -1){
    printf(1, " Error in creating pipe \n");
    exit();
  }

  if(pipe(op) == -1){
    printf(1, "Error in creating pipe #2 \n ");
    exit();
  }

  argvc[1] = argv[1];
  forkexec("ipc_process2", argvc);


  ut1 = uptime();
  for(int i = 0; i < count; i++){
    // Write into pipe 1
    if(write(ip[1], buffer, buf_size) != buf_size){
      printf(1," Error in write");
      exit();

    }


    // Read from the child pipe

    if(read(op[0],readbuff,buf_size) != buf_size){
      printf(1,"\n Error in read by parent");
      exit();
    }

    //printf(1,"\n Parent read : %s \n", readbuff);
    readnum = atoi(readbuff);
    //printf(1,"Number is(p) : %d \n", readnum);

    readnum += 2;

    itoa(readnum, buffer, 10);


  }
  ut2 = uptime();

  ut = ut2 - ut1;

  printf(1,"The time in ticks is  : %d \n",ut);
  printf(1,"The values of count is :  %d  \n",count);



  //printf(1,"\n Out of the loop \n");
  //
  wait();
  exit();
}
