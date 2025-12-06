HANDLE_PLAYER_INPUT proc

    ; Diminui ao m?ximo o delay e o tempo de repeti??o das teclas
    ; TODO verificar outra forma de ler input, esse aqui ainda depende
    ; da repeti??o das teclas, o que ? muito lento
    mov AH, 03H
    mov AL, 05H
    xor BX, BX
    int 16H

    HANDLE_PLAYER_INPUT_LOOP:
        ; Check for input
        mov AH, 01H
        int 16H
       
        jz HANDLE_PLAYER_INPUT_END

        ; Read input
        mov AH, 00H
        int 16H
        
        HANDLE_PLAYER_INPUT_RIGHT:
            cmp AH, KEY_RIGHT
            jne HANDLE_PLAYER_INPUT_LEFT
            add [PLAYER_X], PLAYER_SPEED
        
        HANDLE_PLAYER_INPUT_LEFT:
            cmp AH, KEY_LEFT
            jne HANDLE_PLAYER_INPUT_UP
            sub [PLAYER_X], PLAYER_SPEED
            
        HANDLE_PLAYER_INPUT_UP:
            cmp AH, KEY_UP
            jne HANDLE_PLAYER_INPUT_DOWN
            sub [PLAYER_Y], PLAYER_SPEED
            
        HANDLE_PLAYER_INPUT_DOWN:
            cmp AH, KEY_DOWN
            jne HANDLE_PLAYER_INPUT_LOOP
            add [PLAYER_Y], PLAYER_SPEED            
            
        jmp  HANDLE_PLAYER_INPUT_LOOP
        
HANDLE_PLAYER_INPUT_END:
    ret
endp

; Updates the player position
UPDATE_PLAYER proc
    call HANDLE_PLAYER_INPUT
    ret
endp

; Draws the player character to the screen
DRAW_PLAYER proc
    mov CX, [PLAYER_IDX]
    
    mov     AX, [PLAYER_X]
    mov     BX, [PLAYER_Y]
    mov     SI, offset PLAYER_SPRITE
    call    DRAW_SPRITE

    inc CX
    and CX, 1
    mov [PLAYER_IDX], CX
    ret
endp