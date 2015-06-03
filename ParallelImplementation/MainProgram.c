/* C Code */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "dataExtraction.h"
#define MEAN_DIFF_RANGE 50
#define STRINGLENGTH 1000
#define DATAFILE "MultiCancer1.csv"
#define THRESHOLDFILE "MultiCancer_threshold1.csv"
#define FINALFEATURESFILE "final_features.txt"
#define FINALFEATURESNAMEFILE "final_features_name.txt"
//#define DATAFILE "normals_leu_small.csv"
//#define THRESHOLDFILE "normals_leu_thr_small.csv"
//#define DATAFILE "Breast.csv"
//#define THRESHOLDFILE "Breast2.csv"

char features_1[ROWS][STRINGLENGTH],features[ROWS][STRINGLENGTH];
//char arr1[ROWS][COLS][STRINGLENGTH], arr2[ROWS][COLS][STRINGLENGTH];
char cols1[ROWS][STRINGLENGTH],cols2[ROWS][STRINGLENGTH];
int feature_length=0,rowcount1=0,rowcount2=0;

char* getType(char data[])
{
	int i;
	for(i=0;i<strlen(data);i++)
	{
		if(!(data[i]>=48 && data[i]<=57))
			break;
	}
	if(i==strlen(data))
		return "Integer";
	if(i>0 && data[i]=='.')
	{
		for(i=i+1;i<strlen(data);i++)
			if(!(data[i]>=48 && data[i]<=57))
				break;
	}
	if(i==strlen(data))
		return "Double";
	return "String";
}

int checkColumns()
{
  char data1[ROWS][STRINGLENGTH],data2[ROWS][STRINGLENGTH];
  FILE *fp,*fp1;
  char ch[STRINGLENGTH],str[STRINGLENGTH],*result;
  int j=0,i=0;
  char delims[] = ",";
  fp = fopen(DATAFILE,"r");
  if(fp==NULL)
  {
    printf("Cannot open the file\n");
    return 0;
  }

  /*  Fetch the feature column names for threshold file */
  while(fgets(ch,sizeof(ch),fp)&& (j==0||j==1))//fscanf(fp,"%s",ch)!='\0' && (j==0||j==1))
  {
   i=0;
   strcpy(str,ch);
   result = NULL;
   result = strtok(str, delims);
    while(result != NULL ) {
      if(j==0)
      	strcpy(cols1[i],result);
      if(j==1)
	strcpy(data1[i],result);
      result = strtok( NULL, delims );
     i++;
    }
    j++;
  }
  fclose(fp);

 fp1 = fopen(THRESHOLDFILE,"r");
  if(fp1==NULL)
  {
    printf("Cannot open the file\n");
    return 0;
  }

  /*  Fetch the feature column names for information file */
  int p=0;j=0;int q=i;
  while(fgets(ch,sizeof(ch),fp1) && (j==0||j==1))
  {
   p=0;
   strcpy(str,ch);
   result = NULL;
   result = strtok(str, delims);
    while(result != NULL ) {
      	if(j==0)
		{
      		  strcpy(cols2[p],result);
		}
	if(j==1)
		strcpy(data2[p],result);
      result = strtok( NULL, delims );
     p++;
    }
    j++;
  }
  fclose(fp1);

/* Compare the feature column names */
  int k=0;
  for(i=0;i<q;i++)
  {
    for(j=0;j<p;j++)
    {
       if(strcmp(cols1[i],cols2[j])==0 && strcmp(getType(data1[i]),getType(data2[j]))==0)
       {
	    printf("k =%d",k);
            strcpy(features_1[k++],cols1[i]);	
            break;
       }

    }
 }
feature_length=k;
 return 1;
}

int getArrays(char ***arr1,char ***arr2)
{
  FILE *fp;
  fp = fopen(DATAFILE,"r");
  if(fp==NULL)
  {
    printf("Cannot open the file\n");
    return 0;
  }


 char ch[STRINGLENGTH], str[STRINGLENGTH];
 char delims[] = ",";
 int i=0,j=0,colcount=0;
 char *result = NULL;

 fseek(fp,0,SEEK_SET);

 while(fgets(ch,sizeof(ch),fp))
 {
   
   colcount=0;
   i=0;

   strcpy(str,ch);
   result = NULL;
    result = strtok(str, delims);

   while(result != NULL ) {
      strcpy(arr1[j][i],result);
      result = strtok( NULL, delims );
      colcount++;
      i++;
   }
  printf("row1 %d done\n",j); 	
  j++;

  rowcount1++;
}


 fclose(fp);

 /* THRESHOLD FILE */

 fp = fopen(THRESHOLDFILE,"r");
  if(fp==NULL)
  {
    printf("Cannot open the file\n");
    return 0;
  }

 i=0;j=0;colcount=0;
 result = NULL;

 fseek(fp,0,SEEK_SET);

 while(fgets(ch,sizeof(ch),fp))
 {
  
   colcount=0;
   i=0;
  
    strcpy(str,ch);
   result = NULL;
    result = strtok(str, delims);

   
   while(result != NULL ) {
      
      strcpy(arr2[j][i],result);
     
      result = strtok( NULL, delims );
      colcount++;
      
      i++;
   }
  j++;
   printf("row2 %d done\n",j); 
  rowcount2++;

}

fclose(fp);
 return 0;
}
int main()
{
 int ret_val1,ret_val2,l=0;
 int k=0,flag,count,c=0;
 long i,j; 
 float mean[COLS],sum=0.0;	
 int block_size=feature_length,n=10;
 int num_blocks=rowcount1;
 FILE *f = NULL;
 char ***arr1,***arr2;
 arr1=(char***)malloc(sizeof(char)*ROWS*COLS*STRINGLENGTH); 	
 arr2=(char***)malloc(sizeof(char)*ROWS*COLS*STRINGLENGTH); 	

 for(i=0;i<ROWS;i++)
 {
	arr1[i]=(char**)malloc(sizeof(char)*COLS*STRINGLENGTH);	
	arr2[i]=(char**)malloc(sizeof(char)*COLS*STRINGLENGTH);	
	for(j=0;j<COLS;j++)
	{
		arr1[i][j]=(char*)malloc(sizeof(char)*STRINGLENGTH);
		arr2[i][j]=(char*)malloc(sizeof(char)*STRINGLENGTH);
	}
 }
	
 ret_val1=checkColumns();
 ret_val2=getArrays(arr1,arr2);

float *mean_data=(float*)malloc(sizeof(float)*feature_length);
 float *mean_threshold=(float*)malloc(sizeof(float)*feature_length);

 //float feature_data_h[ROWS][feature_length],feature_threshold_h[ROWS][feature_length];
float *feature_data_h[ROWS],*feature_threshold_h[ROWS];
 /* Host to Device */

 
for(j=0;j<ROWS;j++)
{
	feature_data_h[j]=(float*)malloc(sizeof(float)*feature_length);
}	

 count=0;
    for(j=0;j<COLS;j++)
    {

            for(k=0;k<feature_length;k++ )
            {
                flag=0;
                if(strcmp(arr1[0][j],features_1[k])==0)
                {
		    printf("features_1[k]=%s\t",features_1[k]); 
                    
                    flag=1;
                    break;
                }

            }        
        if(flag && ((strcmp(getType(arr1[1][j]),"Integer")==0) || strcmp(getType(arr1[1][j]),"Double")==0))
	{
		/* Kernel Function call */
 		for(i=1;i<rowcount1;i++)
			feature_data_h[i-1][count]=atof(arr1[i][j]);
                count++;
	}
    }
printf("\n----DATA----\n"); 
mean_data=calculateMean(feature_data_h,rowcount1-1,feature_length);



for(j=0;j<ROWS;j++)
{
	feature_threshold_h[j]=(float*)malloc(sizeof(float)*feature_length);
}	
 count=0;
    for(j=0;j<COLS;j++)
    {

            for(k=0;k<feature_length;k++ )
            {
                flag=0;
                if(strcmp(arr2[0][j],features_1[k])==0)
                {
                    
                    flag=1;
                    break;
                }

            }        
        if(flag && ((strcmp(getType(arr2[1][j]),"Integer")==0) || strcmp(getType(arr2[1][j]),"Double")==0))
	{
		/* Kernel Function call */
 		for(i=1;i<rowcount2;i++)
			feature_threshold_h[i-1][count]=atof(arr2[i][j]);
                count++;
	}
    }
printf("\n-----THRESHOLD----\n");
mean_threshold=calculateMean(feature_threshold_h,rowcount2-1,feature_length);
 

/*Calculating the difference of means */

f = fopen(FINALFEATURESFILE,"w");
FILE *fn = fopen(FINALFEATURESNAMEFILE,"w");
if(f==NULL)
{
  printf("\nCould not open the file\n");
}

if(fn==NULL)
{
  printf("\nCould not open the file\n");
}

for(i=0;i<feature_length;i++)
{
  if(abs(mean_data[i]-mean_threshold[i]) <= MEAN_DIFF_RANGE)
   {
	
      strcpy(features[l++],features_1[i]);

    }

}
printf("\nFinal features\n");
for(j=0;j<ROWS;j++)
{
 for(l=0;l<ROWS;l++)
  {
    if(strcmp(cols1[j],features[l])==0 && strcmp(cols1[j],"")!=0)
     {
             fprintf(f,"%ld,",j); 
	     fprintf(fn,"%s,",cols1[j]); 	
     }
  }
}

fseek(f,-1,SEEK_CUR);
fprintf(f,"%s"," "); 
fseek(fn,-1,SEEK_CUR);
fprintf(fn,"%s"," "); 
for(i=0;i<l;i++)
{
	printf("%s\t",features[i]);
 		
}
printf("No. of features=%d",feature_length);
fclose(f);
fclose(fn);
 return 0;
}

