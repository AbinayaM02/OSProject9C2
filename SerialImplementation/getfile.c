/*********************************************
 *  getfile.c
 *  Sample KNN implementation
 *  read arff file
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include "knn.h"


int get_line (char *s, FILE *fp)
{
	char c;
	int eof_flag = 1;
	int skip_flag = 0;
	int count = 0;

	while((c=fgetc(fp))!=EOF)
  	{
    		if (c == '\n'){
			eof_flag = 0;
			*s = '\0';
			s++;
    		break;
		}else if(c == '?'){
			//skip missing line
			skip_flag = 1;
		}
		*s = c;
	 	s++;
		count++;
  	}
	s = s - count;
	if(eof_flag){
		return 1;
	}else if(skip_flag){
		return 2;
	}
	else{
		return 0;
	}
}


void get_attributes(char* filename,int *Atttr_Num,char *Atttr_Seq){

    FILE  *fp;
	
	char string[2000];
	char*ptr;
	
    fp=fopen(filename,"r");

	if(fp==NULL)
	{
		printf("\nError in opening ");
	}
	
	while(1){
		//printf("in get attr while\n");
		ptr= string;
		get_line(ptr,fp);
		if(string[0] == '@' && string[1] == 'a'){
			printf("%d : %s\n", *Atttr_Num,ptr);
			do{ptr++;} while(*ptr != ' ');
			do{ptr++;} while(*ptr != ' ');
			ptr++;
			if(*ptr == 'r'){
				Atttr_Seq[*Atttr_Num] = 'r';
			}
			(*Atttr_Num)++;
		}else if(string[0] == '@' && string[1] == 'd'){
			Atttr_Seq[*Atttr_Num] = '\0';
			break;
		}
	}

	fclose(fp);
}

char* getword(char *ptr){
	int i;
	char * to;
	if(*ptr == ','){
		ptr++;
	}
	to = (char*)malloc(20*sizeof(char));
	for(i = 0; ptr[i]!=',' && ptr[i]!='\n';i++){
		to[i] = ptr[i];
	}
	to[i] = '\0';

	return to; 
}

struct Node* readfile(char *filename,int *Sample_Num,int *Atttr_Num,char *Atttr_Seq){

    FILE  *fp;
    int finished = 0;
    int i = 0, j,k;//m,n;
    char string[2000];
    char*ptr;
    struct Node *Sample;
    Sample=(struct Node *)malloc(sizeof(struct Node)*MAX_SAMPLE);
    
    get_attributes(filename,Atttr_Num,Atttr_Seq);

    fp=fopen(filename,"r");

	if(fp==NULL)
	{
		printf("\nError in opening ");
		return NULL;
	}
	//n = 0;
	//m = 0;
	k = 0;
	while(finished != 1){
		ptr= string;
		finished = get_line(ptr,fp);
		//printf("line read:%s\n",ptr);
		if(finished == 2){	//skip this line
			continue;
		}
		if(string[0] != '%' && string[0] != '@' && string[0] != '\0'){
			k = 0;
			for(j = 0; j < *Atttr_Num; j++){
				if(j == 0){
					if(Atttr_Seq[k] == 'r'){
						sscanf(ptr,"%f",&Sample[i].NumericAttributes[j]);
					}
					k++;
				}else{
					if(Atttr_Seq[k] == 'r'){
						sscanf(ptr,",%f",&Sample[i].NumericAttributes[j]);
					}
					k++;
				}
				do{ptr++;} while(*ptr != ',');
			}
			//printf("row%d\n",i);
			i++;
			(*Sample_Num)++;
		}
	}
		
	fclose(fp);
	return Sample;
}

