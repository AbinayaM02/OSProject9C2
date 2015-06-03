#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include "knn.h"


//struct Node SampleCopy[MAX_SAMPLE];
float square(float t){
	return t*t;
}

float absv(float a, float b){
	if (a > b) return a-b;
	return b-a;
}

// CALCULATE DISTANCE OF EACH NODE
void getdistances(float *device_array,int predict_attr,struct Node* Sample,int *Sample_Num,int *Atttr_Num,char *Atttr_Seq){
	float dist;
	int i,j,k;
	for(i = 0; i < *Sample_Num; i++){
		for(j = 0, dist = 0, k = 0; j < *Atttr_Num; j++, k++){
			//skip the prediction attribute
			if(j == predict_attr){
				continue;
			}
			// if it is an real number, use ecludiean distance
			if(Atttr_Seq[k] == 'r'){
				dist += (device_array[j] - Sample[i].NumericAttributes[j])*(device_array[j] - Sample[i].NumericAttributes[j]);
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
float NUM_KNN(int index,int k,int predict_attr,struct Node* Sample,int *Sample_Num,int *Atttr_Num,char *Atttr_Seq){
	int i,j;
	float result = 0;
	int num_bytes=(*Sample_Num) * (*Atttr_Num) * sizeof(float);
	float *device_array = 0;
  	float *host_array = 0;
	host_array = (float*)malloc(num_bytes);	
	for(i=0;i<*Sample_Num;i++)
		for(j=0;j<*Atttr_Num;j++)
			host_array[i*(*Atttr_Num)+j]=Sample[i].NumericAttributes[j];
	
		
	getdistances(host_array,predict_attr,Sample,Sample_Num,Atttr_Num,Atttr_Seq);	
	
	free(host_array);   
  	

	quicksort(0,*Sample_Num-1,Sample);

	
	// vote and get average
	for(i = 1; i <= k ; i++){
		result += Sample[i].NumericAttributes[predict_attr];
	}
		result = result/k;
	return result; 

}

