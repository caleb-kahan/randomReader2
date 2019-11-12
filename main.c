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
  printf("Generating Random Numbers: \n");
  for(i=0;i<10;i++){
    array[i] = randomEntropy();
    if(array[i]==-1){
      return 0;
    }
    printf("Random Number %d: %d\n",i+1,array[i]);
  }
  int fd = open("output.txt", O_WRONLY | O_CREAT, 0755);
  if(fd == -1){
    errorPrinter("output.txt","open");
    return 0;
  }
  printf("\n\nWriting numbers to file...\n\n");
  if(write(fd,array,10*sizeof(int)) == -1){
    errorPrinter("output.txt","write");
    close(fd);
    return 0;
  }
  close(fd);
  fd = open("output.txt", O_RDONLY);
  if(fd == -1){
    errorPrinter("output.txt","open");
    return 0;
  }
  int array2[10];
  printf("Reading numbers from file...\n\n");
  if(read(fd,array2,10*sizeof(int)) == -1){
    errorPrinter("output.txt","read");
    close(fd);
    return 0;
  }
  printf("Verification that written values were the same:\n");
  for(i=0;i<10;i++){
    printf("Copied Value %d: %d\n",i+1,array2[i]);
  }
  close(fd);
  return 0;
}
int randomEntropy(){
  int randomNumber[1];
  int fd = open("/dev/urandom", O_RDONLY);
  if(fd == -1){
    errorPrinter("urandom","open");
    return -1;
  }
  if(read(fd, randomNumber, sizeof(int)) == -1){
    errorPrinter("urandom","read");
    close(fd);
    return -1;
  }
  close(fd);
  return randomNumber[0];
}
void errorPrinter(char *fileName, char *action){
  printf("PROBLEM: When trying to %s the file \"%s\", this error was returned: %s\n",action,fileName,strerror(errno));
}
