.name "ldi"

.comment "no comment"

l2: ldi r1,r1,r15
    ldi -2,r1,r15
    ldi %2,%2,r15
    lldi r1,r1,r15
    lldi -2,r1,r15
    lldi %2,%2,r15
    or %0,%48,r10
    aff r10
    aff r10
    aff r10
