.name "corrupt"

.comment "je corrompt"

l2: sti r1,%:live,%1
live: live %1
sti r1,%2048,%1
zjump %:live