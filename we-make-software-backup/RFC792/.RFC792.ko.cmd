savedcmd_RFC792.ko := ld -r -m elf_x86_64 -z noexecstack --no-warn-rwx-segments --build-id=sha1  -T /root/linux/scripts/module.lds -o RFC792.ko RFC792.o RFC792.mod.o .module-common.o
