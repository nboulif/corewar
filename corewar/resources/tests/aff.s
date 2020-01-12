.name "aff"

.comment "aff"

aff:
	sti r1,%:live,%1
	ld %30000, r2
    live: live %1
	aff r2
	and r1,%0,r1
	zjmp %:live 
