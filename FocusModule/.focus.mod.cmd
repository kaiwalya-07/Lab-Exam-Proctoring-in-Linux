cmd_/home/grim-reaper/kernel/FocusModule/focus.mod := printf '%s\n'   focus.o | awk '!x[$$0]++ { print("/home/grim-reaper/kernel/FocusModule/"$$0) }' > /home/grim-reaper/kernel/FocusModule/focus.mod
