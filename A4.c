#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <readline/readline.h>
#include <readline/history.h>

/*Spaltet line mit Hilfe des delimiter-Zeichens und speichert die Teile in args*/
void split_args(char* args[], char line[], char delimiter[]){
  int index = 0;
  char* tmp_str = strtok(line, delimiter);

  while(tmp_str!=NULL){
    args[index] = tmp_str;
    tmp_str = strtok(NULL, delimiter);
    index++;
  }
  args[index] = NULL;
}

int main(int argc, char* argv[], char* envp[]){
  char* args[100];
  char* paths[100];
  char* set_path;
  char* path_to_prog;
  char* line;

  set_path = getenv("SET_PATH");  //SET_PATH muss vor Programmausführung gesetzt werden.
  split_args(paths, set_path, ":");

  if(set_path==NULL){ //Falls SET_PATH doch nicht gesetzt ist, nutze PWD
    paths[0] = getenv("PWD");
    paths[1] = NULL;
  }

  while(1){
    line = readline("MY_OWN_SHELL:$ ");

    /*Prüfe, ob die Eingabe bei line ein UNIX-Befehl ist*/
    int returnValue=system(line);
    if(returnValue==0){
      continue; //Falls ja wird zum nächsten Durchlauf gesprungen
    }

    split_args(args, line, " ");

    int index = 0;

    while(paths[index]!=NULL){
      /*Erzeuge neuen Prozess*/
      pid_t pid = fork();
      strcpy(path_to_prog, paths[index]);

      strcat(path_to_prog, "/");
      strcat(path_to_prog, args[0]); //Füge Programm-Name zum path hinzu

      int status;

      if(pid>=0){ //fork erfolgreich
        if(pid==0){ //Kindprozess
          return execv(path_to_prog, args);
        }
        else{ //Elternprozess
          wait(&status); //Warte darauf, dass Kindprozess sich beendet und speichere Exit-Code
        }
      }
      else{
        printf("Failed\n");
        return 1;
      }

      index++;
    }
    free(line);
  }
  return 0;
}
