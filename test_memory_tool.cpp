#include <cstdio>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
		pid_t executive = fork();

		if( executive < 0 ){
				printf("fork failed\n");
				return 0;
		}
		else if( executive == 0 ){
				//child process
				//execl("./hello", "hello", NULL);
				char **new_argv = new char*[argc-1];
				new_argv=&(argv[2]);
				execv(argv[1], new_argv);//此处argv会包含工具的命令所以往后推一位
				delete [] new_argv;
		}
		else{
				struct rusage rused;
				int status = 0;
				if( wait4( executive, &status, 0, &rused  ) < 0 ){
						printf("wait4 failed\n");
						return 0;
				}

				if( WIFEXITED(status) ){
						int time_usage = (rused.ru_utime.tv_sec * 1000 + rused.ru_utime.tv_usec / 1000);
						time_usage += ( rused.ru_stime.tv_sec * 1000 + rused.ru_stime.tv_usec / 1000 );
						int memory_usage = rused.ru_minflt * ( getpagesize() / 1024 );
						printf("Time used: %d MS Memory used: %d KB \n", time_usage, memory_usage);
						printf("---------------------------------------------------------------------------------------------------------");

				}
		}
		return 0;
}

/*****************************************************************/
//
// 使用方法：
// 工具编译后的文件如tt 使用： tt ./hello 123 123 123
//
/*****************************************************************/