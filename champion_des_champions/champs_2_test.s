.name "4 fork"

.comment "yolo"

#sti r1,%:gengenf1,%1
sti r1,%:genf1,%1
ld %0,r16

#gengenf1:
#    live %0
#    fork %:f1
#    zjmp %:gengenf1

genf1:
    live %0
    fork %:f1
    zjmp %:genf1

f1:
    live %0
    fork %:forkage
    fork %:config3
config1:
    # (CODE)  : (02 d0 00 06) d=2 (dephase de 2 pour la superposition)
    ld %0x02d00006, r2
    # (INDEX) : distance - debut[=ldr + live + sti] + d (93 - 15[=5 + 5 + 5] + 2)
    ld %80, r3
    # (CODE)  : (00 06 01 01) d=4
    ld %0x00060101, r5
    # (INDEX) : debut[= ld + live + sti + sti] (93 - 20[= 5 + 5 + 5 + 5] + 4)
    ld %77, r6
    ld %0, r16
    zjmp %:code

forkage:
    fork %:config4

config2:
    # (CODE)  : (r1) d=8
    st r1, r2
    # (INDEX) : (93 - 15 + 8)
    ld %86, r3
    # (CODE)  : (0b 54 02 03) d=12
    ld %0x0b540203, r5
    # (INDEX) : (93 - 20 + 12)
    ld %85, r6
    ld %0, r16
    zjmp %:code

config3:
    # (CODE)  : (10 0b 54 05) d=16
    ld %0x100b5405, r2
    # (INDEX) : (93 - 15 + 16)
    ld %94, r3
    # (CODE)  : (06 10 02 90) d=20
    ld %0x06100290, r5
    # (INDEX) : (93 - 20 + 20)
    ld %93, r6
    ld %0, r16
    zjmp %:code

config4:
    # (CODE)  : (00 00 00 00) d=24
    ld %0x00000000, r2
    # (INDEX) : (93 - 15 + 24)
    ld %102, r3
    # (CODE)  : (10 09 00 3f) d=28
    ld %0x1009003f, r5
    # (INDEX) : (93 - 20 + 28)
    ld %101, r6
    ld %0, r16
    zjmp %:code

code:
    sti r2, r3, r16
    sti r5, r6, r16
    ld %0, r16
    # distance = taille code + zjmp[=61 + 2[=decalage interne]]
    zjmp %63
