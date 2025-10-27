; Prints a character to the console
; INT DX - Character to print
PRINT_CHAR proc

    push AX
    
    mov AH, 02H
    int 21H
    
    pop AX
    ret
    
endp

; Reads a character from the console
; OUT AX - Character read
READ_CHAR proc
    mov AH, 07H
    int 21H
    
    ret
endp

; Reads an UINT_16 from the console
; OUT AX - UINT_16 read from console
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
            je READ_UINT16_END ; Read 'Enter', finish reading
            
            cmp AL, '0'
            jb READ_UINT16_LOOP ; Ignore if below ASCII code range
                    
            cmp AL, '9'
            ja READ_UINT16_LOOP ; Ignore if above ASCII code range
            
            mov DL, AL
            call PRINT_CHAR     ; Echo-out
            
            sub DL, '0'         ; Transform to regular digit
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


; Prints an UINT_16 to the screen
; IN AX: UINT_16 to print to screen
PRINT_UINT16 proc
    push AX
    push BX
    push CX
    push DX
    
    mov BX, 10       
    xor CX, CX
    
    PRINT_UINT16_LP: ; Pushes each digit to stack
        xor DX, DX
        div BX      ; AX = quotient, DX = remainder
        
        push DX
        inc CX
        
        cmp AX, 0
        jne PRINT_UINT16_LP

        PRINT_UINT16_PRN: ; Pops each digit and prints them
        pop DX
        dec CX
        
        add DL, '0'
        call PRINT_CHAR
        
        cmp CX, 0
        jnz PRINT_UINT16_PRN

    pop DX
    pop CX
    pop BX
    pop AX

    ret
endp
   
; Prints a new line to the screen
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