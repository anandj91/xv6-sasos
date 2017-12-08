#define NDESC (PGSIZE - sizeof(struct spinlock))/sizeof(struct desc)

struct desc {
  int pid;
  void* reference;
};

struct shmem {
  struct spinlock lock;
  struct desc desc[NDESC];
};
