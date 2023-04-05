eo0 = readmatrix("../data/wave_0_e_o.txt", 'Delimiter', ',');
ed0 = readmatrix("../data/wave_0_e_d.txt", 'Delimiter', ',');

mo0 = readmatrix("../data/wave_0_m_o.txt", 'Delimiter', ',');
md0 = readmatrix("../data/wave_0_m_d.txt", 'Delimiter', ',');

eo1 = readmatrix("../data/wave_1_e_o.txt", 'Delimiter', ',');
ed1 = readmatrix("../data/wave_1_e_d.txt", 'Delimiter', ',');

mo1 = readmatrix("../data/wave_1_m_o.txt", 'Delimiter', ',');
md1 = readmatrix("../data/wave_1_m_d.txt", 'Delimiter', ',');

t = [5, -1, -1;          
     6, -1,  2;        
     7,  1, -1];


figure
quiver3(eo0(:,1), eo0(:,2), eo0(:,3), ed0(:,1), ed0(:,2), ed0(:,3),'b', 'AutoScale','off')
hold on
quiver3(mo0(:,1), mo0(:,2), mo0(:,3), md0(:,1), md0(:,2), md0(:,3), 'r', 'AutoScale','off')
hold on
quiver3(eo1(:,1), eo1(:,2), eo1(:,3), ed1(:,1), ed1(:,2), ed1(:,3), 'b', 'AutoScale','off')
hold on
quiver3(mo1(:,1), mo1(:,2), mo1(:,3), md1(:,1), md1(:,2), md1(:,3), 'r', 'AutoScale','off')
hold on
fill3(t(:,1), t(:,2), t(:,3), 'black')
grid on
axis equal

figure
plot3(eo0(:,1), eo0(:,2), eo0(:,3), ed0(:,1) + eo0(:,1), ed0(:,2) + eo0(:,2), ed0(:,3) + eo0(:,3),'b')
hold on
plot3(mo0(:,1), mo0(:,2), mo0(:,3), md0(:,1) + mo0(:,1), md0(:,2) + mo0(:,2), md0(:,3) + mo0(:,3), 'r')
hold on
plot3(eo1(:,1), eo1(:,2), eo1(:,3), ed1(:,1) + eo1(:,1), ed1(:,2) + eo1(:,2), ed1(:,3) + eo1(:,3), 'b')
hold on
plot3(mo1(:,1), mo1(:,2), mo1(:,3), md1(:,1) + mo1(:,1), md1(:,2) + mo1(:,2), md1(:,3) + mo1(:,3), 'r')
hold on
fill3(t(:,1), t(:,2), t(:,3), 'black')
grid on
axis equal