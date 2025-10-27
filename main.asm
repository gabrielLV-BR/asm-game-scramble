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
    
    HELLO       DB 'HELLO, WORLD'
    HELLO_SZ    DW $ - HELLO
; ==========
.code

; Includes
; ==========
include io.inc
; ==========

; Main function
; ==========
start:   
    ; Setup segment registers
    mov AX, @data
    mov DS, AX
    mov ES, AX
    
    ; Setup video mode

    ; Loads HELLO into DI
    mov DI, offset HELLO
    mov CX, HELLO_SZ
    
    ; Print 'HELLO, WORLD'
    call PRINT_STRING

    ; Successfull return code
    mov AH, 4CH
    int 21H

end start
; ==========