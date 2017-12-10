#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define N 10000

void multiply(volatile int mat1[][N],volatile int mat2[][N],volatile int res[][N])
{
  int i, j, k;
  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
    {
      res[i][j] = 0;
      for (k = 0; k < N; k++)
        res[i][j] += mat1[i][k]*mat2[k][j];
    }
  }
}
 
int main()
{
  volatile int mat1[N][N];
 
  volatile int mat2[N][N];
 
  volatile int res[N][N]; // To store result

  //int count = 5;
  int max = 10000000;
  for(int count = 0; count < max; count++){
    for(int i = 0; i < N; i++){
      for(int j = 0; j < N; j++){
        mat1[i][j] = count;
        mat2[i][j] = count+5;
      }
    }

    multiply(mat1, mat2, res);

    }


  exit();
}
