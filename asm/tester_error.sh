
make

for arg in $(find error_test -name "*.s")
do
    player_name_tmp=$(basename $arg)
    player_name=${player_name_tmp%.*}
    printf "`tput setaf 3`#########   ${player_name}   ##########`tput sgr0`\n"
    printf "`tput setaf 4`#########   our   ##########`tput sgr0`\n"
    ASM_RESULT=$(./asm $arg)
    echo "$ASM_RESULT"
    printf "`tput setaf 4`#########   res   ##########`tput sgr0`\n"
    ASM_RES_RESULT=$(./asm_res $arg)
    echo "$ASM_RES_RESULT"

done

