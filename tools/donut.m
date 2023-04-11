donut_points = readmatrix("../data/donut_points.txt", 'Delimiter', ',');
donut_powers = readmatrix("../data/donut_powers.txt");

m = max(donut_powers);
donut_powers = donut_powers * (1 / m);

figure
cmap = jet(256); 
colors = interp1(linspace(0, 1, 256), jet(256), donut_powers);

scatter3(donut_points(:,1),donut_points(:,2), donut_points(:,3), [], colors);
axis equal