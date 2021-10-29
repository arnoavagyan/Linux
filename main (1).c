
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/stat.h>

#define BUFFER_SIZE 1024
#define TOK_BUFFER_SIZE 100
#define TOK_DELIM "\t\n"


struct d {
	char* line;
	char** args;
	int status;
};

char* read_line() {
	int i = 0;
	char* buffer = malloc(sizeof(char) * BUFFER_SIZE);
	int c; //for reading symbols
	if(!buffer) {
		printf("THE MEMORY IS NOT ALOCCATED\n");
		exit(EXIT_FAILURE);
	}
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
			free(buffer);
			buffer = malloc(sizeof(char)* 2 * BUFFER_SIZE);
			if(!buffer) {
				printf("THE MEMORY IS NOT ALOCCATED\n");
				exit(EXIT_FAILURE);
			}
		}
	}
	free(buffer);

}

char** split_line(char* line) {
	assert(line);
	int tok_size = TOK_BUFFER_SIZE, position = 0;
	char** tokens = malloc(sizeof(char*) * tok_size);
	char* token;
	if(!tokens) {
		printf("THE MEMORY IS NOT ALOCCATED\n");
		exit(EXIT_FAILURE);
	}
	token = strtok(line, TOK_DELIM);
	while(token != NULL) {
		tokens[position] = token;
		position++;
		if(position >= tok_size) {
			free(tokens);
			tokens = malloc(sizeof(char*) * 2 * tok_size);
			if(!tokens) {
				printf("THE MEMORY IS NOT ALOCCATED\n");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, TOK_DELIM);
	}
	tokens[position] = NULL;
	free(tokens);
	return tokens;
}

int execute(struct d* d) {
	int rc = fork();
	if(rc < 0) {
		fprintf(stderr, "FORK FAILED\n");
		exit(1);
	}
	else if(rc == 0) {
		close(STDOUT_FILENO);
		open("./Alex_&_Arno's_shell_output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
		execvp(d->args[0], d->args);
	}
	else {
		int rc_wait = wait(NULL);
	}
	return 0;
}

void inf_loop(struct d* d) {
	do {
		printf(">");
		d->line=read_line();
		d->args = split_line(d->line);
		d->status = execute(d);
	}while(d->status);
}

int main(int argc, char* argv[]) {
  struct d d;
	inf_loop(&d);
	return 0;
}
