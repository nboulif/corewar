# Documentation Corewar

## divers

> :label %direct (%: = direct label) rx[x] regitre
> pour un indriect on va lire 4 bytes

-> ldi et lldi doivent modifier le carry ?

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

> load
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
>> **action**
>>> direct
>>> [r2] = [d1]
>>
>>> indirect
>>> [r2] = [position + ([i1] % IDX_MOD)]
>
>> **carry**
>>> ([r3] == 0) ? 1 : 0

### ldi

> load from index
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
>> **action** 
>>> direct
>>> [r3] = [([1] + [2]) % IDX_MOD]
>>
>>> indirect
>>> [r3] = [([i1 % IDX_MOD] + [2]) % IDX_MOD]

### live

### lld

### lldi

### lfork

### or

### st

### sti

### sub

### xor

### zjmp