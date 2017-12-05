#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
  int pid;
  int* addr;

  printf(1, "Testing shared memory\n");

  addr = (int*) shmem_alloc();
  if(addr == 0){
    printf(1, "Error allocating shared memory\n");
    exit();
  }

  *addr = 1;
  printf(1, "Wrote %d\n", *addr);

  pid = fork();
  if(pid){
    printf(1, "In parent\n");
    wait();
    printf(1, "Got %d back from child\n", *addr);
    if(shmem_free(addr) < 0){
      printf(1, "Error deallocating shared memory\n");
    }
  } else {
    printf(1, "In child\n");
    printf(1, "Got %d from parent\n", *addr);
    *addr = 2;
  }

  exit();
}
