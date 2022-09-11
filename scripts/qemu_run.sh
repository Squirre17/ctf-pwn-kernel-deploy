#!/bin/sh

# copy directly
# qemu-system-x86_64 \
#     -m 256M \
#     -kernel ./bzImage \
#     -initrd ./initrd.modified.cpio \
#     -append "root=/dev/ram rw console=ttyS0 oops=panic panic=1 quiet nokaslr" \
#     -cpu qemu64,+smep,+smap \
#     -nographic \
#     -monitor /dev/null

qemu-system-x86_64 \
	-m 256M \
	-kernel ./bzImage \
	-initrd ./initrd.modified.cpio \
	-append "console=ttyS0 oops=panic panic=1 quiet nokaslr" \
	-no-reboot \
	-cpu qemu64 \
	-nographic \
	-net nic,model=virtio \
	-net user \
	-monitor /dev/null
