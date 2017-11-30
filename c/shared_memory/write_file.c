#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/mman.h>
#include <sys/wait.h>

#include <stdatomic.h>

static volatile int stop = 0;
void intHandler(int i) {
  (void) i;
  stop = 1;
}

void error_and_die(const char *msg) {
  perror(msg);
  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
  signal(SIGINT, intHandler);

  int r;

  const char *memname = "./sample";
  const size_t region_size = sysconf(_SC_PAGE_SIZE);

  int fd = shm_open(memname, O_CREAT | O_RDWR, 0666);
  if (fd == -1)
    error_and_die("shm_open");

  //r = ftruncate(fd, region_size);
  //if (r != 0)
  //  error_and_die("ftruncate");

  _Atomic int *ptr = (_Atomic int *)mmap(0, region_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (ptr == MAP_FAILED)
    error_and_die("mmap");
  close(fd);

  int first_character = *(int *)ptr;
  for (size_t i = 0; i < 10000u; ++i)
  {
    //*(int *)ptr = *(int *)ptr + 1;
    atomic_fetch_add(ptr, 1);
    fprintf(stderr, "first character %d on address %p\n", *(int *) ptr, ptr);
    usleep(1000);
  }
  fprintf(stderr, "First character read: %d\n", first_character);

  r = munmap(ptr, region_size);
  if (r != 0)
    error_and_die("munmap");

  return 0;
}
