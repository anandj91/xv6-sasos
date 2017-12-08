#include "types.h"
#include "defs.h"
#include "mmu.h"
#include "param.h"
#include "proc.h"
#include "spinlock.h"
#include "shmem.h"

struct shmem shmem;

void
shmem_init(void)
{
  uint a;
  uint i;
  initlock(&shmem.lock, "shmem");
  for(a = 0x70000000, i = 0; i < NDESC; i++, a += PGSIZE){
    shmem.desc[i].pid = -1;
    shmem.desc[i].parentid = -1;
    shmem.desc[i].reference = (void*)a;
  }
}

int
shmem_mapdup(int i){
  void* uva;
  void* nuva;
  int k;

  acquire(&shmem.lock);
  if(i >= NDESC || shmem.desc[i].parentid != i || shmem.desc[i].pid != proc->pid){
    goto bad;
  }
  for(k = 0; k < NDESC; k++){
    if(shmem.desc[k].pid == -1){
      break;
    }
  }
  if(k >= NDESC){
    goto bad;
  }
  uva = shmem.desc[i].reference;
  nuva = shmem.desc[k].reference;
  if(mapdup(proc->pgdir, uva, nuva) < 0){
    goto bad;
  }
  shmem.desc[k].parentid = i;
  shmem.desc[k].pid = proc->pid;
  release(&shmem.lock);
  return k;
bad:
  release(&shmem.lock);
  return -1;
}

void*
shmem_getref(int i){
  void* ref;
  acquire(&shmem.lock);
  if(i >= NDESC || proc->pid != shmem.desc[i].pid){
    release(&shmem.lock);
    return 0;
  }
  ref = shmem.desc[i].reference;
  release(&shmem.lock);
  return ref;
}

// Look in shmem for unused desc.
// If found, try to allocate a page of memory for shared memory.
// Otherwise, return 0.
int
shmem_alloc(void)
{
  void* ref = 0;
  void* nref = 0;
  int i = 0;

  acquire(&shmem.lock);
  for(i = 0; i < NDESC; i++){
    if(shmem.desc[i].pid == -1){
      break;
    }
  }
  if(i >= NDESC){
    goto bad;
  }
  ref = kalloc();
  if(ref == 0){
    goto bad;
  }
  memset(ref, 0, PGSIZE);
  nref = shmem.desc[i].reference;
  if(remapsharedmem(proc->pgdir, ref, nref) != 0){
    goto bad;
  }
  shmem.desc[i].parentid = i;
  shmem.desc[i].pid = proc->pid;
  release(&shmem.lock);
  return i;
bad:
  if(ref != 0){
    kfree((char*) ref);
  }
  release(&shmem.lock);
  return -1;
}

static
void shmem_freedesc(int i){
  uint a = (uint) shmem.desc[i].reference;
  if(shmem.desc[i].parentid == i){
    if(deallocuvm(proc->pgdir, a+PGSIZE, a) != (uint)a){
      panic("shmem_freedesc");
    }
  } else {
    if(unmappage(proc->pgdir, (void*)a) != 0){
      panic("shmem_freedesc");
    }
  }
  shmem.desc[i].parentid = -1;
  shmem.desc[i].pid = -1;
}

// Look in shmem for desc with reference matching mem and then check if pid of
// that desc matches current proc pid.
// If succeed, free that mem and clear that desc.
// Otherwise, return.
int
shmem_free(int i)
{
  int k;
  acquire(&shmem.lock);
  if(i >= NDESC || shmem.desc[i].pid != proc->pid){
    release(&shmem.lock);
    return -1;
  }
  for(k = 0; k < NDESC; k++){
    if(shmem.desc[k].parentid == i){
      shmem_freedesc(k);
    }
  }
  release(&shmem.lock);
  return 0;
}

void
shmem_freeall(int pid)
{
  uint i;
  acquire(&shmem.lock);
  for(i = 0; i < NDESC; i++){
    if(shmem.desc[i].pid == pid){
      shmem_freedesc(i);
    }
  }
  release(&shmem.lock);
}
