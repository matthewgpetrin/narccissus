d0 = readmatrix("../data/waves_d0", 'Delimiter', ',');
e0 = readmatrix("../data/waves_e0", 'Delimiter', ',');
m0 = readmatrix("../data/waves_m0", 'Delimiter', ',');

d1 = readmatrix("../data/waves_d1", 'Delimiter', ',');
e1 = readmatrix("../data/waves_e1", 'Delimiter', ',');
m1 = readmatrix("../data/waves_m1", 'Delimiter', ',');

figure
quiver3(d0(:,1), d0(:,2), d0(:,3), e0(:,1), e0(:,2), e0(:,3), 'b')
hold on
quiver3(d0(:,1), d0(:,2), d0(:,3), m0(:,1), m0(:,2), m0(:,3), 'r')
grid on
quiver3(d1(:,1), d1(:,2), d1(:,3), e1(:,1), e1(:,2), e1(:,3), 'b')
hold on
quiver3(d1(:,1), d1(:,2), d1(:,3), m1(:,1), m1(:,2), m1(:,3), 'r')
view(30,45);
grid on
axis equal