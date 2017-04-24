#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char* argv[], char* envp[]){

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

  return 0;
}
