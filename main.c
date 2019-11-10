#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
  char * buffer = malloc(100*sizeof(char));
  int fd = open("C:\\Program Files\\Git\\dev\\urandom", O_RDONLY);
  read(fd, buffer, 100*sizeof(char));
  if(fd==-1)
    return 0;
  int i;
  for(i=0;i<100;i++){
    printf("%c",buffer[i]);
  }
  int connection = 0;
  int sss;
  free(buffer);
  close(fd);
}
