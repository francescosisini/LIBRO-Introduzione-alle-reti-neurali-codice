global _start
        
section .data   
messaggio:        db 'Ciao Mondo!', 10
section .text
_start:
        mov rax,1     ;       
        mov rdi,1     ;
        mov rsi, messaggio  ;       
        mov rdx,12    ;                        
        syscall       ;                       
        mov     rax,60 ;       
        syscall        ;
