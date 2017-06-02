#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static pid_t pid;
int m[17][17] ;

int path[17] ;
int used[17] ;
int length = 0 ;
int min = -1 ;

void _travel(int idx) {
	int i ;
	FILE* f;
	f = fopen("pid.txt", "w+");
//	if(f){
	if (idx == 17) {
		if (min == -1 || min > length) {
			min = length ;
			
				
			printf( "%d (", length) ;
			for (i = 0 ; i < 16 ; i++) 
				printf("%d ", path[i]) ;
			printf("%d)\n", path[16]) ;
			
		}
	}
	else {
		for (i = 0 ; i < 17 ; i++) {
			if (used[i] == 0) {
				path[idx] = i ;
				used[i] = 1 ;
				length += m[path[idx-1]][i] ;
				_travel(idx+1) ;
				length -= m[path[idx-1]][i] ;
				used[i] = 0 ;
			}
		}
//	}
}
//printf("error");
}

void travel(int start) {
	path[0] = start ;
	used[start] = 1 ;
	_travel(1) ;
	used[start] = 0 ;
}

void handler(int signum)
{
	int s;
	kill(pid, SIGINT);
	wait(&s);
	printf("Bye.\n");
	exit(0);	
}

int main() {

	int i, j, t,s,k ;
	signal(SIGINT, handler);
	FILE * fp = fopen("gr17.tsp", "r") ;

	for (i = 0 ; i < 17 ; i++) {
		for (j = 0 ; j < 17 ; j++) {
			fscanf(fp, "%d", &t) ;
			m[i][j] = t ;
		}
	}
	fclose(fp) ;

	for (j = 0  ; j < 17 ; j++){ 
		
	if((pid =fork()) == 0)
{
	printf("%d\n", getpid());
	travel(j);
	}

}
/*
 if((pid =fork()) == 0)
{
        printf("%d\n", pid);
        travel(i);
        }
*/
	printf("잘 되나?");
	waitpid(pid, &s, 0);
/*	for (k = 0 ; k < 17 ; k++) {
                pid = wait(&s) ;
                printf("[%d] terminated.\n", pid) ;
        }
//	waitpid(pid, &s, 0);
*/
}

