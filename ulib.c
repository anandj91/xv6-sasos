#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"
#include "x86.h"


//typedef struct queue queue;


char*
strcpy(char *s, char *t)
{
  char *os;

  os = s;
  while((*s++ = *t++) != 0)
    ;
  return os;
}

int
strcmp(const char *p, const char *q)
{
  while(*p && *p == *q)
    p++, q++;
  return (uchar)*p - (uchar)*q;
}

uint
strlen(char *s)
{
  int n;

  for(n = 0; s[n]; n++)
    ;
  return n;
}

void*
memset(void *dst, int c, uint n)
{
  stosb(dst, c, n);
  return dst;
}

char*
strchr(const char *s, char c)
{
  for(; *s; s++)
    if(*s == c)
      return (char*)s;
  return 0;
}

char*
gets(char *buf, int max)
{
  int i, cc;
  char c;

  for(i=0; i+1 < max; ){
    cc = read(0, &c, 1);
    if(cc < 1)
      break;
    buf[i++] = c;
    if(c == '\n' || c == '\r')
      break;
  }
  buf[i] = '\0';
  return buf;
}

int
stat(char *n, struct stat *st)
{
  int fd;
  int r;

  fd = open(n, O_RDONLY);
  if(fd < 0)
    return -1;
  r = fstat(fd, st);
  close(fd);
  return r;
}

int
atoi(const char *s)
{
  int n;

  n = 0;
  while('0' <= *s && *s <= '9')
    n = n*10 + *s++ - '0';
  return n;
}


void reverse(char s[])
{
  int i, j;
  char c;
 
  for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}
void itoa(int num, char* str, int base)
{
  int i = 0;

  // Handle 0 explicitely, otherwise empty string is printed for 0 
  if (num == 0)
  {
    str[i++] = '0';
    str[i] = '\0';
    return;
  }

  // Process individual digits
  while (num != 0)
  {
    int rem = num % base;
    str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
    num = num/base;
  }

  str[i] = '\0'; // Append string terminator

  // Reverse the string
  reverse(str);


}

void*
memmove(void *vdst, void *vsrc, int n)
{
  char *dst, *src;

  dst = vdst;
  src = vsrc;
  while(n-- > 0)
    *dst++ = *src++;
  return vdst;
}

void write2q(struct queue *q, char data){

  // if buffer is full
  if ((q->read == 0 && q->write == QUEUE_SIZE-1) || (q->read == q->write + 1)){
    printf(1,"Buffer Overlfow \n");
    exit();
  }

  // If buffer is currently empty
  else if (q->read == -1){
    q->read = 0;
    q->write = 0;
    q->buff[q->write] = data;
  }

  // Wrap around the buffer
  else if( q->write == QUEUE_SIZE-1 && q->read!=0){
    q->write = 0;
    q->buff[q->write] = data;
  }

  else{
    q->write += 1;
    q->buff[q->write] = data;
  }

  


}

char readq(struct queue *q){

  // No element in the buffer
  if (q->read == -1)
  {
    printf(1,"Buffer Underflow \n");
    exit();
  }

  char data = q->buff[q->read];
  
  // should the read element be replaced by -1?

  if (q->read == q->write)
  {

    
    q->read = -1;
    q->write = -1;
  }

  // Wrap around
  else if (q->read == QUEUE_SIZE-1)
    q->read = 0;
  else
    q->read += 1;
  
  return data;
}


void writen2q(struct queue *q, char data[], int n){

 
  if (n < 0){
    printf(1,"Unexpected negative length \n");
    exit();
  }

  // Write n charecters into the buffer
  for(int i = 0; i < n; i++){
    write2q(q,data[i]);
  }

  return;

}


void readnq(struct queue *q, char data[], int n){

  for(int i = 0; i < n; i++)
    data[i] = readq(q);

  return;

}


void displayQueue(struct queue *q)
{
  if (q->read == -1)
  {
    printf(1,"Empty Buffer \n");
    exit();
  }

  printf(1,"Displaying Elements : \n ");

  if (q->write >= q->read)
  {
    for (int i = q->read; i <= q->write; i++)
      printf(1,"%c ",q->buff[i]);
  }
  else
  {
    for (int i = q->read; i < QUEUE_SIZE; i++)
      printf(1,"%c ", q->buff[i]);

    for (int i = 0; i <= q->write; i++)
      printf(1,"%c ", q->buff[i]);
  }

  return;
}


