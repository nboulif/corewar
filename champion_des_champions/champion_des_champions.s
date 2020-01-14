.name "bonhomme"

.comment "jtemange"

part1:
	ld %47186048,r2
	ld %16945152,r3
    # d0 00 87 02 -> argument premier ld part4 + opc ld 0
    ld %15,r4
    # d0 00 00 0f -> argument ld 0 dans r15
    ld %252248077,r5 
    ld %0,r15

part2:
    st r1,128

part3:
	st r2,-5
    st r3,-6
    st r4,-7
    st r5,-9
# part4:
# 	ld 129,r1
# 	zjmp %17

part6:
    sti r1,%:live,%1
live: live %19
    #zjmp %1
fork %-75
ld %0,r1
#fork %-64
