.name    "sebc"
.comment "sebc"

xor 151123455, 190054921, r11
and 151123455, 190054921, r12
or 151123455, 190054921, r13
add r13, r12, r14
sub r13, r12, r15
st r11, 100
st r12, 102
st r13, 104
st r14, 106
st r15, 108
