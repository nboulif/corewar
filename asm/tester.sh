

pb_players=("Backward" "Misaka_Mikoto" "Torpille" "tdc2" "tdc3" "tdc4" "sebc" "new" "mat" "leeloo" "Death")

make

for arg in $(find .  -name "*.s")
do
    player_name_tmp=$(basename $arg)
    player_name=${player_name_tmp%.*}

    printf "`tput setaf 3`#########   ${player_name}   ##########`tput sgr0`\n"

    ASM_RESULT=$(./asm $arg)
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
        diff "${arg%.*}.mycor" "${arg%.*}.cor"
        rm "${arg%.*}.mycor" "${arg%.*}.cor"

    else
        if [[ " ${pb_players[@]} " =~ " ${player_name} " ]]; then
            echo "`tput setaf 4`Error compiling but its normal`tput sgr0`"
        else echo "`tput setaf 1`Error compiling`tput sgr0` => $arg" ;fi
        
        if [[ "$ASM_RESULT" == *"Writing output program to"* ]]; then
        rm "${arg%.*}.mycor"
        else echo "our : $ASM_RESULT";fi
        
        if [[ "$ASM_RES_RESULT" == *"Writing output program to"* ]]; then
        rm "${arg%.*}.cor"
        else echo "res : $ASM_RES_RESULT";fi

    fi
    # sleep 0.5
done

