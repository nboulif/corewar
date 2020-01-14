.name "bonhomme"

.comment "jtemange"

part1:
	ld %17367057,r3
	ld %47186041,r2
    ld %0,r15

part2:
    st r1,128

part3:
    st r3,-8
	st r2,-17

# part4:
# 	ld 129,r1
# 	zjmp %17

part6:
    sti r1,%:live,%1
live: live %19
    #zjmp %1
ld %0,r1
fork %-64
#fork %-64
