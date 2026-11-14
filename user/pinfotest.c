#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/pinfo.h"
#include "user/user.h"

int
main(void)
{
  struct pinfo info[64];
  int pid = getpid();
  volatile unsigned long work = 0;

  for (unsigned long i = 0; i < 100000000UL; i++)
    work += i;

  int n = getpinfo(info, 64);

  if (n < 0) {
    printf("FAIL: getpinfo returned -1\n");
    exit(1);
  }

  for (int i = 0; i < n; i++) {
    if (info[i].pid == pid) {
      printf("runticks=%d level=%d nsched=%d\n",
             info[i].runticks, info[i].level, info[i].nsched);

      if (info[i].runticks > 0)
        printf("CPU tick test PASSED\n");
      else
        printf("CPU tick test FAILED\n");

      exit(0);
    }
  }

  printf("FAIL: process not found\n");
  exit(1);
}
