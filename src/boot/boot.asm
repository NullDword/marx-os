bits 16
org 0x7c00

STAGE2_SEGMENT equ 0x0800
STAGE2_SECTOR equ 2
%ifndef STAGE2_SECTORS
  %define STAGE2_SECTORS 1
%endif

start:
  cli

  xor ax, ax
  mov ds, ax
  mov ss, ax
  mov sp, 0x7c00

  mov [boot_drive], dl
  mov [0x0500], dl

  mov ax, STAGE2_SEGMENT
  mov es, ax
  xor bx, bx

  mov ah, 0x02
  mov al, STAGE2_SECTORS
  mov ch, 0
  mov cl, STAGE2_SECTOR
  mov dh, 0
  mov dl, [boot_drive]

  int 0x13
  jc hang

  jmp STAGE2_SEGMENT:0

hang:
  cli
  hlt
  jmp hang

boot_drive:
  db 0

times 510 - ($ - $$) db 0
dw 0xAA55
