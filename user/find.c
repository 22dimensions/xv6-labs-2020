#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

char *target_file;

void search(char* file) {
  int fd = 0;
  struct stat st;
  if ((fd = open(file, 0)) < 0) {
    printf("open: open file %s failed\n", file);
    exit(1);
  }
  if (fstat(fd, &st) < 0) {
    printf("stat: stat file %s failed\n", file);
    close(fd);
    exit(1);
  }

  struct dirent de;
  char buf[512], *p;

  if (st.type == T_DIR) {
    

    strcpy(buf, file);
    p = buf + strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)) {
      if (de.inum == 0) {
        continue;
      }
      if (strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0) {
        continue;
      }
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if (strcmp(de.name, target_file) == 0) {
        printf("%s\n", buf);
      }
      
      search(buf);
    }
  }
  return;
}

int main(int argc, char *argv[]) {
  if (argc <= 2) {
    printf("missing filepath or the filename to search!\n");
    exit(1);
  }
  target_file = argv[2];
  search(argv[1]);
  exit(0);
}