#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int
main()
{
  int ip[2] = {3,4};
  int* mem = 0;

  printf(1,"in shmem 2 \n");

  if(read(ip[0], (char*)&mem, sizeof(int*)) != sizeof(int*)){
    printf(1, "Error in read for child!\n");
    exit();
  }

  printf(1, "Got 0x%x from parent\n", mem);

  *mem = 2;

  exit();
}
