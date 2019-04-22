close all; clear;

h = figure;
%axis tight manual % this ensures that getframe() returns a consistent size
filename = 'output.gif';

T = TerraNova_Data_Parser('Test.nova');
lRocker = T.Data(11);
lRocker = lRocker{1};
rRocker = T.Data(12);
rRocker = rRocker{1};
pitch = T.Data(17);
pitch = pitch{1};

max_t = max([lRocker.Time(end) rRocker.Time(end) pitch.Time(end)]);
pitch.Data = lowpass(pitch.Data, 0.001);
xlim([0 max_t]);
ylim([-40 20]);

plot(lRocker.Time, rad2deg(lRocker.Data), 'r', 'linewidth', 2);
hold on;
plot(rRocker.Time, rad2deg(rRocker.Data), 'b', 'linewidth', 2);
plot(pitch.Time, pitch.Data, 'k', 'linewidth', 2);
hold off;

legend('Left Rocker', 'Right Rocker', 'Chassis');


i = 1; j = 1; k = 1;
for time = 0:10:max_t
    
    hold on;
    ind = lRocker.Time <= time;
    plot(lRocker.Time(ind), rad2deg(lRocker.Data(ind)), 'r', 'linewidth', 2);
    ind = rRocker.Time <= time;
    plot(rRocker.Time(ind), rad2deg(rRocker.Data(ind)), 'b', 'linewidth', 2);
    ind = pitch.Time <= time;
    plot(pitch.Time(ind), pitch.Data(ind), 'k', 'linewidth', 2);
    hold off;
    
    drawnow 
    
    frame = getframe(h); 
    im = frame2im(frame); 
    [imind,cm] = rgb2ind(im,256); 
    
    if time == 0 
      imwrite(imind,cm,filename,'gif', 'DelayTime', 0.01, 'Loopcount',inf); 
    else 
      imwrite(imind,cm,filename,'gif', 'DelayTime', 0.01, 'WriteMode','append'); 
    end 
end