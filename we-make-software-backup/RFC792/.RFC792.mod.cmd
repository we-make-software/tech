savedcmd_RFC792.mod := printf '%s\n'   RFC792.o | awk '!x[$$0]++ { print("./"$$0) }' > RFC792.mod
