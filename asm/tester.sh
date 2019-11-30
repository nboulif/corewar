

sed 's/ #-fsanitize=address/ -fsanitize=address/g' Makefile > Makefile_tmp ; rm Makefile ; mv Makefile_tmp Makefile
leaks=0
if [[ $1 == "-v"  ]]; then 
    leaks=1
    sed 's/ -fsanitize=address/ #-fsanitize=address/g' Makefile > Makefile_tmp ; rm Makefile ; mv Makefile_tmp Makefile
fi
make re

# !!!!!!!!!! DESACTIVATE FSANITIZE FOR VALGRIND
pb_players=("Backward" "Misaka_Mikoto" "Torpille" "tdc2" "tdc3" "tdc4" "sebc" "new" "mat" "leeloo" "Death")

for arg in $(find vm_champs -name "*.s")
do
    player_name_tmp=$(basename $arg)
    player_name=${player_name_tmp%.*}

    printf "`tput setaf 3`#########   ${player_name}   ##########`tput sgr0`\n"

    ASM_RESULT=$(./asm $arg)
    if [[ "$ASM_RESULT" == *"Writing output program to"* ]]; then mv ${arg%.*}.cor ${arg%.*}.mycor ;fi
    ASM_RES_RESULT=$(./asm_res $arg)
    
    if [[ "$ASM_RESULT" == *"Writing output program to"* ]] && [[ "$ASM_RES_RESULT" == *"Writing output program to"* ]]; then
        DIFF=$(diff ${arg%.*}.mycor ${arg%.*}.cor)
        if [ "$DIFF" != "" ]; then
            echo "`tput setaf 1`binary difference`tput sgr0` => $arg"
            if [[ " ${pb_players[@]} " =~ " ${player_name} " ]]; then
                echo "`tput setaf 3`its normal`tput sgr0`"
            fi
            echo "$DIFF"
        else echo "`tput setaf 2`OK`tput sgr0` => $arg"
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

        diff "${arg%.*}.mycor" "${arg%.*}.cor"
        rm "${arg%.*}.mycor" "${arg%.*}.cor"

    else
        if [[ " ${pb_players[@]} " =~ " ${player_name} " ]]; then
            if [[ "${player_name}" == "tdc2" ]]; then echo "`tput setaf 5`Error compiling : (.extend)`tput sgr0` => $arg"
            elif [[ "${player_name}" == "tdc3" ]]; then echo "`tput setaf 5`Error compiling : (.extend)`tput sgr0` => $arg"
            elif [[ "${player_name}" == "tdc4" ]]; then echo "`tput setaf 5`Error compiling : (.extend/arithmetic)`tput sgr0` => $arg"
            elif [[ "${player_name}" == "new" ]]; then echo "`tput setaf 5`Error compiling : (.extend/arithmetic)`tput sgr0` => $arg"
            elif [[ "${player_name}" == "leeloo" ]]; then echo "`tput setaf 5`Error compiling : (arithmetic)`tput sgr0` => $arg"
            elif [[ "${player_name}" == "Torpille" ]]; then echo "`tput setaf 5`Error compiling : (.extend/arithmetic)`tput sgr0` => $arg"
            elif [[ "${player_name}" == "Backward" ]]; then echo "`tput setaf 5`Error compiling : (.extend/arithmetic)`tput sgr0` => $arg"
            elif [[ "${player_name}" == "Death" ]]; then echo "`tput setaf 5`Error compiling : (.extend/arithmetic)`tput sgr0` => $arg"
            elif [[ "${player_name}" == "mat" ]]; then echo "`tput setaf 5`Error compiling : (commad '.code 03 FF FF' ?)`tput sgr0` => $arg"
            elif [[ "${player_name}" == "sebc" ]]; then echo "`tput setaf 5`Error compiling : (empty program)`tput sgr0` => $arg"
            elif [[ "${player_name}" == "Misaka_Mikoto" ]]; then echo "`tput setaf 5`Error compiling : (';' as '#')`tput sgr0` => $arg"
            else echo "`tput setaf 1`Error compiling but its normal...`tput sgr0` => $arg" ; fi
        else echo "`tput setaf 1`Error compiling`tput sgr0` => $arg" ;fi
        
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

        if [[ "$ASM_RESULT" == *"Writing output program to"* ]]; then
        rm "${arg%.*}.mycor"
        else echo "our : $ASM_RESULT";fi
        
        if [[ "$ASM_RES_RESULT" == *"Writing output program to"* ]]; then
        rm "${arg%.*}.cor"
        else echo "res : $ASM_RES_RESULT";fi

    fi
    # sleep 0.5
done

sed 's/ -fsanitize=address/ #-fsanitize=address/g' Makefile > Makefile_tmp ; rm Makefile ; mv Makefile_tmp Makefile

make fclean