knn: knn.o getfile.o knnfunc.o
	nvcc -g -o knn knn.o getfile.o knnfunc.o -lm

knn.o: knn.cu 
	nvcc -g -c knn.cu 

getfile.o: getfile.cu 
	nvcc -g -lm -c getfile.cu 

knnfunc.o: knnfunc.cu 
	nvcc -g  -lm -c knnfunc.cu 
