#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[], char* envp[]){

  char* optionalParam = "-v";

  /*Keine Umgebungsvariablen eingegeben*/
  if(argc<=1){
    printf("Eingabe der Umgebungsvariable fehlt\n");
  }
  /*Option -v wurde nicht verwendet*/
  else if(argc == 2){
    if(getenv(argv[1])){
      return 0;
    }
  }
  /*Option -v wurde vielleicht verwendet*/
  else{
    if(getenv(argv[1])){
      if(!strcmp(argv[2],optionalParam))
      {
        printf("%s\n", getenv(argv[1]));
        return 0;
      }
      else{
        printf("Unbekannter Parameter\n");
      }
    }
  }
  return 1;
}
