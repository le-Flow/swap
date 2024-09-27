; TODO: make pie

extern exit
extern printf

section .data
    sieve: times 1000 dd 0
    size: dd 1000
    format_int: db "%d ", 0x0

    str_primes: db "Primes up to %d:", 0xa, 0x0

section .text
    global main

main:
    push rbp
    mov rbp, rsp
    sub rsp, 8

    mov [rbp - 4], dword 2
    call init_array

.loop:
    mov edi, dword [rbp - 4]
    call eliminate_multiples
    call next_prime
    mov [rbp - 4], eax

    imul eax, eax
    cmp eax, dword [size]
    jl .loop

    call print_primes

    mov rsp, rbp
    pop rbp

    xor rdi, rdi
    call exit


init_array:
    xor rcx, rcx
    jmp .loopc
.loop:
    lea rdx, [sieve + ecx * 4]
    mov [rdx], dword 1
    inc ecx
.loopc:
    cmp  dword [size], ecx
    jne .loop

    mov [sieve], dword 0
    mov [sieve + 4], dword 0

    ret


eliminate_multiples:
    push rbp
    mov rbp, rsp

    mov ecx, edi
    add ecx, ecx

    jmp .loopc
.loop:
    mov [sieve + ecx * 4], dword 0

    add ecx, edi
.loopc:
    cmp ecx, dword [size]
    jl .loop

    mov rsp, rbp
    pop rbp

    ret


next_prime:
    push rbp
    mov rbp, rsp

    mov ecx, edi
    inc ecx
    jmp .loopc
.loop:
    mov edx, dword [sieve + ecx * 4]
    test edx, edx
    jz .zero
    jmp .done
.zero:
    inc ecx
.loopc:
    cmp ecx, dword [size]
    jb .loop
.done:
    mov eax, ecx

    mov rsp, rbp
    pop rbp
    ret


print_primes:
    push rbp
    mov rbp, rsp

    mov edi, str_primes
    mov esi, dword [size]
    xor eax, eax
    call printf

    xor ebx, ebx
    jmp .loopc
.loop:
    mov edx, dword [sieve + ebx * 4]
    test edx, edx
    jz .zero
    xor rax, rax
    mov rdi, format_int
    mov esi, ebx
    call printf
.zero:
    inc ebx
.loopc:
    cmp dword [size], ebx
    jne .loop

    mov rsp, rbp
    pop rbp
    ret
