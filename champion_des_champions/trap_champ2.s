.name "trap"

.comment "trap code"

ld 6,r1
live %0
sti r2,r3,r16
sti r5,r6,r16
ld %0,r16
zjmp %63

02 d0 00 06 01 01 00 00 00 00 0b 54 02 03 10 0b 54 05 06 10 02 90 00 00 00 00 10 09 00 3f