#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int
main()
{
  int ip[2] = {3,4};
  int op[2] = {5,6};
  int* mem = 0;

  printf(1,"in shmem 2 \n");

  if(read(ip[0], (char*)&mem, sizeof(int*)) != sizeof(int*)){
    printf(1, "Error in read for child!\n");
    exit();
  }

  printf(1, "Got 0x%x from parent\n", mem);

  *mem = 2;

  // inform the parent of the change
  if(write(op[1], (char*)&mem, 1) != 1){
    printf(1, " Error in write\n");
    exit();
  }

  printf(1, "Child got here\n");

  exit();
}
