.name "test grand sti"

.comment "je sti bcp"

l2:
    and %0,%2156,r2
    sti r1,%:live,%1
    sti r17,%:live,%6

live: 
    live %1
    live %1
    zjmp %:live
