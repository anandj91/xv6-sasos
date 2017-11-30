#include "types.h"
#include "defs.h"
#include "mmu.h"
#include "param.h"
#include "proc.h"
#include "spinlock.h"
#include "shmem.h"

struct desc {
  int pid;
  void* reference;
};

int NDESC = (PGSIZE - sizeof(struct spinlock))/sizeof(struct desc);
struct shmem {
  struct spinlock lock;
  struct desc desc[(PGSIZE - sizeof(struct spinlock))/sizeof(struct desc)];
} shmem;

void
shmem_init(void)
{
  initlock(&shmem.lock, "shmem");
}

// Look in shmem for unused desc.
// If found, try to allocate a page of memory for shared memory.
// Otherwise, return 0.
void*
shmem_alloc(void)
{
  void* ref = 0;
  int i = 0;
  void* nref = 0;
  acquire(&shmem.lock);
  for(i = 0; i < NDESC; i++){
    if(0 == shmem.desc[i].reference){
      break;
    }
  }
  if(NDESC <= i){
    goto bad;
  }
  ref = kalloc();
  if(0 == ref){
    goto bad;
  }
  if(remapsharedmem(proc->pgdir, ref, &nref) != 0){
    goto bad;
  }
  shmem.desc[i].pid = proc->pid;
  shmem.desc[i].reference = ref;
  release(&shmem.lock);
  return nref;
bad:
  if(ref != 0){
    kfree((char*) ref);
  }
  release(&shmem.lock);
  return 0;
}

// Look in shmem for desc with reference matching mem and then check if pid of
// that desc matches current proc pid.
// If succeed, free that mem and clear that desc.
// Otherwise, return.
// Must hold shmem.lock.
void
shmem_free(void* mem)
{
  int i = 0;
  uint a = PGROUNDDOWN((uint) mem);

  acquire(&shmem.lock);
  for(i = 0; i < NDESC; i++){
    if(mem == shmem.desc[i].reference){
      break;
    }
  }
  if(NDESC == i || shmem.desc[i].pid != proc->pid){
    goto bad;
  }
  if(deallocuvm(proc->pgdir, a+PGSIZE, a) != a){
    panic("shmem_free");
  }
  shmem.desc[i].pid = 0;
  shmem.desc[i].reference = 0;
bad:
  release(&shmem.lock);
}
