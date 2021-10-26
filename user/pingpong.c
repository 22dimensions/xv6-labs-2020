#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  int send_pipe[2];
  int receive_pipe[2];
  pipe(send_pipe);
  pipe(receive_pipe);

  char buffer[1] = {'?'};

  if (fork() == 0) {
    close(send_pipe[1]);
    close(receive_pipe[0]);
    read(send_pipe[0], buffer, 1);
    printf("%d: received ping\n", getpid());
    write(receive_pipe[1], buffer, 1);
    close(send_pipe[0]);
    close(receive_pipe[1]);
    exit(0);
  } else {
    close(send_pipe[0]);
    close(receive_pipe[1]);
    write(send_pipe[1], buffer, 1);
    read(receive_pipe[0], buffer, 1);
    printf("%d: received pong\n", getpid());
    close(send_pipe[1]);
    close(receive_pipe[0]);
    exit(0);
  }
  exit(0);
}