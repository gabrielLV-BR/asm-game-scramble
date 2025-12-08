UPDATE_ENEMIES proc
    ; Estado dos inimigos
    ; DB Sprite index
    ; DW Posicao X
    ; DW Posicao Y
    mov CX, [ENEMY_LIST_COUNT]
    
    cmp CX, 0
    jnz UPDATE_ENEMY
    ret
    
    UPDATE_ENEMY:
        push CX
        
        mov SI, offset ENEMY_LIST
        mov AX, ENEMY_STRUCT_SIZE
        dec CX
        mul CX
        add SI, AX
        
        inc SI
        
        ; Move o inimigo pra esquerda
        sub [SI], 10
        
        mov AX, [SI]
        add SI, 2

        mov BX, [SI]
        add SI, 2
        
        
        xor CX, CX
        
        mov SI, offset ENEMY_SPRITE
        
        call DRAW_SPRITE
        pop CX
        loop UPDATE_ENEMY
    ret
endp

DRAW_ENEMIES proc
    ret
endp

; Cria um inimigo e o insere na lista de inimigos, caso possivel
SPAWN_ENEMY proc
    push AX
    push BX

    cmp [ENEMY_LIST_COUNT], ENEMY_LIST_CAPACITY
    jge SPAWN_ENEMY_END ; Sem espaco
    
        ; Realiza calculo da posicao do novo
        ; inimigo na lista
        mov AX, [ENEMY_LIST_COUNT]
        
        mov BX, ENEMY_STRUCT_SIZE
        mul BX
        
        add AX, offset ENEMY_LIST
        mov BX, AX
        
        ; Inicializa indice do sprite
        mov WORD PTR [BX], 0
        inc BX
        
        ; Inicializa posicao X
        mov [BX], SCREEN_WIDTH
        add BX, 2
        
        ; Inicializa posicao Y
        mov BX, SCREEN_HEIGHT
        call RANDOM_NUMBER

        mov [BX], AX
        add BX, 2
        
        ; Aumenta quantidade de inimigos
        inc WORD PTR [ENEMY_LIST_COUNT]
    
SPAWN_ENEMY_END:
    pop BX
    pop AX
    ret
endp