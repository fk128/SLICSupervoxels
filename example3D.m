%%
% load images
I = imread('cameraman.tif');

I = repmat(I,[1 1 130]);

sv = 17;
s = 2;
opts.supervoxelsize= [sv sv sv];
opts.spacing = [s s s];
opts.compactness = 30;
opts.numIter = 5;
I = (round(mat2gray(I)*255));
%%
tic
S = SLICSupervoxelsMex(uint32(I),opts);
toc

s = size(I);
S = reshape(S,s);
S = S+1;

%%
[height, width, depth] = size(I);
rimg = zeros(height,width, depth);
gimg = zeros(height,width, depth);
bimg = zeros(height,width, depth);


nC = max(S(:));
tic
rp = regionprops(S,'PixelIdxList');
for i=1:length(rp)
    idx = rp(i).PixelIdxList;
    rimg(idx) = rand(1);
    gimg(idx) = rand(1);
    bimg(idx) = rand(1);

end
toc
out = double(I);
out(:,:,:,1) = rimg;
out(:,:,:,2) = gimg;
out(:,:,:,3) = bimg;




ratio = double(nC)/numel(I)
