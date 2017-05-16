%% Load

plot_all = 0;

%%
t = [0 25 50 75 99];
for k = 1 : length(t); 
    file_omega = sprintf('../data/CFD_omega_%d.txt',t(k));
    file_psi   = sprintf('../data/CFD_psi_%d.txt',t(k));
    file_u     = sprintf('../data/CFD_u_%d.txt',t(k));
    file_v     = sprintf('../data/CFD_v_%d.txt',t(k));
    file_R     = sprintf('../data/CFD_R_%d.txt',t(k));
    omega(:,:,k) = load(file_omega);
    psi  (:,:,k) = load(file_psi);
    u    (:,:,k) = load(file_u);
    v    (:,:,k) = load(file_v);
    R    (:,:,k) = load(file_R);
end
%% 
k = 2;
[SY SX] = size(omega(:,:,1))
%%
if plot_all == 1 
for k = 1 : length(t)    
figure;
subplot(4,1,1);
im1 = imagesc(omega(:,:,k));
axis equal; axis xy; 
axis([0,SX,0,SY]);
caxis([-0.005 0.005]);
colormap jet;
colorbar;
title('Omega - Vorticity');
subplot(4,1,2);
im2 = contour(psi(:,:,k));
axis equal; axis xy;
axis([0,SX,0,SY]);
%caxis([-0.005 0.005]);
colormap jet;
colorbar;
title('Psi - Streamline');
subplot(4,1,3);
im3 = imagesc(u(:,:,k));
axis equal; axis xy;
axis([0,SX,0,SY]);
%caxis([-0.005 0.005]);
colormap jet;
colorbar;
title('u - Velocity')
subplot(4,1,4);
im4 = imagesc(v(:,:,k));
axis equal; axis xy;
axis([0,SX,0,SY]);
%caxis([-0.005 0.005]);
colormap jet;
colorbar;
title('v - Velocity')
end
end