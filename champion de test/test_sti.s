.name "test grand sti"

.comment "je sti bcp"

l2:
ld 0,r1
sti r1,%:live,%1
live: live %1
zjmp %:live
