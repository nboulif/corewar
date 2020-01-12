.name "bad_arg"

.comment "jjhsbdvdfv"

l2: sti r21,%:live,%1
    live: live %1
    sti r21,%2048,%1
    zjmp %:live
