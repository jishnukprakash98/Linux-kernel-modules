#include <stdlib.h>
#include <time.h>
#include <stdio.h>

char line[50] = "shit";
char name[20];
 
int main(){
	FILE *file;
	file = fopen("status","r");
	//fgets(line,50,file);
	//fscanf(file,"%s",line);
	//printf("\n%s",line);
	
	while(fgets(line,100,file) != NULL){
	int i = 0;
	int j = 0;
		for( i = 0; line[i] != '\t'; i++);
		while(line[i] != '\n')
			name[j++] = line[++i];
				
		
		printf("\n%s",name);
	}
return 0;
}
