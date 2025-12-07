; Desenha a interface do usuario
DRAW_UI proc
 
    ; Posiciona o texto
    mov dl, 0 ; Column
    mov dh, 0 ; Row
    mov bx, 0 ; Page number, 0 for graphics modes
    mov ah, 2h
    int 10h
    ;call SET_CURSOR_POSITION

    ; IN DI - Address of string
    ; IN CX - String length
    mov DX, offset HELLO_WORLD
    mov AH, 09H
    int 21H
    
    ret
endp