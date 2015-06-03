#! /usr/bin/octave -qf

printf("The plot is getting generated...");
finalplot("Breast_data_coordinates.dat",0,0,1)
finalplot("Lung_data_coordinates.dat",0,0,2)
finalplot("Colon_data_coordinates.dat",0,0,3)
finalplot("Prostate_data_coordinates.dat",0,0,4)
printf("Final plot done!");
