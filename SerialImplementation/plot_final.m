filename = "data_coordinates.dat";
fid = fopen (filename, "r");
data = dlmread(filename,",",1,0);
data = data.'

t = linspace(0, 2*pi, 1000);
h = zeros(1,10);
k = data(1,:);
r = data(2,:);
rx = rand(10,1);
ry = rand(10,1);
for i = 1:10
	x = r(i).*cos(t) + h(i);
	y = r(i).*sin(t) + k(i);
	plot(x,y);
	hold on;
	scatter(rx(i).*r(i),ry(i).*r(i),[],sqrt(rx(i).^2 + ry(i).^2));
	hold on;
endfor
hold off;

axis square;
