; Escreve um caractere do terminal
; Entradas:
; DX - Caractere a escrever
PRINT_CHAR proc

    push AX
    
    mov AH, 02H
    int 21H
    
    pop AX
    ret
    
endp

; L? um caractere do terminal
; Sa?das:
; AX - Caractere lido
READ_CHAR proc
    
    mov AH, 07H
    int 21H
    
    ret
    
endp

; L? do terminal um UINT_16
; Sa?das:
; AX - Caractere UINT_16 lido
READ_UINT16 proc      
              
    push BX
    push DX
              
    xor AX, AX
    xor DX, DX
    
    mov BX, 10
       
    READ_UINT16_START:
    
        push AX

            READ_UINT16_LOOP:
               
            call READ_CHAR

            cmp AL, CRET
            je READ_UINT16_END
            
            cmp AL, '0'
            jb READ_UINT16_LOOP
                    
            cmp AL, '9'
            ja READ_UINT16_LOOP
            
            mov DL, AL
            call PRINT_CHAR
            
            sub DL, '0'
            
            pop AX
            push DX
            
            mul BX
            
            pop DX
            add AX, DX
            
            jmp READ_UINT16_START

    READ_UINT16_END:    
    pop AX
    pop DX
    pop BX

    ret    
endp


; Imprime na tela um UINT_16
; Entradas:
; - AX: Caractere a escrever na tela
PRINT_UINT16 proc
    ; Salva registradores
    push AX
    push BX
    push CX
    push DX
    
    mov BX, 10       
    xor CX, CX
    
    PRINT_UINT16_LP:
    xor DX, DX
    div BX      ; AX = quociente, DX = resto
    
    push DX
    inc CX
    
    cmp AX, 0
    jne PRINT_UINT16_LP

    PRINT_UINT16_PRN:
    pop DX
    dec CX
    
    add DL, '0'
    call PRINT_CHAR
    
    cmp CX, 0
    jnz PRINT_UINT16_PRN
    

    ; Restaura variaveis    
    pop DX
    pop CX
    pop BX
    pop AX

    ret
endp
   
; Escreve uma nova linha na tela
PRINT_NEWLINE proc
    
    push DX    
  
    mov DL, LFED
    call PRINT_CHAR
            
    mov DL, CRET
    call PRINT_CHAR                      
    
    pop DX
    
    ret
endp

; Prints a string to the console
; IN DI - Address of string
; IN CX - String length
PRINT_STRING proc
    
    push AX
    push DI
    push CX
    
    PRINT_STRING_LOOP:               
        mov DX, [DI]
        call PRINT_CHAR
        inc DI
        loop PRINT_STRING_LOOP
    
    pop CX
    pop DI
    pop AX
    
    ret
endp