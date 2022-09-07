.PHONY: gdb run compile pack unzip init extract
RED="\\033[31m"
BLUE="\\033[34m"
GREEN="\\033[32m"
DFT="\\033[0m"
NOTIFY=[${BLUE}*${DFT}]
ERROR =[${RED}!${DFT}]
DONE  =[${GREEN}+${DFT}]
spath =./scripts
init:
	@echo "${NOTIFY} (only need once)Initializing..."
	@chmod +x -R ${spath}
	@${spath}/rename.sh
	@chmod +x ./initrd.cpio
	@${spath}/cpio.sh unzip

compile:
	@echo "${NOTIFY} Compiling..."
	@gcc -g -o ./rootfs/exp exp.c --static -lpthread
	@echo "${DONE} Compile done"

unzip:
	@echo "${NOTIFY} Unzipping..."
	@${spath}/cpio.sh unzip

pack:
	@echo "${NOTIFY} Pack..."
	@${spath}/cpio.sh zip

gdb:compile pack
	@echo "${NOTIFY} open gdb port on 1234"
	@${spath}/qemu_gdb.sh

run:compile pack
	@echo "${NOTIFY} >> make run must after init <<"
	@echo "${NOTIFY} run qemu right now"
	@${spath}/qemu_run.sh

extract:
	@echo "Function testing ,NOT AVAIABLE ,ABORT"
	@exit 1
	@/usr/src/linux-headers-$(uname -r)/scripts/extract-vmlinux bzImage > vmlinux