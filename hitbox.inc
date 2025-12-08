
; Verifica se existe colisao
; entre as hitboxes  A e B
; IN STACK[1] - Posicao X de A
; IN STACK[2] - Posicao Y de A
; IN STACK[3] - Largura de A
; IN STACK[4] - Altura de A

; IN STACK[5] - Posicao X de B
; IN STACK[6] - Posicao Y de B
; IN STACK[7] - Largura de B
; IN STACK[8] - Altura de B
; OUT ZF - Zero caso nao haja colisao,
;          Um caso haja

CHECK_COLLISION proc
    push AX
    push BX
    push BP
    mov  BP, SP

    ; X1 < X2 + W2
    mov  AX, [BP+4]       ; AX = X1
    mov  BX, [BP+12]      ; BX = X2
    add  BX, [BP+16]      ; BX = X2 + W2
    cmp  AX, BX
    jge  CHECK_COLLISION_NO_COLLISION

    ; X1 + W1 > X2
    mov  AX, [BP+4]       ; AX = X1
    add  AX, [BP+8]       ; AX = X1 + W1
    cmp  AX, [BP+12]
    jle  CHECK_COLLISION_NO_COLLISION

    ; Y1 < Y2 + H2
    mov  AX, [BP+6]       ; AX = Y1
    mov  BX, [BP+14]      ; BX = Y2
    add  BX, [BP+18]      ; BX = Y2 + H2
    cmp  AX, BX
    jge  CHECK_COLLISION_NO_COLLISION

    ; Y1 + H1 > Y2
    mov  AX, [BP+6]       ; AX = Y1
    add  AX, [BP+10]      ; AX = Y1 + H1
    cmp  AX, [BP+14] 
    jle  CHECK_COLLISION_NO_COLLISION

    mov  al, 1
    jmp  CHECK_COLLISION_END

CHECK_COLLISION_NO_COLLISION:
    mov  al, 0

CHECK_COLLISION_END:
    pop BP
    pop BX
    pop AX
    ret
endp
