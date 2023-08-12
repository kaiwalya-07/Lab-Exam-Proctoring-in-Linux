cmd_/home/grim-reaper/kernel/network/filter.mod := printf '%s\n'   filter.o | awk '!x[$$0]++ { print("/home/grim-reaper/kernel/network/"$$0) }' > /home/grim-reaper/kernel/network/filter.mod
