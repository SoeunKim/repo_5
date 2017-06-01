#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int main()
{
	pid_t pid;
	int s,j,k; 
	int i=0, count=0; // i : 입력받은 filename을 저장할때 index값
	char f[15]; 
	int len;
	char a[20][15]; // 입력받은 filename 저장소


	while( !feof(stdin) )
	{
		if( fgets(f, sizeof(f), stdin)==NULL) break;
                len = strlen(f)-4;
		strcpy(a[i++], f);
		a[i-1][len] = '\0';
		printf("%s.gz\n", a[i-1]);
		count++;
	}
	
	printf("\nthe number of input file : %d 개 \n", count);
        printf("\nLet's unzip every 'gzip' file's.\n") ;
       
	for(j=0; j<count; j++){
		if (fork() == 0)
			execl("/bin/gzip", "gzip" , "-d" ,a[j] , NULL); // gzip 파일들 압축 풀기
		printf("success ..%d\n", j+1);
		sleep(2); // 2초간 sleep하고 fork
	}

        for (k = 0 ; k < count ; k++) {
                pid = wait(&s) ;
                printf("[%d] terminated.\n", pid) ;
        } // 각 child 들이 끝나기를 기다렸다가 순서대로 pid 출력


	sleep(3); //parent끝나기 전 5초간 sleep!
        printf("Done.\n") ;
}
