#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>


/*Comment added in develop branch*/

int main(int argc, char* argv[], char* envp[]){
  char* line;
  while(1){
    line = readline("Enter text: ");
    printf("%s\n", line);
  }
  return 0;
}
