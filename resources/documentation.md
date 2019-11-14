# Documentation Corewar

## divers

> :label %direct (%: = direct label) rx[x] regitre
> pour un indirect on va lire 4 bytes

-> ldi est le seul type [ld] qui ne modifie pas le carry

> choix arbitraires a verifier :

* ordre assigne aux nouveaux processus (choix actuel = debut de la liste des processus)
	* possibilite envisagee : pas d'ordre (les processus qui doivent s'executer lisent leurs arguments, et ensuite on reparcourt la liste pour l'execution)
* verification qu'un processus est en vie (choix actuel = 1ere verification ignoree meme sans live)

## operations

### add

> addition
>> **structure** -> 5 bytes
>>> operation code -> 1 byte
>>
>>> codage octal -> 1 byte
>>
>>> arguments
>>>> T_REG [r1] -> 1 byte
>>>
>>>> T_REG [r2] -> 1 byte
>>>
>>>> T_REG [r3] -> 1 byte
>
>> **action** -> 10 cycles
>>> [r3] = [r1] + [r2]
>
>> **carry**
>>> ([r3] == 0) ? 1 : 0

### aff

> affichage
>> **structure** -> 3 bytes
>>> operation code -> 1 byte
>>
>>> codage octal -> 1 byte 
>>
>>> arguments
>>>> T_REG [r1] -> 1 byte
>
>> **action** -> 2 cycles
>>> STDOUT << [r1] % 256

### and

> bitwise and
>> **structure** -> 5 - 11 bytes
>>> operation code -> 1 byte
>>
>>> codage octal -> 1 byte
>>
>>> arguments
>>>> T_REG [r1] -> 1 byte
>>>> T_DIR [d1] -> 4 bytes
>>>> t_IND [i1] -> 2 bytes
>>>
>>>> T_REG [r2] -> 1 byte
>>>> T_DIR [d2] -> 4 bytes
>>>> t_IND [i2] -> 2 bytes
>>>
>>>> T_REG [r3] -> 1 byte
>
>> **action** -> 6 cycles
>>> [r3] = [1] & [2]
>
>> **carry**
>>> ([r3] == 0) ? 1 : 0

### fork

> nouveau processus
>> **structure** -> 3 bytes
>>> operation code -> 1 byte
>>
>>> arguments
>>>> T_DIR [d1] -> 2 bytes
>
>> **action** -> 800 cycles
>>> cree un nouveau processus avec une copie des registres
>>>> position
>>>> new = old + ([d1] % IDX_MOD)

### ld

> sauvegarde dans un registre 
> * positionnement de lecture sans acces registre
> * contrainte de distance de lecture par IDX_MOD
>> **structure** -> 5 - 7 bytes
>>> operation code -> 1 byte
>>
>>> codage octal -> 1 byte
>>
>>> arguments
>>>> T_DIR [d1] -> 4 bytes
>>>> T_IND [i1] -> 2 bytes
>>>
>>>> T_REG [r2] -> 1 byte
>
>> **action** -> 5 cycles
>>> direct
>>> [r2] = [d1]
>>
>>> indirect
>>> [r2] = [position + ([i1] % IDX_MOD)]
>
>> **carry**
>>> ([r3] == 0) ? 1 : 0

### ldi

> sauvegarde dans un registre
> * possibilite d'acceder aux registre pour le positionnement de lecture
> * contrainte de distance de lecture par IDX_MOD
> * ne modifie pas le carry
>> **structure** -> 5 - 7 bytes
>>> operation code -> 1 byte
>>
>>> codage octal -> 1 byte
>>
>>> arguments
>>>> T_REG [r1] -> 1 byte
>>>> T_DIR [d1] -> 2 bytes
>>>> T_IND [i1] -> 2 bytes
>>>
>>>> T_REG [r2] -> 1 byte
>>>> T_DIR [d2] -> 2 bytes
>>>
>>>> T_REG [r3] -> 1 byte
>
>> **action** -> 25 cycles
>>> direct
>>> [r3] = [([1] + [2]) % IDX_MOD]
>>
>>> indirect
>>> [r3] = [([i1 % IDX_MOD] + [2]) % IDX_MOD]

### live

> signal de vie de processus et de champion
>> **structure** -> 5 bytes
>>> operation code -> 1 byte
>>
>>> arguments
>>>> T_DIR [d1] -> 4 bytes
>
>> **action** -> 10 cycles
>>> indique que le processus courant est en vie
>>> indique que le joueur d'index = [d1] est en vie

### lld

> sauvegarde dans un registre 
> * positionnement de lecture sans acces registre
>> **structure** -> 5 - 7 bytes
>>> operation code -> 1 byte
>>
>>> codage octal -> 1 byte
>>
>>> arguments
>>>> T_DIR [d1] -> 4 bytes
>>>> T_IND [i1] -> 2 bytes
>>>
>>>> T_REG [r2] -> 1 byte
>
>> **action** -> 10 cycles
>>> direct
>>> [r2] = [d1]
>>
>>> indirect
>>> [r2] = [position + [i1]]
>
>> **carry**
>>> ([r3] == 0) ? 1 : 0

### lldi

> sauvegarde dans un registre
> * possibilite d'acceder aux registre pour le positionnement de lecture
>> **structure** -> 5 - 7 bytes
>>> operation code -> 1 byte
>>
>>> codage octal -> 1 byte
>>
>>> arguments
>>>> T_REG [r1] -> 1 byte
>>>> T_DIR [d1] -> 2 bytes
>>>> T_IND [i1] -> 2 bytes
>>>
>>>> T_REG [r2] -> 1 byte
>>>> T_DIR [d2] -> 2 bytes
>>>
>>>> T_REG [r3] -> 1 byte
>
>> **action** -> 25 cycles
>>> direct
>>> [r3] = [\[1] + [2]]
>>
>>> indirect
>>> [r3] = [\[i1 % IDX_MOD] + [2]]

### lfork

### or

### st

### sti

### sub

### xor

### zjmp