#include <stdio.h>

int main(int argc, char* argv[], char* envp[]){

  int index = 0;
  while(envp[index]!=NULL){
    printf("%s\n", envp[index]);
    index++;
  }

  printf("Anzahl der gesetzten Umgebungsvariablen: %d\n", index);

  return 0;
}
