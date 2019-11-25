.name "test grand sti"

.comment "je sti bcp"

l2: ld  %200,r1
    add r2,r2,r3
    sti r1,%:live,%1
    sti r1,%:live,%6
    sti r1,%:fork_bcl,%1
    fork %1

live: 
    live %1
    live %1
    zjmp %:live

fork_bcl:
    live %1
    fork %:live
    ld %0,r2
    zjmp %:fork_bcl
