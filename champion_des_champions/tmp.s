.name "bonhomme"

.comment "jtemange"

# ld (02 d0 00 81 01 09 00 11) -> load le r1 511 case plus loin + zjmp les st qui suivent
02 d0 00 00 0f
ld 129,r1
zjmp %17

# ld %47186431,r2
# ld %17367057,r3

