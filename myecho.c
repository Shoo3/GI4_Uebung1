#include <stdio.h>

int main(int argc, char* argv[], char* envp[]){

  if(argc<=1){
    printf("Nothing to print! Input arguments needed!\n");
  }

  else{
    int index;
    for(index=1; index<argc; index++){
      printf("%s ", argv[index]);
    }
    printf("\n");
  }

  return 0;
}
