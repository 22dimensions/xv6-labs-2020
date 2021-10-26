#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  if (argc <= 1) {
    printf("sleep: missing operand\n");
    exit(1);
  }
  int time;
  time = atoi(argv[1]);
  if (time <= 0) {
    printf("invalid option %s\n", argv[1]);
    exit(1);
  }
  sleep(time);
  exit(0);
}