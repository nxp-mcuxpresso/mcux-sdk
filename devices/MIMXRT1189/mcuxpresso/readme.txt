Mcuxpresso generates bootable image by default, image_hash_tool.py is used to add hash in container 
for bootable image at post-build steps. 
If user try to configure the Mcuxpresso to generate raw iamge(without boot header), should avoid to
use image_hash_tool.py at post-build.