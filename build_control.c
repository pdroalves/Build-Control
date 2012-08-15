#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void print(FILE *f,int build){
 
	struct tm *local;
	time_t t;

	t = time(NULL);
	local = localtime(&t);
				
	fprintf(f,"Build: %d - %s",build,asctime(local));
	return;
}

int main(int argc,char *argv[]){

	int build;
	char *tmp;
 	char *buildfilename;
	char *buildhistoryfilename;

	if(argc > 1){

		FILE *build_control;
		FILE *build_history;

		buildfilename = (char*)malloc(100*sizeof(char));
		
		strcpy(buildfilename,argv[1]);
		strcat(buildfilename,".txt");
		build_control = fopen(buildfilename,"a+");
		
		buildhistoryfilename = (char*)malloc(100*sizeof(char));
		
		strcpy(buildhistoryfilename,argv[1]);
		strcat(buildhistoryfilename,"_history.txt");
		build_history = fopen(buildhistoryfilename,"a+");

		if(build_control != NULL){
			if(feof(build_control) != 0){
				print(build_control,0);
				print(build_history,0);
			}else{
				tmp = (char*)malloc(100*sizeof(char));
				fscanf(build_control,"Build: %d - %s",&build,tmp);
				
				fclose(build_control);
				build_control = fopen(buildfilename,"w+");
				print(build_control,build+1);
				print(build_history,build+1);
			}	
			fclose(build_control);
		}
	}
	return 0;
}
