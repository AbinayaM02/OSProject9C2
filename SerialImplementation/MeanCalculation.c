#include <stdlib.h>
#include <stdio.h>

 void kernel(float *array,float *result_array,int rows,int columns)
{
  
  int index = 0,i;

  // map the two 2D block indices to a single linear, 1D block index
  float sum;
  for(index=0;index<columns;index++)
  {
	sum=0;
	for(i=0;i<rows;i++)	
        	sum=sum+array[i*columns+index];  
	result_array[index]=sum/rows;	  	  
  }
}

float* calculateMean(float **a,int num_elements_x,int num_elements_y)
{  
  int i,j,row;
  int num_bytes = num_elements_x * num_elements_y * sizeof(float);
//printf("num_x %d", num_elements_x);
//printf("num_y %d", num_elements_y);
//printf("num_bytes %d", num_bytes);
  float *device_array = 0;
  float *host_array = 0;
  float *host_result_array = 0;
  float *device_result_array = 0;
  printf("\n----calculating mean----\n");
  // allocate memory in either space
  host_array = (float*)malloc(num_bytes);
  host_result_array = (float*)malloc(num_elements_y*sizeof(float));
  for(i=0;i<num_elements_x;i++)
	for(j=0;j<num_elements_y;j++)
	{	
		host_array[i*num_elements_y+j]=a[i][j];
	}  
  
  for(i=0;i<num_elements_x;i++)
	{	
		for(j=0;j<num_elements_y;j++)
			printf("%f\t",host_array[i*num_elements_y+j]);
		printf("\n");	
	}
   printf("\n");
  // grid_size & block_size are passed as arguments to the triple chevrons as usual
  kernel(host_array,host_result_array,num_elements_x,num_elements_y);
  
  // print out the result element by element
  for(row = 0; row < num_elements_y; row++)
  {
    printf("Mean %d:%f\n",row+1,host_result_array[row]);
  }
  printf("\n");

  // deallocate memory 
  //free(host_array); 
  //free(host_result_array);  
  return host_result_array;
}
