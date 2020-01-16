.name "Ken"

.comment "omae wa mou shindeiru"

sti r1,%:genf1,%1
ld %0,r16

# inside code
# ld 6,r1
# live %0
# sti r2,r3,r16
# sti r5,r6,r16
# ld %0,r16
# zjmp %63
# 02 d0 00 06 01 01 00 00 00 00 0b 54 02 03 10 0b 54 05 06 10 02 90 00 00 00 00 10 09 00 3f

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
    ld %466, r3
    # (CODE)  : (00 06 01 01) d=4
    ld %0x00060101, r5
    # (INDEX) : debut[=ld + live + sti + sti] (93 - 20[=5 + 5 + 5 + 5] + 4)
    ld %463, r6
    ld %0, r16
    zjmp %:code

forkage:
    fork %:config4

config2:
    # (CODE)  : (r1) d=8
    st r1, r2
    # (INDEX) : (93 - 15 + 8)
    ld %472, r3
    # (CODE)  : (0b 54 02 03) d=12
    ld %0x0b540203, r5
    # (INDEX) : (93 - 20 + 12)
    ld %471, r6
    ld %0, r16
    zjmp %:code

config3:
    # (CODE)  : (10 0b 54 05) d=16
    ld %0x100b5405, r2
    # (INDEX) : (93 - 15 + 16)
    ld %480, r3
    # (CODE)  : (06 10 02 90) d=20
    ld %0x06100290, r5
    # (INDEX) : (93 - 20 + 20)
    ld %479, r6
    ld %0, r16
    zjmp %:code

config4:
    # (CODE)  : (00 00 00 00) d=24
    ld %0x00000000, r2
    # (INDEX) : (93 - 15 + 24)
    ld %488, r3
    # (CODE)  : (10 09 00 3f) d=28
    ld %0x100901c1, r5
    # (INDEX) : (93 - 20 + 28)
    ld %487, r6
    ld %0, r16
    zjmp %:code

code:
    sti r2, r3, r16
    sti r5, r6, r16
    ld %0, r16
    # distance[=93] = taille code[=30] + zjmp[=61 + 2[=decalage interne]]
    zjmp %449
