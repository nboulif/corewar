


sed 's/ #-fsanitize=address/ -fsanitize=address/g' Makefile > Makefile_tmp ; rm Makefile ; mv Makefile_tmp Makefile
leaks=0
if [[ $1 == "-v"  ]]; then 
    leaks=1
    sed 's/ -fsanitize=address/ #-fsanitize=address/g' Makefile > Makefile_tmp ; rm Makefile ; mv Makefile_tmp Makefile
fi
make re

for arg in $(find error_test -name "*.s")
do
    player_name_tmp=$(basename $arg)
    player_name=${player_name_tmp%.*}
    printf "`tput setaf 3`#########   ${player_name}   ##########`tput sgr0`\n"

    printf "`tput setaf 4`#########   our   ##########`tput sgr0`\n"
    
    ASM_RESULT=$(./asm $arg)
    if [[ "$ASM_RESULT" == *"Writing output program to"*  ]]; then 
         echo "`tput setaf 1`$ASM_RESULT`tput sgr0`"
    else
        echo "$ASM_RESULT"
    fi

    printf "`tput setaf 4`#########   res   ##########`tput sgr0`\n"
    ASM_RES_RESULT=$(./asm_res $arg)
    if [[ "$ASM_RES_RESULT" == *"Writing output program to"*  ]]; then 
         echo "`tput setaf 1`$ASM_RES_RESULT`tput sgr0`"
    else
        echo "$ASM_RES_RESULT"
    fi

    if [[ $leaks == 1  ]]; then 
        leaks_definitely=''
        leaks_indirectly=''
        while read -r line ; do
            if [[ "$line" == *"definitely lost"*  ]]; then 
                leaks_definitely="$line"
            elif [[ "$line" == *"indirectly lost"*  ]]; then 
                leaks_indirectly="$line"
            fi
        done <<< "$(valgrind --leak-check=full --show-leak-kinds=all ./asm -a $arg 2>&1 | grep 'definitely\|indirectly')"

        if [[ "$leaks_definitely" == *"0 bytes in 0 blocks"*  ]] && [[ "$leaks_indirectly" == *"0 bytes in 0 blocks"*  ]]; then 
            echo "`tput setaf 2`OK`tput sgr0` => leaks"
        else
            if [[ "$leaks_definitely" != *"0 bytes in 0 blocks"* ]]; then echo "`tput setaf 1`$leaks_definitely`tput sgr0`" ;fi 
            if [[ "$leaks_indirectly" != *"0 bytes in 0 blocks"* ]]; then echo "`tput setaf 1`$leaks_indirectly`tput sgr0`" ;fi 
        fi
    fi

done

sed 's/ -fsanitize=address/ #-fsanitize=address/g' Makefile > Makefile_tmp ; rm Makefile ; mv Makefile_tmp Makefile

make fclean
