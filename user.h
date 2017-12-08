struct stat;
struct rtcdate;
//struct queue;


#define QUEUE_SIZE 100
struct queue{
  int read;
  int write;
  char buff[QUEUE_SIZE];
};


//typedef struct queue queue;

// system calls
int fork(void);
int exit(void) __attribute__((noreturn));
int wait(void);
int pipe(int*);
int write(int, void*, int);
int read(int, void*, int);
int close(int);
int kill(int);
int exec(char*, char**);
int open(char*, int);
int mknod(char*, short, short);
int unlink(char*);
int fstat(int fd, struct stat*);
int link(char*, char*);
int mkdir(char*);
int chdir(char*);
int dup(int);
int getpid(void);
char* sbrk(int);
int sleep(int);
int uptime(void);
int forkexec(char*, char**);
int shmem_alloc(void);
int shmem_free(int);
void* shmem_getref(int);
int shmem_mapdup(int);

// ulib.c
int stat(char*, struct stat*);
char* strcpy(char*, char*);
void *memmove(void*, void*, int);
char* strchr(const char*, char c);
int strcmp(const char*, const char*);
void printf(int, char*, ...);
char* gets(char*, int max);
uint strlen(char*);
void* memset(void*, int, uint);
void* malloc(uint);
void free(void*);
int atoi(const char*);
void reverse(char *);
void itoa(int , char*, int);

void write2q(struct queue*, char);
char readq(struct queue*);
void writen2q(struct queue*, char*, int);
void readnq(struct queue*, char*, int );
void displayQueue(struct queue*);
