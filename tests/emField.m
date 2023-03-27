d = a(1:2:end, :);
c = zeros(size(d));

figure
plot3([c(:,1) d(:,1)]', [c(:,2) d(:,2)]', [c(:,3) d(:,3)]', 'r')
hold on
quiver3(a(:,1), a(:,2), a(:,3),b(:,1), b(:,2), b(:,3), 'b')
grid
axis equal