donut_points = readmatrix("../data/donut_points.txt", 'Delimiter', ',');
donut_powers = readmatrix("../data/donut_powers.txt");
holes = 0 * donut_points;

figure

cmap = jet(256);   % Replace with your preferred color map
colors = interp1(linspace(0, 1, 256), jet(256), donut_powers);


% Plot points with colored markers
scatter3(donut_points(:,1),donut_points(:,2), donut_points(:,3), [], colors);
axis equal