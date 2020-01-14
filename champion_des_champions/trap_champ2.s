.name "trap"

.comment "trap code"

ld 5,r1
live %0
sti r2,r3,r16
sti r5,r6,r16
ld %0,r16
zjmp %65
