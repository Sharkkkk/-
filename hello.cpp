#include <stdio.h>
#include<unistd.h>
int main(int argc, char *argv[]){
		sleep(1);
		printf("argc=%d\n", argc);
		for (int i = 0; i <argc; i ++) {
			printf(argv[i]);
		}
		printf("\n");	
		//printf("我运行了\n");
		return 0;
}
