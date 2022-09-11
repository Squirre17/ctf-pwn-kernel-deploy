#!/bin/sh
cd rootfs
find . -print0 | \
	cpio -o --null --format=newc \
	> ../initrd.modified.cpio
cd ..

qemu-system-x86_64 \
     -m 64M \
     -nographic \
     -kernel ./bzImage \
     -append "console=ttyS0 loglevel=3 oops=panic panic=-1 nopti nokaslr" \
     -no-reboot \
     -cpu qemu64 \
     -monitor /dev/null \
     -initrd ./initrd.modified.cpio \
     -net nic,model=virtio \
     -net user