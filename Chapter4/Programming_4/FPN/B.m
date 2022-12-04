x1=[-3.5,-3,-2.5,-2,-1.75,-1.5,-1.25,-1,-0.875,-0.75,-0.625,-0.5,0,0.5,0.625,0.75,0.875,1,1.25,1.5,1.75,2,2.5,3,3.5];
y1=zeros(25,1);
axis([-4 4 -0.1 0.1]);
hold on
scatter(x1,y1,'filled');
legend('Normal');
title('B1');
figure;

x2=[-0.1875,-0.125,-0.0625,0.0625,0.125,0.1875];
y2=zeros(6,1);
axis([-4 4 -0.1 0.1]);
hold on
scatter(x1,y1,'filled');
scatter(x2,y2,'filled');
legend('Normal','Subnormal');
title('B2');

