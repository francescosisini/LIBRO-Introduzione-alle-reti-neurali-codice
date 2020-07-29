section .data                     
a:      db 1
b:      db 2
c:      db 0
d:      db 10
        section .text        
global _start
_start:
        mov al,[a]                ;
        add al,[b]                ;
        add al,48                  ;
        mov [c],al                ;
        mov rax,1                 ;
        mov rdi,1     ;
        mov rsi,c ;       
        mov rdx,2    ;                        
        syscall       ;                       
        mov     rax,60 ;       
        syscall        ;

