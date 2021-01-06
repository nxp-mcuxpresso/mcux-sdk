
   IMGUTIL User Guide
  
   ======================================
   
   1. Build SDK2.x application
   2. Copy built binary (.bin file) to imgutil/<board> folder and rename to sdk20-app.bin
   3. In imgutil/<board> folder, run mkimg.sh to get bootable image file sdk20-app.img
       a. If the image is built with ram link file, use "mkimage.sh ram" to make the bootable image.
       b. If the image is built with flash link file, use "mkimage.sh flash" to make the bootable XIP image.
   4. In imgutil/<board> folder, qcb.bin is a binary block for "QuadSPI Configuration Parameters" which provides
      information to ROM how to configure the flash on board. For more information, see "QuadSPI serial flash memory
      boot" in the Processor Reference Manual. And users can create their own qcb.bin according to the flash type
      and performance requirement.

   ======================================
