#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int
main()
{
  int ip[2] = {3,4};
  int op[2] = {5,6};
  int buf_size = sizeof(void*)/sizeof(char);
  char buffer[sizeof(void*)/sizeof(char)] = {0};
  int mask = 0xff;
  int* mem = 0;
  int m = 0;

  printf(1,"in shmem 2 \n");

  if(read(ip[0], buffer, buf_size) != buf_size){
    printf(1, "Error in read for child!\n");
    exit();
  }

  for(int i = buf_size-1; i >= 0; i--){
    m = ((m << 8) | (buffer[i] & mask));
    printf(1, "child buffer[%d] = %x m = %x\n", i, buffer[i], m);
  }
  mem = (int*) m;

  printf(1, "Got 0x%x from the parent\n", m);

  *mem = 2;

  // inform the parent of the change
  if(write(op[1], buffer, 1) != 1){
    printf(1, " Error in write\n");
    exit();
  }

  exit();
}
