.name    "sebc"
.comment "sebc"

debut:
    ld 0, r11
    ldi -20, %0, r12
    lld -11, r13
    lldi -10, %0, r14
    st r11, 100
    st r12, 102
    st r13, 104
    st r14, 106
