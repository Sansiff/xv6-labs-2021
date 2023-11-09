#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  char* targv[32];
  for(int i = 1; i < argc; i ++) {
    targv[i - 1] = argv[i];
  }

  int tp = argc - 1;
  int p = tp;
  char buf[32];
  while(read(0, (void*)&buf, 32) > 0) {
    char s[32];
    int m = 0;
    for(int i = 0; i < 32; i ++) {
      if(buf[i] == '\n') {
        targv[p ++] = s;
        targv[p] = 0;
        if(fork() == 0) {
          exec(argv[1], targv);
        }
        wait(0);
        p = tp;
      } else if(buf[i] == ' '){
        s[m] = 0;
        targv[p ++] = s;
        m = 0;
      } else {
        s[m ++] = buf[i];    
      }
    }
  }

  exit(0);
}
