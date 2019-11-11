#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "header.h"

int main(){
  int array[10];
  int i;
  for(i=0;i<10;i++){
    array[i] = randomEntropy();;
    printf("Random Number %d: %d\n",i+1,array[i]);
  }
  int fd = open("output.txt", O_WRONLY | O_CREAT, 0755);
  if(fd == -1){
    errorPrinter("output.txt");
    return 0;
  }
  write(fd,array,10*sizeof(int));
  close(fd);
  fd = open("output.txt", O_RDONLY);
  if(fd == -1){
    errorPrinter("output.txt");
    return 0;
  }
  int array2[10];
  read(fd,array2,10*sizeof(int));
  for(i=0;i<10;i++){
    printf("Copied Value %d: %d\n",i+1,array2[i]);
  }
  return 0;
}
int randomEntropy(){
  int randomNumber[1];
  int fd = open("/dev/urandom", O_RDONLY);
  if(fd == -1){
    errorPrinter("urandom");
    return 0;
  }
  read(fd, randomNumber, sizeof(int));
  if(fd==-1){
    printf("%s\n",strerror(errno));
    return 0;
  }
  int i;
  close(fd);
  return randomNumber[0];
}
void errorPrinter(char *fileName){
  printf("PROBLEM: When trying to open the file \"%s\", this error was returned: %s\n",fileName,strerror(errno));
}
