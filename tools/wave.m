d = readmatrix("../data/waves_d", 'Delimiter', ',');
e = readmatrix("../data/waves_e", 'Delimiter', ',');
m = readmatrix("../data/waves_m", 'Delimiter', ',');

figure
quiver3(d(:,1), d(:,2), d(:,3), e(:,1), e(:,2), e(:,3), 'b')
hold on
quiver3(d(:,1), d(:,2), d(:,3), m(:,1), m(:,2), m(:,3), 'r')
grid
axis equal