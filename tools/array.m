points = readmatrix("../data/points.txt", 'Delimiter', ',');
polesc = readmatrix("../data/polesc.txt", 'Delimiter', ',');
fields = readmatrix("../data/fields.txt", 'Delimiter', ',');
powers = readmatrix("../data/powers.txt", 'Delimiter', ',');

fields(isnan(fields)) = 0;

m = max(powers);
powers = powers * (1 / m);

points = points .* powers;

figure
cmap = jet(256); 
colors = interp1(linspace(0, 1, 256), jet(256), powers);
colors(isnan(colors)) = 0;
scatter3(points(:,1), points(:,2), points(:,3), [], colors, "filled");
hold on
scatter3(polesc(:,1), polesc(:,2), polesc(:,3), "black");
axis equal

figure
quiver3(points(:,1), points(:,2), points(:,3), fields(:,1), fields(:,2), fields(:,3), 'r')
hold on
scatter3(polesc(:,1), polesc(:,2), polesc(:,3), "black");
axis equal