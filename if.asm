section .data                     
a:      db 1
b:      db 21
c:      db 0
d:      db 10
msg1:    db 'Somma minore di 10',10
msg2:    db 'Somma maggiore di 10',10
        section .text        
global _start
_start:
        mov al,[a]                ;
        add al,[b]                ;
        add al,48                  ;
        mov [c],al                ;
        cmp al,58                ;
        mov rax,1                 ;
        ja maggiore               ;
        mov rdi,1     ;
        mov rsi,msg1 ;       
        mov rdx,19    ;                        
        syscall       ;                       
        mov     rax,60 ;       
        syscall        ;
maggiore:               
        mov rdi,1     ;
        mov rsi,msg2 ;       
        mov rdx,21    ;                        
        syscall       ;                       
        mov     rax,60 ;       
        syscall        ;
