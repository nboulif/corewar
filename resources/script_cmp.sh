nb_lines_diff=""
declare -a op=( "live" "st" "add" "sub" "and" "or" "xor" "zjmp" "ldi" "sti" "fork" "lld" "lldi" "lfork" )
declare -a champ=( "Gagnant" "ultima" "Kitty_Miaou" "Backward" "jumper" "Douceur_power" "gateau" "overwatch" "maxidef" "run_Kitty_RUN" "test" "test2")
# #-----------------------1 Player---------------------------------------------
# for cur_champ in "${champ[@]}"
# do
#     ./a.out resources/tests/$cur_champ.cor -r > r$cur_champ
#     ./resources/vm_champs/corewar resources/tests/$cur_champ.cor -v 4 > v4$cur_champ
#     diff r$cur_champ v4$cur_champ > diff_rv4$cur_champ
#     echo "$cur_champ"
#     cat diff_rv4$cur_champ | grep "P "
#     nb_lines_diff=`cat diff_rv4$cur_champ | grep "P " | wc -l | bc -l`
#     #if [ $nb_lines_diff != "0" ]; then
#         # for i in "${op[@]}"
#         # do
#         #     # echo "$i"
#         #     nb=`cat v4$cur_champ | grep "$i" | wc -l | bc -l`
#         #     echo "($i : |${nb}|) "
#         # done
#     #fi
#     rm r$cur_champ v4$cur_champ diff_rv4$cur_champ
# done
# echo "FINISH FORR 1 Player"

# #-----------------------2 Player---------------------------------------------
# #Gagnant ultima
# ./a.out resources/tests/Gagnant.cor resources/tests/ultima.cor -r > rGu
# ./resources/vm_champs/corewar resources/tests/Gagnant.cor resources/tests/ultima.cor -v 4 > v4Gu
# diff rGu v4Gu > diff_rv4Gu
# echo "Gagnant ultima"
# cat diff_rv4Gu | grep "P "

# #ultima Gagnant
# ./a.out resources/tests/ultima.cor resources/tests/Gagnant.cor -r > ruG
# ./resources/vm_champs/corewar resources/tests/ultima.cor resources/tests/Gagnant.cor -v 4 > v4uG
# diff ruG v4uG > diff_rv4uG
# echo "ultima Gagnant"
# cat diff_rv4uG | grep "P "
# rm ruG v4uG diff_rv4uG

# #Kitty_Miaou Gagnant
# ./a.out resources/tests/Kitty_Miaou.cor resources/tests/Gagnant.cor -r > rKG
# ./resources/vm_champs/corewar resources/tests/Kitty_Miaou.cor resources/tests/Gagnant.cor -v 4 > v4KG
# diff rKG v4KG > diff_rv4KG
# echo "Kitty_Miaou Gagnant"
# cat diff_rv4KG | grep "P "
# rm rKG v4KG diff_rv4KG

# #jumper Gagnant
# ./a.out resources/tests/jumper.cor resources/tests/Gagnant.cor -r > rjG
# ./resources/vm_champs/corewar resources/tests/jumper.cor resources/tests/Gagnant.cor -v 4 > v4jG
# diff rjG v4jG > diff_rv4jG
# echo "jumper Gagnant"
# cat diff_rv4jG | grep "P "


# #gateau overwatch
# ./a.out resources/tests/gateau.cor resources/tests/overwatch.cor -r > rgo
# ./resources/vm_champs/corewar resources/tests/gateau.cor resources/tests/overwatch.cor -v 4 > v4go
# diff rgo v4go > diff_rv4go
# echo "gateau overwatch"
# cat diff_rv4go | grep "P "
# rm rgo v4go diff_rv4go

# #jumper overwatch
# ./a.out resources/tests/jumper.cor resources/tests/overwatch.cor -r > rjo
# ./resources/vm_champs/corewar resources/tests/jumper.cor resources/tests/overwatch.cor -v 4 > v4jo
# diff rjo v4jo > diff_rv4jo
# echo "jumper overwatch"
# cat diff_rv4jo | grep "P "
# rm rjo v4jo diff_rv4jo

# #run_Kitty_RUN ultima
# ./a.out resources/tests/run_Kitty_RUN.cor resources/tests/ultima.cor -r > rru
# ./resources/vm_champs/corewar resources/tests/run_Kitty_RUN.cor resources/tests/ultima.cor -v 4 > v4ru
# diff rru v4ru > diff_rv4ru
# echo "run_KittY_RUN ultima"
# cat diff_rv4ru | grep "P "

# #-----------------------3 Player---------------------------------------------
# #test Kitty_Miaou ForgottenOne
# ./a.out resources/tests/test.cor resources/tests/Kitty_Miaou.cor resources/tests/ForgottenOne.cor -r > rtKF
# ./resources/vm_champs/corewar resources/tests/test.cor resources/tests/Kitty_Miaou.cor resources/tests/ForgottenOne.cor -v 4 > v4tKF
# diff rtKF v4tKF > diff_rv4tKF
# echo "test Kitty_Miaou ForgottenOne"
# cat diff_rv4tKF | grep "P "
# rm rtKF v4tKF diff_rv4tKF

# #Gagnant ultima Kitty_Miaou
# ./a.out resources/tests/Gagnant.cor resources/tests/ultima.cor resources/tests/Kitty_Miaou.cor -r > rGuK
# ./resources/vm_champs/corewar resources/tests/Gagnant.cor resources/tests/ultima.cor resources/tests/Kitty_Miaou.cor -v 4 > v4GuK
# diff rGuK v4GuK > diff_rv4GuK
# echo "Gagnant ultima Kitty_Miaou"
# cat diff_rv4GuK | grep "P "
# rm rGuK v4GuK diff_rv4GuK

# #Gagnant Backward ultima
# ./a.out resources/tests/Gagnant.cor resources/tests/Backward.cor resources/tests/ultima.cor -r > rGBu
# ./resources/vm_champs/corewar resources/tests/Gagnant.cor resources/tests/Backward.cor resources/tests/ultima.cor -v 4 > v4GBu
# diff rGBu v4GBu > diff_rv4GBu
# echo "Gagnant Backward ultima"
# cat diff_rv4GBu | grep "P "
# rm rGBu v4GBu diff_rv4GBu

# #ForgottenOne Kitty_Miaou Gagnant
# ./a.out resources/tests/ForgottenOne.cor resources/tests/Kitty_Miaou.cor resources/tests/Gagnant.cor -r > rFKG
# ./resources/vm_champs/corewar resources/tests/ForgottenOne.cor resources/tests/Kitty_Miaou.cor resources/tests/Gagnant.cor -v 4 > v4FKG
# diff rFKG v4FKG > diff_rv4FKG
# echo "ForgottenOne Kitty_Miaou Gagnant"
# cat diff_rv4FKG | grep "P "
# rm rFKG v4FKG diff_rv4FKG

# #jumper Gagnant Gagnant
# ./a.out resources/tests/jumper.cor resources/tests/Gagnant.cor resources/tests/Gagnant.cor -r > rjGG
# ./resources/vm_champs/corewar resources/tests/jumper.cor resources/tests/Gagnant.cor resources/tests/Gagnant.cor -v 4 > v4jGG
# diff rjGG v4jGG > diff_rv4jGG
# echo "jumper Gagnant Gagnant"
# cat diff_rv4jGG | grep "P "
# rm rjGG v4jGG diff_rv4jGG

# #jumper jumper Gagnant
# ./a.out resources/tests/jumper.cor resources/tests/jumper.cor resources/tests/Gagnant.cor -r > rjjG
# ./resources/vm_champs/corewar resources/tests/jumper.cor resources/tests/jumper.cor resources/tests/Gagnant.cor -v 4 > v4jjG
# diff rjjG v4jjG > diff_rv4jjG
# echo "jumper jumper Gagnant"
# cat diff_rv4jjG | grep "P "
# rm rjjG v4jjG diff_rv4jjG

# #-----------------------4 Player---------------------------------------------
# #Gagnant Gagnant Gagnant Gagnant
# ./a.out resources/tests/Gagnant.cor resources/tests/Gagnant.cor resources/tests/Gagnant.cor resources/tests/Gagnant.cor -r > rGGGG
# ./resources/vm_champs/corewar resources/tests/Gagnant.cor resources/tests/Gagnant.cor resources/tests/Gagnant.cor resources/tests/Gagnant.cor -v 4 > v4GGGG
# diff rGGGG v4GGGG > diff_rv4GGGG
# echo "Gagnant Gagnant Gagnant Gagnant"
# cat diff_rv4GGGG | grep "P "
# rm rGGGG v4GGGG diff_rv4GGGG

# #Gagnant ultima ForgottenOne Kitty_Miaou
# ./a.out resources/tests/Gagnant.cor resources/tests/ultima.cor resources/tests/ForgottenOne.cor resources/tests/Kitty_Miaou.cor -r > rGuFK
# ./resources/vm_champs/corewar resources/tests/Gagnant.cor resources/tests/ultima.cor resources/tests/ForgottenOne.cor resources/tests/Kitty_Miaou.cor -v 4 > v4GuFK
# diff rGuFK v4GuFK > diff_rv4GuFK
# echo "Gagnant ultima ForgottenOne Kitty_Miaou"
# cat diff_rv4GuFK | grep "P "
# rm rGuFK v4GuFK diff_rv4GuFK

# #test2 test test test
# ./a.out resources/tests/test2.cor resources/tests/test.cor resources/tests/test.cor resources/tests/test.cor -r > rt2ttt
# ./resources/vm_champs/corewar resources/tests/test2.cor resources/tests/test.cor resources/tests/test.cor resources/tests/test.cor -v 4 > v4t2ttt
# diff rt2ttt v4t2ttt > diff_rv4t2ttt
# echo "test2 test test test"
# cat diff_rv4t2ttt | grep "P "
# rm rt2ttt v4t2ttt diff_rv4t2ttt

# #jumper Gagnant overwatch gateau
# ./a.out resources/tests/jumper.cor resources/tests/Gagnant.cor resources/tests/overwatch.cor resources/tests/gateau.cor -r > rjGog
# ./resources/vm_champs/corewar resources/tests/jumper.cor resources/tests/Gagnant.cor resources/tests/overwatch.cor resources/tests/gateau.cor -v 4 > v4jGog
# diff rjGog v4jGog > diff_rv4jGog
# echo "jumper Gagnant overwatch gateau"
# cat diff_rv4jGog | grep "P "
# rm rjGog v4jGog diff_rv4jGog

# #Kitty_Miaou2 ultima Gagnant Backward
# ./a.out resources/tests/Kitty_Miaou2.cor resources/tests/ultima.cor resources/tests/Gagnant.cor resources/tests/Backward.cor -r > rKuGB
# ./resources/vm_champs/corewar resources/tests/Kitty_Miaou2.cor resources/tests/ultima.cor resources/tests/Gagnant.cor resources/tests/Backward.cor -v 4 > v4KuGB
# diff rKuGB v4KuGB > diff_rv4KuGB
# echo "Kitty_Miaou2 ultima Gagnant Backward"
# cat diff_rv4KuGB | grep "P " | wc -l
# rm rKuGB v4KuGB diff_rv4KuGB

#ultima ultima ultima ultima
./a.out resources/tests/ultima.cor resources/tests/ultima.cor resources/tests/ultima.cor resources/tests/ultima.cor -r > ruuuu
./resources/vm_champs/corewar resources/tests/ultima.cor resources/tests/ultima.cor resources/tests/ultima.cor resources/tests/ultima.cor -v 4 > v4uuuu
diff ruuuu v4uuuu | grep "P" > diff_rv4uuuu
echo "ultima ultima ultima ultima"
cat diff_rv4uuuu | wc -l
#  
for i in "${op[@]}"
do
    # echo "$i"
    nb=`cat v4uuuu | grep "$i" | wc -l | bc -l`
    echo "($i : |${nb}|) "
done

#jumper jumper Gagnant Gagnant
./a.out resources/tests/jumper.cor resources/tests/jumper.cor resources/tests/Gagnant.cor resources/tests/Gagnant.cor -r > rjjGG
./resources/vm_champs/corewar resources/tests/jumper.cor resources/tests/jumper.cor resources/tests/Gagnant.cor resources/tests/Gagnant.cor -v 4 > v4jjGG
diff rjjGG v4jjGG > diff_rv4jjGG
echo "jumper jumper Gagnant Gagnant"
cat diff_rv4jjGG | grep "P " | wc -l

for i in "${op[@]}"
do
    # echo "$i"
    nb=`cat v4jjGG | grep "$i" | wc -l | bc -l`
    echo "($i : |${nb}|) "
done

#overwatch overwatch Gagnant Gagnant
./a.out resources/tests/overwatch.cor resources/tests/overwatch.cor resources/tests/Gagnant.cor resources/tests/Gagnant.cor -r > rooGG
./resources/vm_champs/corewar resources/tests/overwatch.cor resources/tests/overwatch.cor resources/tests/Gagnant.cor resources/tests/Gagnant.cor -v 4 > v4ooGG
diff rooGG v4ooGG > diff_rv4ooGG
echo "overwatch overwatch Gagnant Gagnant"
cat diff_rv4ooGG | grep "P "
rm rooGG v4ooGG diff_rv4ooGG

#jumper jumper overwatch overwatch
./a.out resources/tests/jumper.cor resources/tests/jumper.cor resources/tests/overwatch.cor resources/tests/overwatch.cor -r > rjjoo
./resources/vm_champs/corewar resources/tests/jumper.cor resources/tests/jumper.cor resources/tests/overwatch.cor resources/tests/overwatch.cor -v 4 > v4jjoo
diff rjjoo v4jjoo > diff_rv4jjoo
echo "jumper jumper overwatch overwatch"
cat diff_rv4jjoo | grep "P "

#jumper Gagnant jumper Gagnant
./a.out resources/tests/jumper.cor resources/tests/Gagnant.cor resources/tests/jumper.cor resources/tests/Gagnant.cor -r > rjGjG
./resources/vm_champs/corewar resources/tests/jumper.cor resources/tests/Gagnant.cor resources/tests/jumper.cor resources/tests/Gagnant.cor -v 4 > v4jGjG
diff rjGjG v4jGjG > diff_rv4jGjG
echo "jumper Gagnant jumper Gagnant"
cat diff_rv4jGjG | grep "P " | wc -l
rm rjGjG v4jGjG diff_rv4jGjG

#Gagnant Gagnant jumper jumper
./a.out resources/tests/Gagnant.cor resources/tests/Gagnant.cor resources/tests/jumper.cor resources/tests/jumper.cor -r > rGGjj
./resources/vm_champs/corewar resources/tests/Gagnant.cor resources/tests/Gagnant.cor resources/tests/jumper.cor resources/tests/jumper.cor -v 4 > v4GGjj
diff rGGjj v4GGjj > diff_rv4GGjj
echo "Gagnant Gagnant jumper jumper"
cat diff_rv4GGjj | grep "P "

#ultima ultima jumper jumper
./a.out resources/tests/ultima.cor resources/tests/ultima.cor resources/tests/jumper.cor resources/tests/jumper.cor -r > ruujj
./resources/vm_champs/corewar resources/tests/ultima.cor resources/tests/ultima.cor resources/tests/jumper.cor resources/tests/jumper.cor -v 4 > v4uujj
diff ruujj v4uujj > diff_rv4uujj
echo "ultima ultima jumper jumper"
cat diff_rv4uujj | grep "P "

#jumper jumper ultima ultima 
./a.out resources/tests/jumper.cor resources/tests/jumper.cor resources/tests/ultima.cor resources/tests/ultima.cor -r > rjjuu
./resources/vm_champs/corewar resources/tests/jumper.cor resources/tests/jumper.cor resources/tests/ultima.cor resources/tests/ultima.cor -v 4 > v4jjuu
diff rjjuu v4jjuu > diff_rv4jjuu
echo "jumper jumper ultima ultima"
cat diff_rv4jjuu | grep "P "

#mise_a_jour maxidef run_Kitty_RUN jumper
./a.out resources/tests/mise_a_jour_windows95.cor resources/tests/maxidef.cor resources/tests/run_Kitty_RUN.cor resources/tests/jumper.cor -r > rmimarj
./resources/vm_champs/corewar resources/tests/mise_a_jour_windows95.cor resources/tests/maxidef.cor resources/tests/run_Kitty_RUN.cor resources/tests/jumper.cor -v 4 > v4mimarj
diff rmimarj v4mimarj > diff_rv4mimarj
echo "mise_a_jour maxidef run_Kitty_RUN jumper"
cat diff_rv4mimarj | grep "P "


#Douceur_power run_Kitty_RUN Gagnant ultima
./a.out resources/tests/Douceur_power.cor resources/tests/run_Kitty_RUN.cor resources/tests/Gagnant.cor resources/tests/ultima.cor -r > rDrGu
./resources/vm_champs/corewar resources/tests/Douceur_power.cor resources/tests/run_Kitty_RUN.cor resources/tests/Gagnant.cor resources/tests/ultima.cor -v 4 > v4DrGu
diff rDrGu v4DrGu > diff_rv4DrGu
echo "Douceur_power run_Kitty_RUN Gagnant ultima"
cat diff_rv4DrGu | grep "P " | wc -l

#Douceur_power Douceur_power Douceur_power Douceur_power
./a.out resources/tests/Douceur_power.cor resources/tests/Douceur_power.cor resources/tests/Douceur_power.cor resources/tests/Douceur_power.cor -r > rDDDD
./resources/vm_champs/corewar resources/tests/Douceur_power.cor resources/tests/Douceur_power.cor resources/tests/Douceur_power.cor resources/tests/Douceur_power.cor -v 4 > v4DDDD
diff rDDDD v4DDDD > diff_rv4DDDD
echo "Douceur_power Douceur_power Douceur_power Douceur_power"
cat diff_rv4DDDD | grep "P "
rm rDDDD v4DDDD diff_rv4DDDD

#Douceur_power run_Kitty_RUN jumper Douceur_power
./a.out resources/tests/Douceur_power.cor resources/tests/run_Kitty_RUN.cor resources/tests/jumper.cor resources/tests/Douceur_power.cor -r > rDrjD
./resources/vm_champs/corewar resources/tests/Douceur_power.cor resources/tests/run_Kitty_RUN.cor resources/tests/jumper.cor resources/tests/Douceur_power.cor -v 4 > v4DrjD
diff rDrjD v4DrjD > diff_rv4DrjD
echo "Douceur_power run_Kitty_RUN jumper Douceur_power"
cat diff_rv4DrjD | grep "P "
rm rDrjD v4DrjD diff_rv4DrjD

#Gagnant Douceur_power maxidef mise_a_jour
./a.out resources/tests/Gagnant.cor resources/tests/Douceur_power.cor resources/tests/maxidef.cor resources/tests/mise_a_jour_windows95.cor -r > rGDmami
./resources/vm_champs/corewar resources/tests/Gagnant.cor resources/tests/Douceur_power.cor resources/tests/maxidef.cor resources/tests/mise_a_jour_windows95.cor -v 4 > v4GDmami
diff rGDmami v4GDmami > diff_rv4GDmami
echo "Gagnant Douceur_power maxidef mise_a_jour"
cat diff_rv4GDmami | grep "P " | wc -l
