str:
 .ascii "Bonjour\n"
 .global _start

_start:
movl $4, %eax
movl $1, %ebx
movl $str, %ecx
movl $8, %edx
int $0x80
movl $1, %eax
movl $0, %ebx
int $0x80

;Compilation:
;as code.s -o code.o
;ld code.o -o code

;Execution:
;./code