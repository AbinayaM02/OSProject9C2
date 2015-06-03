knn: knn.o getfile.o knnfunc.o
	gcc -g -o knn knn.o getfile.o knnfunc.o -lm

knn.o: knn.c
	gcc -g -c knn.c

getfile.o: getfile.c
	gcc -g -lm -c getfile.c

knnfunc.o: knnfunc.c
	gcc -g  -lm -c knnfunc.c
