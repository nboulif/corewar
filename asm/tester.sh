

make

file="zork2"

./asm "$file.s"
./asm_res "$file.s"


DIFF=$(diff $file.mycor zork2.cor)

if [ "$DIFF" != "" ] 
then echo "result = $DIFF"
else echo "same"; fi

