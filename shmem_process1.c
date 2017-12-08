#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int
main()
{
  int ip[2] = {3,4};
  int op[2] = {5,6};
  char *argv[] = {"shmem_process2",0};
  int mask = 0xff;
  int buf_size = sizeof(void*)/sizeof(char);
  char buffer[sizeof(void*)/sizeof(char)] = {0};
  int* mem = 0;
  int m;

  printf(1,"in shmem 1 \n");

  // Creating pipes
  if(pipe(ip) == -1 || pipe(op) == -1){
    printf(1, " Error in creating pipes \n");
    exit();
  }

  forkexec("shmem_process2", argv);

  mem = (int*) shmem_alloc();
  if (0 == mem){
    printf(1, "Error in allocating shared memory\n");
    exit();
  }
  printf(1, "Allocated memory at 0x%x\n", mem);
  m = (int) mem;
  for(int i = 0; i < buf_size; i++){
    buffer[i] = (m & mask);
    m = m >> 8;
    printf(1, "parent buffer[%d] = %x\n", i, buffer[i]);
  }

  *mem = 1;

  // inform the child of the allocated memory
  if(write(ip[1], buffer, buf_size) != buf_size){
    printf(1, " Error in write\n");
    exit();
  }

  // Read from the child pipe
  if(read(op[0], buffer, 1) != 1){
    printf(1,"\n Error in read by parent");
    exit();
  }

  printf(1, "Got back %d\n", *mem);

  shmem_free(mem);

  wait();
  exit();
}
