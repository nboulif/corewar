

sed 's/ #-fsanitize=address/ -fsanitize=address/g' Makefile > Makefile_tmp ; rm Makefile ; mv Makefile_tmp Makefile
leaks=0
if [[ $1 == "-v"  ]]; then 
    leaks=1
    sed 's/ -fsanitize=address/ #-fsanitize=address/g' Makefile > Makefile_tmp ; rm Makefile ; mv Makefile_tmp Makefile
fi
make re

while read -r line ; do
    line_rem=$line
    if [[ ${line:0:1} == "#" ]]; then 
        line_rem=${line:1}
        sed "s/$line/$line_rem/g" zork2.s > zork2_tmp.s ; rm zork2.s ; mv zork2_tmp.s zork2.s

        echo "`tput setaf 3`#########   ${line_rem}   ##########`tput sgr0`"

        echo "`tput setaf 4`#########   our   ##########`tput sgr0`"
        
        ASM_RESULT=$(./asm zork2.s)
        if [[ "$ASM_RESULT" == *"Writing output program to"*  ]]; then 
            echo "`tput setaf 1`$ASM_RESULT`tput sgr0`"
        else
            echo "$ASM_RESULT"
        fi

        echo "`tput setaf 4`#########   res   ##########`tput sgr0`"
        ASM_RES_RESULT=$(./asm_res zork2.s)
        if [[ "$ASM_RES_RESULT" == *"Writing output program to"*  ]]; then 
            echo "`tput setaf 1`$ASM_RES_RESULT`tput sgr0`"
        else
            echo "$ASM_RES_RESULT"
        fi

        if [[ $leaks == 1  ]]; then 
            leaks_definitely=''
            leaks_indirectly=''
            while read -r line2 ; do
                if [[ "$line2" == *"definitely lost"*  ]]; then 
                    leaks_definitely="$line2"
                elif [[ "$line2" == *"indirectly lost"*  ]]; then 
                    leaks_indirectly="$line2"
                fi
            done <<< "$(valgrind --leak-check=full --show-leak-kinds=all ./asm zork2.s 2>&1 | grep 'definitely\|indirectly')"

            if [[ "$leaks_definitely" == *"0 bytes in 0 blocks"*  ]] && [[ "$leaks_indirectly" == *"0 bytes in 0 blocks"*  ]]; then 
                echo "`tput setaf 2`OK`tput sgr0` => leaks"
            else
                if [[ "$leaks_definitely" != *"0 bytes in 0 blocks"* ]]; then echo "`tput setaf 1`$leaks_definitely`tput sgr0`" ;fi 
                if [[ "$leaks_indirectly" != *"0 bytes in 0 blocks"* ]]; then echo "`tput setaf 1`$leaks_indirectly`tput sgr0`" ;fi 
            fi
        fi
        
        sed "s/$line_rem/$line/g" zork2.s > zork2_tmp.s ; rm zork2.s ; mv zork2_tmp.s zork2.s
    fi
done <<< "$(cat zork2.s)"

sed 's/ -fsanitize=address/ #-fsanitize=address/g' Makefile > Makefile_tmp ; rm Makefile ; mv Makefile_tmp Makefile

make fclean
