modify exp.c, pack cpio, boot qemu then gdb attach and so on is fussy and error prone

so i format it to fixed template to focus on exploit without distraction

# demand

- launch qemu
- launch qemu with gdb port to 1234
- kill qemu(when no response)
- pack cpio(maybe it's some operation's dependency)
- objdump some function disassembly on which we will breakpoint
- unpack original cpio file
- base64 and strip

Use makefile to support some option to operate
also need gdbscript ...

all operation scripts were placed in `$path/scripts`.
root file system be placed in `$path/rootfs` in which we exp will locate.

exp.c in `$path` also need `initrd.modified.cpio` to avoid injure original cpio file.

so we need cpio file be renamed to `initrd.cpio` (`rename.sh` will do that)

# script

use script should in `$path`

`cpio.sh` execute `zip/unzip` function

need `initrd.cpio` file
```shell
➜  Kerexp ./scripts/cpio.sh unzip
➜  Kerexp ./scripts/cpio.sh zip  
```


