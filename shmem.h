#define NDESC ((PGSIZE - sizeof(struct spinlock))/sizeof(struct desc))

struct desc {
  void* reference;
  int pid;
  int parentid;
};

struct shmem {
  struct spinlock lock;
  struct desc desc[NDESC];
};
