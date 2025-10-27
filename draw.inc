; Clears the screen with a solid color
; IN AX - Color to clean the screen with
CLEAR_SCREEN proc
    push CX
    push DX

    CLD             ; Clear DF (direction flag)
                    ; For string operations, DF = 0
                    ; means DI will be incremented each loop
    xor DI, DI
    mov CX, SCREEN_SIZE ; Load up CX with screen size
    rep STOSB           ; Repeatedly run STOSB ([ES:DI] <- AX; DI++)
                        ; while CX > 0
    
    pop DX
    pop CX
    ret
endp