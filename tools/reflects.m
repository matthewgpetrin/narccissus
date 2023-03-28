o0 = readmatrix("../data/reflects_o0.txt", 'Delimiter', ',');
d0 = readmatrix("../data/reflects_d0.txt", 'Delimiter', ',');
o1 = readmatrix("../data/reflects_o1.txt", 'Delimiter', ',');
d1 = readmatrix("../data/reflects_d1.txt", 'Delimiter', ',');
o2 = readmatrix("../data/reflects_o2.txt", 'Delimiter', ',');
d2 = readmatrix("../data/reflects_d2.txt", 'Delimiter', ',');

t0 = [-2, 0, 0;
      -2, 2, 0;
      -2, 0, 2];

t1 = [2,  0, 1;
      1,  1, 2;
      1, -1, 2];

t2 = [0,  3, -2;
      2, -2, -2;
     -2, -2, -2];

t3 = [2, 0, 0;
      2, 2, 0;
      2, 0, 2];

figure
quiver3(o0(:,1), o0(:,2), o0(:,3), d0(:,1), d0(:,2), d0(:,3), 'Color', '[0 0.4470 0.7410]')
hold on
quiver3(o1(:,1), o1(:,2), o1(:,3), d1(:,1), d1(:,2), d1(:,3), 'Color', '[0.8500 0.3250 0.0980]')
hold on
quiver3(o2(:,1), o2(:,2), o2(:,3), d2(:,1), d2(:,2), d2(:,3), 'Color', '[0.9290 0.6940 0.1250]')
hold on
fill3(t0(:,1), t0(:,2), t0(:,3), 'white')
hold on
fill3(t1(:,1), t1(:,2), t1(:,3), 'white')
hold on
fill3(t2(:,1), t2(:,2), t2(:,3), 'white')
hold on
fill3(t3(:,1), t3(:,2), t3(:,3), 'white')
grid
axis equal
hold off

