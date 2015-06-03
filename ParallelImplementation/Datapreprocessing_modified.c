#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define SIZE 100000

int main(){
	char ch,ch1;
	int lines=0;
	int l=0, h=0;
	int dline=0;
	int temp;
	int x[SIZE];
	int y[SIZE];
	int t1[SIZE];
	int t2[SIZE];
	int training_data[SIZE];
	int test_data[SIZE];
	int i,j,k,z;
	int flag0=0,flag1=0,f0=0,f1=0,fs1=0,fs2=0;
	int pos=0;
	int v=0;
	int rand_y,rand_x,rem, length_slope, total_length,fin_cord,final;
	int max_x=0,min_x=0,max_y=0,min_y=0,centroid_x,centroid_y;
	FILE *fp,*fp1,*fp2,*fpc;

	fp=fopen("cancer_data_1200.arff","r");
	if(fp==NULL){
		printf("\nCannot open file");
		exit(0);
	}
	while(ch!=EOF){
		ch=fgetc(fp);
		if(ch=='%' || ch=='@'){
			l++;
			ch=fgetc(fp);
		}
	}
	rewind(fp);
	ch=fgetc(fp);
	while(ch!=EOF){
		ch=fgetc(fp);
                if(ch=='\n'){
                	lines++;
			ch=fgetc(fp);
		}
	}
	//fclose(fp);
	//printf("\nNumber of lines not containing numeric data%d \n",l);
	//printf("\nTotal number of lines in file is %d \n",lines);
	dline = lines - l;
	printf("\nNumber of lines containing data in file is %d \n",dline);	
	
	for(i=0;i<SIZE;i++){
		x[i]=-1;
		y[i]=-1;
	}
	
	srand(time(NULL));
	for(i=0;i<dline;i++){
		x[i] = rand()%50;
		//printf("\n%d - %d ",i,x[i]);
	}
	//printf("\n-------------------------------");
	for(i=0;i<dline;i++){
		y[i] = rand()%100+1;
		//printf("\n%d - %d ",i,y[i]);
	}
	fpc=fopen("coordinates.dat","w");
	if(fpc==NULL){
		printf("\nCannot open file");
		exit(0);
	}
	for(i=0;i<dline;i++){
		fprintf(fpc,"%d\t",(i+1));
		fprintf(fpc,"%d\t",x[i]);
		fprintf(fpc,"%d\n",y[i]);
	}
	fclose(fpc);
	
	max_x=x[0];
	min_x=x[0];
	max_y=y[0];
	min_y=y[0];
	for(i=1;i<dline;i++){
		if(x[i]>=max_x && y[i]>=max_y){
			max_x=x[i];
			max_y=y[i];
		}
		if(x[i]<min_x && y[i]<min_y){
			min_x=x[i];
			min_y=y[i];
		}
	}

	//printf("\nmax points are [%d][%d]",max_x,max_y);
	//printf("\nmin points are [%d][%d]",min_x,min_y); 
	
	centroid_x=(max_x+min_x)/2;
	centroid_y=(max_y+min_y)/2;
	//printf("\ncentroid is [%d][%d]",centroid_x,centroid_y);

	rand_x=rand()%50;
	rand_y=rand()%100+1;
	//printf("\nrand_x=%d, rand_y=%d",rand_x,rand_y);
	z=0;
	if(rand_x>rand_y){
		if(rand_x>centroid_x){
			rem=rand_x;
			printf("\nrem 1 = %d",rem);
		}
		else{
			rem=rand_x+centroid_x;
			printf("\nrem 1 = %d",rem);
		}
		flag0=1;
	}
	else{
		if(rand_y>centroid_y){
			rem=rand_y;
			printf("\nrem 2 = %d",rem);
		}
		else{
			rem=rand_y+centroid_y;
			printf("\nrem 2 = %d",rem);
		}
		flag1=1;
	}
	
	if(flag0==1){
		fin_cord=((rem*centroid_y)/centroid_x)-centroid_y;
		if(fin_cord<=1){
			fin_cord=fin_cord+(rand()%16);
		}
		printf("\n fin_cord 1 = %d",fin_cord);
		/*fprintf(fpc,"%d\t",z);
		fprintf(fpc,"%d\t",rem);
		fprintf(fpc,"%d\n",z);
		fprintf(fpc,"%d\t",z);
		fprintf(fpc,"%d\t",z);
		fprintf(fpc,"%d\n",fin_cord);
		fclose(fpc);*/
		/*final=rem-centroid_x;
		printf("\nfinal 1 = %d",final);
		length_slope=sqrt(pow(final,2)+pow(centroid_y,2));
		printf("\nlength_slope 1 = %d",length_slope);
		total_length=2*length_slope;
		printf("\ntotal_length 1 = %d",total_length);
		fin_cord=sqrt(pow(total_length,2)-pow(rem,2));
		printf("\nfc 1 = %d",fin_cord);*/
	}
	if(flag1==1){
		fin_cord=((rem*centroid_x)/centroid_y)-centroid_x;
		if(fin_cord<=1){
			fin_cord=fin_cord+(rand()%16);
		}
		printf("\nfin_cord 2 = %d",fin_cord);
		/*fprintf(fpc,"%d\t",z);
		fprintf(fpc,"%d\t",z);
		fprintf(fpc,"%d\n",rem);
		fprintf(fpc,"%d\t",z);
		fprintf(fpc,"%d\t",fin_cord);
		fprintf(fpc,"%d\n",z);
		fclose(fpc);*/
		/*final=rem-centroid_y;
		printf("\nfinal 2 = %d",final);
		length_slope=sqrt(pow(final,2)+pow(centroid_x,2));
		printf("\nlength_slope 2 = %d",length_slope);
		total_length=2*length_slope;
		printf("\ntotal_length 2 = %d",total_length);
		fin_cord=sqrt(pow(total_length,2)-pow(rem,2));
		printf("\nfc 2 = %d",fin_cord);*/
	}	
	j=0;
	k=0;
	if(flag0==1){
	for(i=0;i<dline;i++){
			if(x[i]<=rem && y[i]<=fin_cord){
				t1[j]=i;
				//printf("\n%d",t1[j]);
				j++;
			}
			else{
				t2[k]=i;
				//printf("\n%d",t2[k]);
				k++;
			}
	}
	}
	if(flag1==1){
	for(i=0;i<dline;i++){
			if(x[i]<=fin_cord && y[i]<=rem){
				t1[j]=i;
				//printf("\n%d",t1[j]);
				j++;
			}
			else{
				t2[k]=i;
				//printf("\n%d",t2[k]);
				k++;
			}
	}
	}
	
	if(j>=k){
		f0=1;
	}
	else{
		f1=1;
	}

	/*fpn=fopen("/home/sana/Desktop/os/new.txt","w");
	if(fpn==NULL){
		printf("\nErrorin opening file");
		exit(0);
	}
	temp=l;
	rewind(fp);
	ch=fgetc(fp);
	while(temp>0){
		//ch=fgetc(fp);
		fprintf(fpn,"%c",ch);
		ch=fgetc(fp);
		if(ch=='\n')
			temp--;
	}
	fclose(fpn);*/

	fp1=fopen("training_data.arff","w");
	fp2=fopen("test_data.arff","w");

	if(fp1==NULL){
		printf("\n1. Cannot open file");
		exit(0);
	}
	if(fp2==NULL){
		printf("\n2. Cannot open file");
		exit(0);
	}

	if(f0==1){
		//printf("\n--------------------------------------");
		printf("\nTraining data sets are:");
		temp=l;
		rewind(fp);
		ch=fgetc(fp);
		while(temp>0){
			//ch=fgetc(fp);
			fprintf(fp1,"%c",ch);
			ch=fgetc(fp);
			if(ch=='\n'){
				temp--;
				pos++;
			}
		}
		fprintf(fp1,"\n",NULL);
		if(ch=='\n'){
			ch=fgetc(fp);
			pos++;
		}
		for(i=0;i<j;i++){
			training_data[i]=t1[i]+1;
			printf("\n%d",training_data[i]);
		}
		i=0;
		v=dline;
		while(v>0){
			if(training_data[i]+l==pos){
				while(ch!='\n'){
					fprintf(fp1,"%c",ch);
					ch=fgetc(fp);
				}
				fprintf(fp1,"\n",NULL);
				fs1=1;
			}
			else{
				while(ch!='\n'){
					ch=fgetc(fp);
				}
				fs1=0;
			}
			if(fs1==1){
				i++;
			}
			ch=fgetc(fp);
			pos++;
			v--;
		}
		/*for(i=0;i<j;i++){
			training_data[i]=t1[i]+1;
			fprintf(fp1,"\n%d",training_data[i]);
			printf("\n%d",training_data[i]);
		}*/
		//printf("\n--------------------------------------");
		fclose(fp1);
		printf("\nTest data sets are:");
		pos=0;
		temp=l;
		rewind(fp);
		ch=fgetc(fp);
		while(temp>0){
			if(temp==2)
				printf("");
			else
				fprintf(fp2,"%c",ch);
			ch=fgetc(fp);
			if(ch=='\n'){
				temp--;
				pos++;
			}
		}
		fprintf(fp2,"\n",NULL);
		if(ch=='\n'){
			ch=fgetc(fp);
			pos++;
		}
		for(i=0;i<k;i++){
			test_data[i]=t2[i]+1;
			printf("\n%d",test_data[i]);
		}
		i=0;
		v=dline;
		while(v>0){
			if(test_data[i]+l==pos){
				while(ch!='\n'){
					fprintf(fp2,"%c",ch);
					ch=fgetc(fp);
				}
				if(ch=='\n'){
					fseek(fp,-3,SEEK_CUR);
					ch=fgetc(fp);
					//printf("\nch=%c",ch);
					//printf("\nend");
				}
				while(ch!='\n'){
					//printf("\na ch = %c",ch);
					fseek(fp2,-2,SEEK_CUR);
					fprintf(fp2,"  ",NULL);
					ch=fgetc(fp);
					//printf("\nb ch = %c",ch);
				}
				fprintf(fp2,"\n",NULL);
				fs2=1;
			}
			else{
				while(ch!='\n'){
					ch=fgetc(fp);
				}
				fs2=0;
			}
			if(fs2==1){
				i++;
			}
			ch=fgetc(fp);
			pos++;
			v--;
		}

		fclose(fp2);
		fclose(fp);
	}
	if(f1==1){
		//printf("\n--------------------------------------");
		printf("\nTraining data sets are:");
		temp=l;
		rewind(fp);
		ch=fgetc(fp);
		while(temp>0){
			//ch=fgetc(fp);
			fprintf(fp1,"%c",ch);
			ch=fgetc(fp);
			if(ch=='\n'){
				temp--;
				pos++;
			}
		}
		fprintf(fp1,"\n",NULL);
		if(ch=='\n'){
			ch=fgetc(fp);
			pos++;
		}
		for(i=0;i<k;i++){
			training_data[i]=t2[i]+1;
			printf("\n%d",training_data[i]);
		}
		i=0;
		v=dline;
		while(v>0){
			if(training_data[i]+l==pos){
				while(ch!='\n'){
					fprintf(fp1,"%c",ch);
					ch=fgetc(fp);
				}
				fprintf(fp1,"\n",NULL);
				fs1=1;
			}
			else{
				while(ch!='\n'){
					ch=fgetc(fp);
				}
				fs1=0;
			}
			if(fs1==1){
				i++;
			}
			ch=fgetc(fp);
			pos++;
			v--;
		}
		//printf("\n--------------------------------------");
		fclose(fp1);
		printf("\nTest data sets are:");
		pos=0;
		temp=l;
		rewind(fp);
		ch=fgetc(fp);
		while(temp>0){
			if(temp==2)
				printf("");
			else
				fprintf(fp2,"%c",ch);
			//printf("\nhere");
			ch=fgetc(fp);
			if(ch=='\n'){
				temp--;
				pos++;
			}
		}
		fprintf(fp2,"\n",NULL);
		if(ch=='\n'){
			ch=fgetc(fp);
			pos++;
		}
		for(i=0;i<j;i++){
			test_data[i]=t1[i]+1;
			printf("\n%d",test_data[i]);
		}
		i=0;
		v=dline;
		while(v>0){
			if(test_data[i]+l==pos){
				while(ch!='\n'){
					fprintf(fp2,"%c",ch);
					ch=fgetc(fp);
				}
				if(ch=='\n'){
					fseek(fp,-3,SEEK_CUR);
					ch=fgetc(fp);
					//printf("\nch=%c",ch);
					//printf("\nend");
				}
				while(ch!='\n'){
					//printf("\na ch = %c",ch);
					fseek(fp2,-2,SEEK_CUR);
					fprintf(fp2,"  ",NULL);
					ch=fgetc(fp);
					//printf("\nb ch = %c",ch);
				}
				fprintf(fp2,"\n",NULL);
				fs2=1;
			}
			else{
				while(ch!='\n'){
					ch=fgetc(fp);
				}
				fs2=0;
			}
			if(fs2==1){
				i++;
			}
			ch=fgetc(fp);
			pos++;
			v--;
		}

		fclose(fp2);
		fclose(fp);
	}
	return 0;
}
