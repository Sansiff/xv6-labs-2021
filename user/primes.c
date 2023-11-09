#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void primes(int bp) {
  int prime, rb, x;
  rb = read(bp, &prime, 4);
  if(rb == 0) {
    exit(0);
  } 
  printf("prime %d\n", prime);
  int p[2];
  pipe(p);
  while(read(bp, &x, 4)) {
    if(x % prime != 0) {
      write(p[1], (void*)&x, 4);
    }
  }
  close(p[1]);
  if(fork() == 0) {
    primes(p[0]);
    close(p[0]);
  } else {
    wait(0);
  }
}

int main(int argc, char* argv[]) {
  int p[2];
  pipe(p);
  for(int i = 2; i <= 35; ++ i) {
    write(p[1], (void*)&i, sizeof(i));
  }
  close(p[1]);
  if(fork() == 0) {
    primes(p[0]);
    close(p[0]);
  } else {
    wait(0);
  }

  exit(0);
}