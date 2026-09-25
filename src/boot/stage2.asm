bits 16
org 0x8000

%ifndef KERNEL_SECTORS
  %define KERNEL_SECTORS 1
%endif

%ifndef KERNEL_START_SECTOR
  %define KERNEL_START_SECTOR 2
%endif

KERNEL_LOAD_SEGMENT equ 0x1000
KERNEL_LOAD_OFFSET  equ 0x0000

%define NEWLINE 0x0D, 0x0A

start:
  cli

  mov ax, 0x00
  mov ds, ax
  mov ss, ax
  mov sp, 0x7c00

  sti

  mov dl, [0x0500]
  mov [BootDrive], dl

  call setup_vbe
  call load_kernel
  call detect_memory

  cli

  lgdt [GDTDescriptor]

  mov eax, cr0
  or eax, 1
  mov cr0, eax

  jmp 0x08:protected_mode

setup_vbe:
  mov ax, 0x4F01
  mov cx, 0x144

  xor bx, bx
  mov es, bx

  mov di, 0x9000

  int 0x10

  cmp ax, 0x004F
  jne .error

  mov ax, [0x9000 + 0x00]
  test ax, 0x0080
  jz .error

  mov ax, [0x9000 + 0x12]
  cmp ax, 1024
  jne .error

  mov ax, [0x9000 + 0x14]
  cmp ax, 768
  jne .error

  mov al, [0x9000 + 0x19]
  cmp al, 32
  jne .error

  mov eax, [0x9000 + 0x28]
  mov [FrameAddress], eax

  mov ax, [0x9000 + 0x10]
  mov [FramePitch], ax

  mov ax, [0x9000 + 0x12]
  mov [FrameWidth], ax

  mov ax, [0x9000 + 0x14]
  mov [FrameHeight], ax

  mov ax, 0x4F02
  mov bx, 0x4144

  int 0x10

  cmp ax, 0x004F
  jne .error

  ret

  .error:
    mov si, VbeError
    call println

  .hang:
    cli
    hlt
    jmp .hang

get_vbe_modes:
  mov ax, 0x4F00
  mov di, 0x8000
  int 0x10

  cmp ax, 0x004F
  jne .error

  ret

  .error:
    cli
    hlt
    jmp .error

load_kernel:
  mov ax, KERNEL_LOAD_SEGMENT
  mov es, ax

  mov bx, KERNEL_LOAD_OFFSET

  mov word [DAP + 0], 0x0010
  mov word [DAP + 2], KERNEL_SECTORS
  mov word [DAP + 4], KERNEL_LOAD_OFFSET
  mov word [DAP + 6], KERNEL_LOAD_SEGMENT

  mov dword [DAP + 8], KERNEL_START_SECTOR
  mov dword [DAP + 12], 0

  mov si, DAP
  mov dl, [BootDrive]
  mov ah, 0x42

  int 0x13

  jc .error

  ret

  .error:
    mov si, DiskError
    call println

  .hang:
    cli
    hlt
    jmp .hang

MAX_MMAP_ENTRIES equ 40
MMAP_BUFFER equ 0x9200
MMAP_COUNT_ADDR equ 0x9600
MMAP_TOTAL_KB_ADDR equ 0x9604

detect_memory:
  pusha
  push es

  xor ax, ax
  mov es, ax

  mov dword [MMAP_COUNT_ADDR], 0
  mov dword [MMAP_TOTAL_KB_ADDR], 0

  mov di, MMAP_BUFFER
  xor ebx, ebx
  xor bp, bp

  .loop:
    cmp bp, MAX_MMAP_ENTRIES
    jae .done

    mov eax, 0xE820
    mov ecx, 24
    mov edx, 0x534D4150
    int 0x15

    jc .done
    cmp eax, 0x534D4150
    jne .done

    cmp ecx, 20
    jb .check_continue

    inc bp
    add di, 24

  .check_continue:
    cmp ebx, 0
    je .done
    jmp .loop

  .done:
    mov [MMAP_COUNT_ADDR], bp

    mov si, MMAP_BUFFER
    xor di, di
    xor eax, eax

  .sum_loop:
    cmp di, [MMAP_COUNT_ADDR]
    jae .sum_done

    mov edx, [si + 16] 
    cmp edx, 1
    jne .next_entry

    cmp dword [si + 4], 0
    jne .next_entry
    cmp dword [si + 12], 0
    jne .next_entry

    mov ebx, [si + 0]
    mov edx, [si + 8]

    cmp ebx, 0x100000
    jae .no_trim
    mov ecx, 0x100000
    sub ecx, ebx
    cmp edx, ecx
    jbe .zero_length
    sub edx, ecx
    jmp .no_trim

  .zero_length:
    xor edx, edx

  .no_trim:
    shr edx, 10
    add eax, edx

  .next_entry:
    add si, 24
    inc di
    jmp .sum_loop

  .sum_done:
    mov [MMAP_TOTAL_KB_ADDR], eax

  pop es
  popa
  ret

bits 32
protected_mode:
  mov ax, 0x10

  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  mov ss, ax

  mov eax, [FrameAddress]
  mov ebx, [FramePitch]
  mov ecx, [FrameWidth]
  mov edx, [FrameHeight]

  jmp 0x10000

bits 16
putc:
  mov ah, 0x0E
  mov bh, 0x00
  int 0x10

  ret

print:
  lodsb

  cmp al, 0
  je .done

  call putc

  jmp print

  .done:
    ret

println:
  call print

  mov si, NewLine
  call print

  ret

BootDrive:
  db 0

DAP:
  db 0x10
  db 0x00
  dw 0x0000
  dw 0x0000
  dw 0x0000
  dd 0x00000000
  dd 0x00000000

FrameAddress:
  dd 0
FramePitch:
  dd 0
FrameWidth:
  dd 0
FrameHeight:
  dd 0

NewLine:
  db NEWLINE, 0

VbeError:
  db "VBE error", 0

DiskError:
  db "There is an error loading the kernel", 0

GDTStart:
GDTNull:
  dq 0

GDTCode:
  dw 0xFFFF
  dw 0x0000
  db 0x00
  db 0b10011010
  db 0b11001111
  db 0x00

GDTData:
  dw 0xFFFF
  dw 0x0000
  db 0x00
  db 0b10010010
  db 0b11001111
  db 0x00

GDTEnd:
GDTDescriptor:
  dw GDTEnd - GDTStart - 1
  dd GDTStart
