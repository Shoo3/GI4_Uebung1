#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <readline/readline.h>
#include <readline/history.h>

void split_args(char* args[], char line[], char delimiter[]){
  int index = 0;
  char* tmp_str = strtok(line, delimiter);

  while(tmp_str!=NULL){
    args[index] = tmp_str;
    tmp_str = strtok(NULL, delimiter);
    index++;
  }
  args[index] = NULL;
  /*
  index=0;

  while(args[index]!=NULL){
    printf("%s\n", args[index]);
    index++;
  }
  */
}

int main(int argc, char* argv[], char* envp[]){
  char* args[100];
  char* paths[100];
  char* env_path;
  char* my_path;
  char* line;

  env_path = getenv("SET_PATH");  //SET_PATH muss vor Programmausführung gesetzt werden.
  if(env_path==NULL){
    paths[0] = getenv("PWD");
    paths[1] = NULL;
  }

  split_args(paths, env_path, ":");

  while(1){
    line = readline("My_shell:$ ");
    split_args(args, line, " ");

    int index = 0;

    while(paths[index]!=NULL){
      /*Erzeuge neuen Prozess*/
      pid_t pid = fork();
      strcpy(my_path, paths[index]);
      strcat(my_path, "/");
      strcat(my_path, args[0]);
      int status;

      if(pid>=0){ //fork erfolgreich
        if(pid==0){ //Kindprozess
          return execv(my_path, args+1);
        }
        else{ //Elternprozess
          wait(&status); //Warte darauf, dass Kindprozess sich beendet und speichere Exit-Code
          printf("Exit code: %d\n", WEXITSTATUS(status));
        }
      }
      else{
        printf("Failed\n");
        return 1;
      }
    }

    free(line);
  }
  return 0;
}
