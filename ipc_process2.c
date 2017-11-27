#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"


char *argv[] = {"ipc_process1",0};

void reverse(char s[])
{
  int i, j;
  char c;
 
  for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}

void itoa(int num, char* str, int base)
{
  int i = 0;
  

  // Handle 0 explicitely, otherwise empty string is printed for 0 
  if (num == 0)
  {
    str[i++] = '0';
    str[i] = '\0';
    return;
  }

  // Process individual digits
  while (num != 0)
  {
    int rem = num % base;
    str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
    num = num/base;
  }

  str[i] = '\0'; // Append string terminator

  // Reverse the string
  reverse(str);

 
}



int
main()
{

  //int pid;

  // for parent to write and child to read
  int ip[2] = {3,4};

  // for child to write and parent to read
  int op[2] = {5,6};



  int count = 1000;
  // Write and read variable
  int buf_size = 7;
  //char buffer[20] = "2000000";
  char readbuff[20];
  int readnum;

  printf(1," in ipc 2 \n");



  for(int i = 0; i < count; i++){

    if(read(ip[0], readbuff, buf_size) != buf_size ){
      printf(1,"error in read for child !!!!");
      exit();
    }
 

    

    readnum = atoi(readbuff);

    printf(1,"Number is(c) : %d \n", readnum);

    readnum++;

    itoa(readnum, readbuff, 10);

    if(write(op[1], readbuff, buf_size) != buf_size ){
      printf(1,"error in write for child !!!!");
      exit();
    }
  }
  
  exit();

}
