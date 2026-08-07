section .text
global dot_product_asm
dot_product_asm:
    subsd xmm0, xmm0            ; xmm0 (sum) = 0.0
.loop:
    movsd  xmm1, qword [rsi]    ; xmm1 = A[i]
    movsd xmm2, qword [rdx]     ; xmm2 = B[i]
    mulsd xmm1, xmm2            ; xmm1 = A[i] * B[i]
    addsd xmm0, xmm1            ; sum += A[i] * B[i]
    add rsi, 8                  ; A++
    add rdx, 8                  ; B++
    dec edi                     ; n--
    jnz .loop                   ; repeat while n != 0
.done:
    movsd qword [rcx], xmm0     ; *sdot = sum
    ret
