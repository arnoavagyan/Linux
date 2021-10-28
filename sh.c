#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>

#define BUFFER_SIZE 1024
#define TOK_BUFFER_SIZE 100
#define TOK_DELIM "\t\n"

char* read_line();
char** split_line(char* line);
int execute(char** args);
char* line;
char** args;
int status;

void inf_loop() {
	
	do {
		printf(">");
		line = read_line();
		args = split_line(line);
		status = execute(args);
		free(line);
		free(args);
	}while(status);
}

char* read_line() {
  int i = 0;
	char* buffer = malloc(sizeof(char) * BUFFER_SIZE);
	int c;
	if(!buffer)
		printf("THE MEMORY IS NOT ALOCCATED\n");
		exit(EXIT_FAILURE);
	while(1) {
		c = getchar();
		if(c == EOF || c == '\n') {
			buffer[i] = '\0';
			return buffer;
		}
		else {
			buffer[i] = c;
		}
		++i;
		if(i >= BUFFER_SIZE){
			int BUFFER_SIZE_2 = 2*BUFFER_SIZE;
			buffer = malloc(sizeof(char) * BUFFER_SIZE_2);
			if(!buffer) {
				printf("THE MEMORY IS NOT ALOCCATED\n");
				exit(EXIT_FAILURE);
			}
		}
	}
}



char** split_line(char* line) {
	int buffer = TOK_BUFFER_SIZE, position = 0;
	char** tokens = malloc(buffer * sizeof(char*));
	char* token;
	if(!tokens) {
		printf("THE MEMORY IS NOT ALOCCATED\n");
		exit(EXIT_FAILURE);
	}
	token=strtok(line, TOK_DELIM);
	while(token != NULL) {
		tokens[position] = token;
		position++;
		if(position >= buffer) {
			buffer += TOK_BUFFER_SIZE;
			tokens = malloc(buffer * sizeof(char*));
			if(!tokens) {
				printf("THE MEMORY IS NOT ALOCCATED\n");
			}
			exit(EXIT_FAILURE);
		}
		token = strtok(NULL, TOK_DELIM);
	}
	tokens[position] = NULL;
	return tokens;
}

int execute(char **args) {
    int rc = fork();
    if (rc < 0) {
      fprintf(stderr, "fork failed\n");
      exit(1);
    } else if (rc == 0) {
      close(STDOUT_FILENO);
      open("./p4.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);

      char *myargs[3];
      myargs[0] = strdup("line"); 
      myargs[1] = strdup("args"); 
      myargs[2] = NULL; 
      execvp(myargs[0], myargs); 
    } else {
      int rc_wait = wait(NULL);
      }
 return 0;
 }

int main(int argc, char* argv[]) {
	inf_loop();
}
