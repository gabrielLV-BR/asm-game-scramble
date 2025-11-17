; SCRAMBLE(R) - 2025
; Gabriel Lovato Vianna
; Arquitetura de Computadores
; UCS Caxias do Sul

.model SMALL
.stack 100H

.data
; ==========
; Constantes e estado global
; ==========
    CRET        EQU 0DH ; Char 'Enter'
    LFED        EQU 0AH ; Char 'New line'
    
    SCREEN_WIDTH EQU 320
    SCREEN_HEIGHT EQU 200
    SCREEN_SIZE EQU SCREEN_WIDTH*SCREEN_HEIGHT
        
    FRONT_BUFFER_LOC EQU 0A000H
    BACK_BUFFER_LOC EQU 02000H
        
    HELLO       DB 'HELLO, WORLD'
    HELLO_SZ    DW $ - HELLO
    
    PLAYER_X    DW ?
    PLAYER_Y    DW ?
    PLAYER_IDX  DW 0
    
    PLAYER_SPRITE   DW 3, 3 ; Largura, Altura
                    DB 3, 3, 3 ; Sprite 0
                    DB 3, 2, 2
                    DB 2, 2, 3
                    DB 9, 6, 6 ; Sprite 1
                    DB 5, 9, 6
                    DB 5, 9, 5


.code

; ==========
; Includes
; ==========
include io.inc
include draw.inc


; ==========
; Start
; ==========
start:   
    ; Configura modo de v?deo
    mov AX, 13H
    int 10H
    
    ; Estado inicial basico
    mov AX, 100
    push AX

    MAIN_LOOP:
        ; ==========
        ; PREPARACAO
        ; ==========

        ; Configura segmentos de dados
        mov AX, @data
        mov DS, AX
        
        ; Configura segmento do back buffer
        mov AX, BACK_BUFFER_LOC
        mov ES, AX
        
        ; Limpa a tela
        mov     AX, 0
        call    CLEAR_SCREEN
        
        ; ==========
        ; LOGICA DO JOGO
        ; ==========

        pop AX
        
        ; Printa o quadradinho
        mov CX, [PLAYER_IDX]

        mov     BX, 100
        mov     SI, offset PLAYER_SPRITE
        call    DRAW_SPRITE

        inc CX
        and CX, 1
        mov [PLAYER_IDX], CX
        
        inc AX
        push AX
        
        ; ==========
        ; RENDERIZACAO E TEMPORIZACAO
        ; ==========

        
        ; Copia o buffer de memoria auxiliar
        ; para a regiao mapeada para a tela
        cld

        xor DI, DI
        xor SI, SI
        
        mov AX, BACK_BUFFER_LOC
        mov DS, AX

        mov AX, FRONT_BUFFER_LOC
        mov ES, AX

        mov CX, SCREEN_SIZE
        rep movsb
        
        ; Dorme por 33 milisegundos
        ; para termos 30 FPS
        xor     AL, AL
        mov     AH, 86H     ; Funcao de espera
        mov     CX, 0       
        mov     DX, 80E8H   ; Lo bytes de 33 milisegundos em hexa
        int     15H
        
        jmp     MAIN_LOOP
    
    ; Retorno de sucesso
    mov     AH, 4CH
    int     21H

end start
; ==========