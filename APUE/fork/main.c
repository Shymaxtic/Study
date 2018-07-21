#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int globvar = 6;
char buf[] = "a write to stdout\n";

int main() 
{
	int var;
	pid_t pid;
	
	var = 88;
	if(write(STDOUT_FILENO, buf, sizeof(buf)-1) != sizeof(buf) -1) {
		fprintf(stderr, "write error");
	}
	printf("before fork\n");		/* stdout is line buffer in terminal, full buffer in others */
	if((pid = fork()) < 0) {
		fprintf(stderr, "fork error");
	} else if(pid == 0) {
		globvar++;
		var++;
	} else {
		sleep(2);
	}
	printf("pid = %ld, globvar = %d, var = %d\n", (long)getpid(), globvar, var);
	exit(0);
}