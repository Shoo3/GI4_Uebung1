#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <readline/readline.h>
#include <readline/history.h>

void split_args(char* args[], char line[]){
  char delimiter[] = " ";
  char* tmp_str;
  int index=0;
  tmp_str = strtok(line, delimiter);

  while(tmp_str!=NULL){
    args[index] = tmp_str;
    tmp_str = strtok(NULL, delimiter);
    index++;
  }
  args[index] = NULL;
}


int main(int argc, char* argv[], char* envp[]){
  /*

  */
  char string[] = "Kurt Kanns 555678 DE";
  char delimiter[] = " ";
  char *ptr;
  char* args[100];
  int index=0;




  char* line;
  while(1){
    line = readline("Enter text: ");
    split_args(args, line);
    /*Erzeuge neuen Prozess*/
    pid_t pid = fork();
    int status;

    if(pid>=0){ //fork erfolgreich
      if(pid==0){ //Kindprozess
        printf("Kindprozess:\n");
        printf("PID =  %d, Eltern PID = %d\n", getpid(), getppid());
        return execv(argv[1], argv+1);
      }
      else{ //Elternprozess
        printf("Elternprozess:\n");
        printf("PID =  %d, Kind PID = %d\n", getpid(), pid);
        wait(&status); //Warte darauf, dass Kindprozess sich beendet und speichere Exit-Code
        printf("Exit code: %d\n", WEXITSTATUS(status));
      }
    }
    else{
      printf("Prozesserzeugung fehlgeschlagen\n");
      return 1;
    }
    free(line);
  }
  return 0;
}
