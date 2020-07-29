        section .data
a:      dd 48                   
x:      dd 2
y:      dd 2

        section .text           
global _start

_start:
        ;; *** Procedura Caller o chiamante***
        ;; chiama la funzione somma dei quadrati
        ;; i due parametri della sono memorizzati in edi e esi
        mov edi,[x]               ;
        mov esi,[y]               ;
        ;; Chiamata alla procedura e attende il risultato in eax
        call somma_quadrati              ;       
        ;; Dopo la chiamata accede al risultato
        add [a],eax               ;
        mov rax,1             ;
        mov rdi,1       ; 
        mov rsi,a       ;       
        mov rdx,1    ;                        
        syscall
        mov     rax,60 ;Fine dell'esecuzione       
        syscall        ;

somma_quadrati:
        ;; *** Procedura Callee o chiamata***
        ;; calcola x^2
        mov eax,esi             ;
        mul esi             ;
        mov esi,eax             ;
        ;; calcola y^2
        mov eax,edi             ;       
        mul edi              ;
        mov edi,eax          ;
        ;; somma x^2 e y^2
        add edi,esi             ;
        ;; copia la somma in eax comme accordato con il chiamante
        mov eax,edi             ;       
        ret                     ;
