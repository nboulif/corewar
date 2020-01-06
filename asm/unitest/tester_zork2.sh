
MAIN_FOLDER="../../"
ASM_FOLDER="../"

ASM=$ASM_FOLDER"./asm"

MAKEFILE=$ASM_FOLDER"Makefile"
MAKEFILE_TMP=$ASM_FOLDER"Makefile_tmp"

ASM_RES=$MAIN_FOLDER"resource/./asm_res"
VM_CHAMPS=$MAIN_FOLDER"resource/champs"

ZORK2S="zork2.s"
ZORK2S_TMP="zork2_tmp.s"

sed 's/ #-fsanitize=address/ -fsanitize=address/g' $MAKEFILE > $MAKEFILE_TMP ; rm $MAKEFILE ; mv $MAKEFILE_TMP $MAKEFILE
leaks=0
if [[ $1 == "-v"  ]]; then 
    leaks=1
    sed 's/ -fsanitize=address/ #-fsanitize=address/g' $MAKEFILE > $MAKEFILE_TMP ; rm $MAKEFILE ; mv $MAKEFILE_TMP $MAKEFILE
fi

make -sC $ASM_FOLDER re

while read -r line ; do
    line_rem=$line
    if [[ ${line:0:1} == "#" ]]; then 
        line_rem=${line:1}
        sed "s/$line/$line_rem/g" $ZORK2S > $ZORK2S_TMP ; rm $ZORK2S ; mv $ZORK2S_TMP $ZORK2S

        echo "`tput setaf 3`#########   ${line_rem}   ##########`tput sgr0`"

        echo "`tput setaf 4`#########   our   ##########`tput sgr0`"
        
        ASM_RESULT=$($ASM $ZORK2S)
        if [[ "$ASM_RESULT" == *"Writing output program to"*  ]]; then 
            echo "`tput setaf 1`$ASM_RESULT`tput sgr0`"
        else
            echo "$ASM_RESULT"
        fi

        echo "`tput setaf 4`#########   res   ##########`tput sgr0`"
        ASM_RES_RESULT=$($ASM_RES $ZORK2S)
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
            done <<< "$(valgrind --leak-check=full --show-leak-kinds=all $ASM $ZORK2S 2>&1 | grep 'definitely\|indirectly')"

            if [[ "$leaks_definitely" == *"0 bytes in 0 blocks"*  ]] && [[ "$leaks_indirectly" == *"0 bytes in 0 blocks"*  ]]; then 
                echo "`tput setaf 2`OK`tput sgr0` => leaks"
            else
                if [[ "$leaks_definitely" != *"0 bytes in 0 blocks"* ]]; then echo "`tput setaf 1`$leaks_definitely`tput sgr0`" ;fi 
                if [[ "$leaks_indirectly" != *"0 bytes in 0 blocks"* ]]; then echo "`tput setaf 1`$leaks_indirectly`tput sgr0`" ;fi 
            fi
        fi
        
        sed "s/$line_rem/$line/g" $ZORK2S > $ZORK2S_TMP ; rm $ZORK2S ; mv $ZORK2S_TMP $ZORK2S
    fi
done <<< "$(cat $ZORK2S)"

sed 's/ -fsanitize=address/ #-fsanitize=address/g' $MAKEFILE > $MAKEFILE_TMP ; rm $MAKEFILE ; mv $MAKEFILE_TMP $MAKEFILE

make -sC $ASM_FOLDER fclean
