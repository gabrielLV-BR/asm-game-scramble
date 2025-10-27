; SCRAMBLE(R) - 2025
; Gabriel Lovato Vianna
; Arquitetura de Computadores
; UCS Caxias do Sul

.model SMALL
.stack 100H

.data
; Constants and global variables
; ==========
    CRET        EQU 0DH ; Char 'Enter'
    LFED        EQU 0AH ; Char 'New line'
    
    SCREEN_SIZE EQU 64000
    
    HELLO       DB 'HELLO, WORLD'
    HELLO_SZ    DW $ - HELLO
; ==========
.code

; Includes
; ==========
include io.inc
include draw.inc
; ==========

; Main function
; ==========
start:   
    ; Setup segment registers
    mov AX, @data
    mov DS, AX
    
    ; Setup video mode
    mov AX, 0A000H
    mov ES, AX          ; The ES segment will be aligned with
                        ; the memory region mapped to the screen
    
    mov AX, 13H
    int 10H
    
    ; Draw to screen
    
    mov BX, 1
    
    MAIN_LOOP:
        mov     AX, BX
        call    CLEAR_SCREEN
       
        ; Changes color
        inc     BX
        and     BX, 7
        
        ; Sleeps for 33 milliseconds
        ; for 30FPS frame time
        xor     AL, AL
        mov     AH, 86H     ; Elapsed time wait function
        mov     CX, 0       
        mov     DX, 80E8H   ; Low bytes of 33 mili in hex
        int     15H

        jmp     MAIN_LOOP
    
    ; Successfull return code
    mov     AH, 4CH
    int     21H

end start
; ==========