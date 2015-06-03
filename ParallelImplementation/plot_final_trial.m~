function finalplot(filename,flag1,flag2,color)
fid = fopen (filename, "r");
data = dlmread(filename,",",1,0);
data = sort(data);
data = data.';


t = linspace(0, 2*pi, 1000);
pred = data(1,:);
act = data(2,:);
maximum = 0;
distinct = unique(act);
distinct = distinct.';

for i = 1:columns(data)
	if (maximum <= abs(pred(i) - act(i)))
		maximum = abs(pred(i) - act(i));
	endif
endfor

randy = randn(columns(act),1);
randy = abs(randy.').*maximum;

maximum

x = 2.*maximum.*cos(t) + median(pred)+(flag1.*150);
y = 2.*maximum.*sin(t) + median(act)+(flag2.*150);
plot(x,y,color);
hold on;



for i = 1 : columns(data)
	scatter(randy(i)-maximum+median(act)+(flag2.*150),pred(i)+(flag1.*150),[],color);
	hold on;
endfor

ylabel("Predicted Value");
xlabel("Actual Value");
legend("Blue : Breast Cancer Maroon : Lung Cancer Light Blue : Colon Cancer Yellow : Prostate Cancer");


axis square;
endfunction
