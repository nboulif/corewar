.name "bonhomme"

.comment "jtemange"

#           mettre f1 en 'entier' dans les registres;

record:
    or %0,:f1,r2
    or %0,:f1,r2
    ld %0,r15

tmp:
    zjmp %:f1
f1:
#            ecrire r1 loin;        
    st r1,511
#            enregistrer le r1 ecrit au loin dans -> r1; aka corruption 
    ld 511,r1
#            ecrire remplir les registre && ecraser le code a tmp et f1 + 1
    ld %127139840,r2
    ld %514,r3
    st r2,:tmp
    sti r3,%:f1,%1

#            ecrire le code (f1) plus loin;
    
#            ecrire r1 en face du live a la prochaine ligne;
    sti r1,%7,%1
#            faire un live;
    live %19
#            sauter sur le code ecrit plus loin;
    zjmp %150
