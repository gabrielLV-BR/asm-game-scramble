; SCRAMBLE(R) - 2025
; Gabriel Lovato Vianna
; Arquitetura de Computadores
; UCS Caxias do Sul

.model SMALL
.stack 100H

.data
; ==========
; Constantes
; ==========
    CRET        EQU 0DH ; Char 'Enter'
    LFED        EQU 0AH ; Char 'New line'
    
    SCREEN_WIDTH EQU 320
    SCREEN_HEIGHT EQU 200
    SCREEN_SIZE EQU SCREEN_WIDTH*SCREEN_HEIGHT
    
    FRONT_BUFFER_LOC EQU 0A000H
    BACK_BUFFER_LOC EQU 02000H
        
    RETRACE     EQU 03DAH
    
    KEY_DOWN    EQU 50H
    KEY_UP      EQU 48H
    KEY_LEFT    EQU 4BH
    KEY_RIGHT   EQU 4DH
    KEY_FIRE    EQU 2CH ; Z
    
    ENEMY_LIST_CAPACITY EQU 5
    ENEMY_SPAWN_TIMER_MAX EQU 5

    PLAYER_SPEED EQU 5
    
; ==========
; Estado global
; ==========
    HELLO_WORLD DB 'Hello, World$'

    PLAYER_X    DW 100
    PLAYER_Y    DW 100
    PLAYER_IDX  DW 0
    
    PLAYER_SPRITE   DW 3, 3 ; Largura, Altura
                    DB 3, 3, 3 ; Sprite 0
                    DB 3, 2, 2
                    DB 2, 2, 3
                    DB 9, 6, 6 ; Sprite 1
                    DB 5, 9, 6
                    DB 5, 9, 5
                    
    ENEMY_SPRITE    DW 5, 3 ; Largura, Altura
                    DB 1, 2, 3, 4, 5
                    DB 1, 2, 3, 4, 5
                    DB 1, 2, 3, 4, 5
    ; Estado dos inimigos
    ; DB Sprite index
    ; DW Posicao X
    ; DW Posicao Y
    ; Atualizar tamanho caso mudar!
    ENEMY_STRUCT_SIZE EQU 5
    ENEMY_LIST DB ENEMY_STRUCT_SIZE*ENEMY_LIST_CAPACITY DUP(?)
    ENEMY_LIST_COUNT DW 0
    ENEMY_SPAWN_TIMER DW 0
    
    RANDOM_SEED DW ?
.code

; ==========
; Includes
; ==========

include io.inc
include ui.inc
include draw.inc
include enemy.inc
include player.inc

; ==========
; Start
; ==========
start:   

    ; Configura modo de video
    mov AX, 13H
    int 10H

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
        
        call    UPDATE_PLAYER
        call    DRAW_PLAYER
        
        ; Logica de spawn de inimigos

        inc [ENEMY_SPAWN_TIMER]
        cmp [ENEMY_SPAWN_TIMER], ENEMY_SPAWN_TIMER_MAX
        
        jle ENEMY_SPAWN_TIMER_NOT_REACHED
            mov [ENEMY_SPAWN_TIMER], 0
            call SPAWN_ENEMY
        ENEMY_SPAWN_TIMER_NOT_REACHED:
            
        call UPDATE_ENEMIES

        ; ==========
        ; RENDERIZACAO E TEMPORIZACAO
        ; ==========
        
        ; Aguarda para o v-sync
     
        mov DX, RETRACE
        Vsync1:
            in      AL,DX
            test    AL,8
            jz      Vsync1
        Vsync2:
            in      AL,DX
            test    AL,8
            jnz     Vsync2   

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