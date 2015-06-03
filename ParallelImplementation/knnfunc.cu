/*********************************************
 *  knnfunc.c
 *  Sample KNN implementation
 *  COMP9417 Machine Learning and Data Mining
 *  UNSW Session 1, 2012
 *	Chengbin Wang z3313137

 *  KNN functions implementation
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include "knn.cuh"


//struct Node SampleCopy[MAX_SAMPLE];
float square(float t){
	return t*t;
}

float absv(float a, float b){
	if (a > b) return a-b;
	return b-a;
}

// CALCULATE DISTANCE OF EACH NODE
__global__ void getdistances(float *device_array,int predict_attr,struct Node* Sample, float* actual,int *Sample_Num,int *Atttr_Num,char *Atttr_Seq){
	float dist;
	int i,j,k;
	for(i = 0; i < *Sample_Num; i++){
		for(j = 0, dist = 0, k = 0; j < *Atttr_Num; j++, k++){
			//use the prediction attribute
			if(j == predict_attr){
				
			// if it is an real number, use ecludiean distance
			if(Atttr_Seq[k] == 'r'){
				dist += (device_array[i*(*Atttr_Num)+j] - actual[j])*(device_array[i*(*Atttr_Num)+j] - actual[j]);
			}
		    }
		}
		Sample[i].distance = sqrt(dist);
	}
}

// quick sort the Nodes with distances
void quicksort(int low, int high,struct Node* Sample){

	int i,j,piviot;
	struct Node t;

	if(high > low){
		piviot = (low+high)/2;
		SWAP(t,Sample[low],Sample[piviot]);

		i = low + 1;
		j = high;
		while(i <= j){
			while(Sample[i].distance <= Sample[low].distance
				  && i <= high){i++;}
			while(Sample[j].distance >= Sample[low].distance
				  && j > low){j--;}
			if(i < j){
				SWAP(t,Sample[i],Sample[j]);
			}
		}
		SWAP(t,Sample[low],Sample[j]);
		quicksort ( low, j - 1,Sample );
		quicksort ( j + 1, high,Sample );
	}
}


//KNN to predict numeric value
float NUM_KNN(int index,int k,int predict_attr,struct Node* Sample,int *Sample_Num,int *Atttr_Num,char *Atttr_Seq,int predict_attr_count,float *actual){
	int i,j;
	float result = 0,sum=0;
	int num_bytes=(*Sample_Num) * (*Atttr_Num) * sizeof(float);
	float *device_array = 0;
  	float *host_array = 0;
	host_array = (float*)malloc(num_bytes);	
	for(i=0;i<*Sample_Num;i++)
		for(j=0;j<*Atttr_Num;j++)
			host_array[i*(*Atttr_Num)+j]=Sample[i].NumericAttributes[j];
	cudaMalloc((void**)&device_array, num_bytes);
	cudaMemcpy(device_array, host_array, num_bytes, cudaMemcpyHostToDevice);
	dim3 block_size;
 	block_size.x = *Sample_Num;
  	block_size.y = 1;

  	// configure a two dimensional grid as well
  	dim3 grid_size;
  	grid_size.x = *Sample_Num / block_size.x;
  	grid_size.y = *Atttr_Num / block_size.y;
	
	getdistances<<<grid_size,block_size>>>(device_array,predict_attr,Sample,actual,Sample_Num,Atttr_Num,Atttr_Seq);	
	cudaMemcpy(host_array, device_array, num_bytes, cudaMemcpyDeviceToHost);

	free(host_array);   
  	cudaFree(device_array);

	quicksort(0,*Sample_Num-1,Sample);

	
	// vote and get average
	for(i = 1; i <= k ; i++){
		result += Sample[i].NumericAttributes[predict_attr];
	}
		result = result/k;
	return result; 

}

