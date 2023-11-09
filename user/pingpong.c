#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char* argv[]) {
  int p2c[2], c2p[2]; // 0 for read, 1 for write
  char buf[4];
  pipe(p2c), pipe(c2p);
  int pid = fork();
  if(pid > 0) {
    // parent progress
    write(p2c[1], "ping", 4);
    read(c2p[0], buf, 4);
    printf("%d: received %s\n", getpid(), buf);
  } else {
    // child progress
    read(p2c[0], buf, 4);
    printf("%d: received %s\n", getpid(), buf);
    write(c2p[1], "pong", 4);
  }
  exit(0);
}