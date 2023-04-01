o = readmatrix("../data/fields_o.txt", 'Delimiter', ',');
e = readmatrix("../data/fields_e.txt", 'Delimiter', ',');
m = readmatrix("../data/fields_m.txt", 'Delimiter', ',');

figure
quiver3(o(:,1), o(:,2), o(:,3), e(:,1), e(:,2), e(:,3), 'b');
hold on
quiver3(o(:,1), o(:,2), o(:,3), m(:,1), m(:,2), m(:,3), 'r');
grid on
axis equal