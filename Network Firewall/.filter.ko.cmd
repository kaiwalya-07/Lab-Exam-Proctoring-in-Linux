cmd_/home/grim-reaper/kernel/network/filter.ko := ld -r -m elf_x86_64 -z noexecstack --no-warn-rwx-segments --build-id=sha1  -T scripts/module.lds -o /home/grim-reaper/kernel/network/filter.ko /home/grim-reaper/kernel/network/filter.o /home/grim-reaper/kernel/network/filter.mod.o;  true
