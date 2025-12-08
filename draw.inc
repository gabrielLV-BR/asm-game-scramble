; Limpa a tela com uma cor solida
; IN AX - A cor para limpar a tela
CLEAR_SCREEN proc
    push CX
    push DX

    CLD             ; Limpa DF (direction flag)
                    ; Para operacoes de string, DF = 0
                    ; significa que ele sera incrementado
                    ; a cada loop
    
    ; Zera DI para limpar a tela desde o in?cio
    ; xor DI, DI

    ; Limpa tela deixando por??o vazia para textos
    mov DI, 3200
    mov CX, SCREEN_SIZE ; Carrega CX com o tamanho da tela
    
    ; Subtrai
    sub CX, DI
    
    rep STOSB           ; Roda STOSB ([ES:DI] <- AX; DI++)
                        ; enquanto CX > 0
    
    pop DX
    pop CX
    
    ret
endp

; Desenha um sprite na tela
; IN AX - A posicao X do sprite na tela
; IN BX - A posicao Y do sprite na tela
; IN CX - O indice do sprite para ser desenhado
; IN SI - O endereco inicial do sprite
DRAW_SPRITE proc
    push AX
    push BX
    push CX
    push DX
    push SI

    ; Verificamos se podemos desenhar o sprite

    cmp AX, SCREEN_WIDTH
    jge DRAW_SPRITE_END ; Estamos a direita da tela
    
    cmp BX, SCREEN_HEIGHT
    jge DRAW_SPRITE_END ; Estamos abaixo da tela
    
    ; Transformamos a posicao X Y
    ; na posicao real de memoria
    call TO_MEMORY_LOCATION
    
    ; Calculamos os pontos extremos
    push AX
    push BX
    
    add AX, [SI]
    add SI, 2
    add BX, [SI]
    sub SI, 2 ; Retornamos o SI para o inicio

    cmp AX, 0
    jle DRAW_SPRITE_END ; Estamos a esquerda
    
    cmp BX, 0
    jle DRAW_SPRITE_END ; Estamos acima
    
    pop BX
    pop AX
    
    ; Movemos para AX a largura
    ; e para BX a altura
    mov AX, [SI]
    add SI, 2
    mov BX, [SI]
    add SI, 2
    
    ; Calculamos a posicao de memoria do
    ; sprite com base no indice informado
    push AX
    
    add AX, BX
    mul CX
    add SI, AX

    pop AX

    ; Limpamos a flag de direcao
    cld
    
    ; Iteramos as linhas e desenhamos coluna a coluna
    DRAW_SPRITE_LINE_LOOP:
        ; Copiamos toda as colunas da linha deste
        ; sprite na memoria
        mov CX, AX
        rep movsb

        ; Avancamos o equivalente a uma linha na
        ; area de memoria e retrocedemos as colunas
        add DI, SCREEN_WIDTH
        sub DI, AX

        ; Reduzimos um da altura e realizamos
        ; o laco de novo caso ainda sobrem
        ; linhas
        dec BX
        jnz DRAW_SPRITE_LINE_LOOP

DRAW_SPRITE_END:
    pop SI
    pop DX
    pop CX
    pop BX
    pop AX

    ret
endp

; Calcula a posicao de memoria de uma dada coordenada
; IN AX - Coordenada X
; IN BX - Coordenada Y
; OUT DI - Posicao de memoria resultante
TO_MEMORY_LOCATION proc
    push AX
    push BX
    push DX

    mov DI, AX

    mov AX, BX
    mov BX, SCREEN_WIDTH
    mul BX

    add DI, AX
    
    pop DX
    pop BX
    pop AX
    ret
endp