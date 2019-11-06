section .data                     
end:    db 10
messaggio:    db 67,105,97,111,32,109,111,110,100,111,33,0
        section .text        
global _start
_start:
        mov rax,1               ;
        mov rdi,1     ;
        add r9,messaggio        ;
ciclo:  
        mov rsi,r9;       
        mov rdx,1    ;                        
        syscall       ;
        mov rsi,end              ;
        syscall
        add r9,1                ;
        mov r10,[r9]
        cmp r10,0              ;
        jne ciclo               ;
        
        mov     rax,60 ;Fine dell'esecuzione       
        syscall        ;

