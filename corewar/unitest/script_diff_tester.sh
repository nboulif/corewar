#-----------------------1 Player---------------------------------------------
#Gagnant
echo "Gagnant"
python3 unitest/test.py Gagnant ../resource/tests/Gagnant.cor

#ultima
echo "ultima"
python3 unitest/test.py ultima ../resource/tests/ultima.cor

#Kitty_Miaou
echo "Kitty_Miaou"
python3 unitest/test.py Kitty ../resource/tests/Kitty_Miaou.cor

#Backward
echo "Backward"
python3 unitest/test.py  Backward ../resource/tests/Backward.cor

#ForgottenOne
echo "ForgottenOne"
python3 unitest/test.py Forgotten ../resource/tests/ForgottenOne.cor


#jumper
echo "jumper"
python3 unitest/test.py jumper ../resource/tests/jumper.cor

#-----------------------2 Player---------------------------------------------
#Gagnant ultima
echo "Gagnant ultima"
python3 unitest/test.py gu ../resource/tests/Gagnant.cor ../resource/tests/ultima.cor

#ultima Gagnant
echo "ultima Gagnant"
python3 unitest/test.py ug ../resource/tests/ultima.cor ../resource/tests/Gagnant.cor

#Kitty_Miaou Gagnant
echo "Kitty_Miaou Gagnant"
python3 unitest/test.py kg ../resource/tests/Kitty_Miaou.cor ../resource/tests/Gagnant.cor

#jumper Gagnant
echo "jumper Gagnant"
python3 unitest/test.py jg ../resource/tests/jumper.cor ../resource/tests/Gagnant.cor

#gateau overwatch
echo "gateau overwatch"
python3 unitest/test.py go ../resource/tests/gateau.cor ../resource/tests/overwatch.cor

#-----------------------3 Player---------------------------------------------
#test Kitty_Miaou ForgottenOne
echo "test Kitty_Miaou ForgottenOne"
python3 unitest/test.py tKF ../resource/tests/test.cor ../resource/tests/Kitty_Miaou.cor ../resource/tests/ForgottenOne.cor

#Gagnant ultima Kitty_Miaou
echo "Gagnant ultima Kitty_Miaou"
python3 unitest/test.py guk ../resource/tests/Gagnant.cor ../resource/tests/ultima.cor ../resource/tests/Kitty_Miaou.cor

#Gagnant Backward ultima
echo "Gagnant Backward ultima"
python3 unitest/test.py gbu ../resource/tests/Gagnant.cor ../resource/tests/Backward.cor ../resource/tests/ultima.cor

#ForgottenOne Kitty_Miaou Gagnant
echo "ForgottenOne Kitty_Miaou Gagnant"
python3 unitest/test.py fkg ../resource/tests/ForgottenOne.cor ../resource/tests/Kitty_Miaou.cor ../resource/tests/Gagnant.cor

#jumper Gagnant Gagnant
echo "jumper Gagnant Gagnant"
python3 unitest/test.py jgg ../resource/tests/jumper.cor ../resource/tests/Gagnant.cor ../resource/tests/Gagnant.cor

#jumper jumper Gagnant
echo "jumper jumper Gagnant"
python3 unitest/test.py jjg ../resource/tests/jumper.cor ../resource/tests/jumper.cor ../resource/tests/Gagnant.cor

#-----------------------4 Player---------------------------------------------
#Gagnant Gagnant Gagnant Gagnant
echo "Gagnant Gagnant Gagnant Gagnant"
python3 unitest/test.py gggg ../resource/tests/Gagnant.cor ../resource/tests/Gagnant.cor ../resource/tests/Gagnant.cor ../resource/tests/Gagnant.cor

#Gagnant ultima ForgottenOne Kitty_Miaou
echo "Gagnant ultima ForgottenOne Kitty_Miaou"
python3 unitest/test.py GuFK ../resource/tests/Gagnant.cor ../resource/tests/ultima.cor ../resource/tests/ForgottenOne.cor ../resource/tests/Kitty_Miaou.cor

#jumper Gagnant overwatch gateau
echo "jumper Gagnant overwatch gateau"
python3 unitest/test.py jGog ../resource/tests/jumper.cor ../resource/tests/Gagnant.cor ../resource/tests/overwatch.cor ../resource/tests/gateau.cor

#Kitty_Miaou2 ultima Gagnant Backward
echo "Kitty_Miaou2 ultima Gagnant Backward"
python3 unitest/test.py K2uGB ../resource/tests/Kitty_Miaou2.cor ../resource/tests/ultima.cor ../resource/tests/Gagnant.cor ../resource/tests/Backward.cor

#ultima ultima ultima ultima
echo "ultima ultima ultima ultima"
python3 unitest/test.py uuuu ../resource/tests/ultima.cor ../resource/tests/ultima.cor ../resource/tests/ultima.cor ../resource/tests/ultima.cor

#jumper jumper Gagnant Gagnant
echo "jumper jumper Gagnant Gagnant"
python3 unitest/test.py jjGG ../resource/tests/jumper.cor ../resource/tests/jumper.cor ../resource/tests/Gagnant.cor ../resource/tests/Gagnant.cor

#Douceur_power run_Kitty_RUN Gagnant ultima
echo "Douceur_power run_Kitty_RUN Gagnant ultima"
python3 unitest/test.py DrGu ../resource/tests/Douceur_power.cor ../resource/tests/run_Kitty_RUN.cor ../resource/tests/Gagnant.cor ../resource/tests/ultima.cor
