normalizaNumero:
        addiu   $sp,$sp,-32
        sw      $fp,28($sp)
        move    $fp,$sp
        sw      $4,32($fp)
        sw      $5,36($fp)
        sw      $6,40($fp)
        sw      $7,44($fp)
        lw      $2,36($fp)
        nop
        andi    $2,$2,0x00ff
        andi    $2,$2,0x1
        andi    $2,$2,0x00ff
        andi    $2,$2,0x1
        lw      $4,20($fp)
        li      $3,-2                 # 0xfffffffffffffffe
        and     $3,$4,$3
        or      $2,$3,$2
        sw      $2,20($fp)
        sw      $0,8($fp)
        lw      $2,44($fp)
        nop
        beq     $2,$0,$L2
        nop

        li      $2,-2147483648                  # 0xffffffff80000000
        sw      $2,12($fp)
        li      $2,31                 # 0x1f
        sw      $2,16($fp)
        b       $L3
        nop

$L6:
        lw      $3,44($fp)
        lw      $2,12($fp)
        nop
        and     $2,$3,$2
        beq     $2,$0,$L4
        nop

        lw      $2,16($fp)
        nop
        sw      $2,8($fp)
        b       $L5
        nop

$L4:
        lw      $2,12($fp)
        nop
        sra     $2,$2,1
        sw      $2,12($fp)
        lw      $2,16($fp)
        nop
        addiu   $2,$2,-1
        sw      $2,16($fp)
$L3:
        lw      $2,16($fp)
        nop
        bgez    $2,$L6
        nop

$L5:
        lw      $2,8($fp)
        nop
        addiu   $2,$2,-23
        sw      $2,8($fp)
        lw      $2,8($fp)
        nop
        bgez    $2,$L7
        nop

        lw      $2,8($fp)
        nop
        bgez    $2,$L8
        nop

        subu    $2,$0,$2
$L8:
        move    $3,$2
        lw      $2,44($fp)
        nop
        sll     $2,$2,$3
        sw      $2,44($fp)
        b       $L9
        nop

$L7:
        lw      $3,44($fp)
        lw      $2,8($fp)
        nop
        sra     $2,$3,$2
        sw      $2,44($fp)
$L9:
        lw      $2,40($fp)
        nop
        andi    $3,$2,0x00ff
        lw      $2,8($fp)
        nop
        andi    $2,$2,0x00ff
        addu    $2,$3,$2
        andi    $2,$2,0x00ff
        addiu   $2,$2,127
        andi    $2,$2,0x00ff
        sll     $2,$2,1
        lw      $4,20($fp)
        li      $3,-511           # 0xfffffffffffffe01
        and     $3,$4,$3
        or      $2,$3,$2
        sw      $2,20($fp)
        b       $L10
        nop

$L2:
        lw      $3,20($fp)
        li      $2,-511           # 0xfffffffffffffe01
        and     $2,$3,$2
        sw      $2,20($fp)
$L10:
        lw      $3,44($fp)
        li      $2,8323072              # 0x7f0000
        ori     $2,$2,0xffff
        and     $2,$3,$2
        sll     $2,$2,9
        lw      $3,20($fp)
        nop
        andi    $3,$3,0x1ff
        or      $2,$3,$2
        sw      $2,20($fp)
        lw      $2,32($fp)
        lw      $3,20($fp)
        nop
        sw      $3,0($2)
        lw      $2,32($fp)
        move    $sp,$fp
        lw      $fp,28($sp)
        addiu   $sp,$sp,32
        j       $31
        nop

ajustaNegativo:
        addiu   $sp,$sp,-8
        sw      $fp,4($sp)
        move    $fp,$sp
        sw      $4,8($fp)
        sw      $5,12($fp)
        lw      $2,8($fp)
        nop
        lw      $2,0($2)
        nop
        subu    $3,$0,$2
        lw      $2,8($fp)
        nop
        sw      $3,0($2)
        nop
        move    $sp,$fp
        lw      $fp,4($sp)
        addiu   $sp,$sp,8
        j       $31
        nop

add:
        addiu   $sp,$sp,-64
        sw      $31,60($sp)
        sw      $fp,56($sp)
        move    $fp,$sp
        sw      $4,64($fp)
        sw      $5,68($fp)
        sw      $6,72($fp)
        lw      $2,68($fp)
        nop
        srl     $2,$2,1
        move    $3,$2
        li      $2,-1                 # 0xffffffffffffffff
        and     $2,$3,$2
        andi    $2,$2,0x00ff
        addiu   $2,$2,-127
        sw      $2,36($fp)
        lw      $2,72($fp)
        nop
        srl     $2,$2,1
        move    $3,$2
        li      $2,-1                 # 0xffffffffffffffff
        and     $2,$3,$2
        andi    $2,$2,0x00ff
        addiu   $2,$2,-127
        sw      $2,40($fp)
        lw      $2,68($fp)
        nop
        srl     $2,$2,9
        move    $3,$2
        li      $2,8388608              # 0x800000
        addu    $2,$3,$2
        sw      $2,44($fp)
        lw      $2,72($fp)
        nop
        srl     $2,$2,9
        move    $3,$2
        li      $2,8388608              # 0x800000
        addu    $2,$3,$2
        sw      $2,48($fp)
        lw      $2,68($fp)
        nop
        andi    $2,$2,0x1
        beq     $2,$0,$L14
        nop

        addiu   $3,$fp,36
        addiu   $2,$fp,44
        move    $5,$3
        move    $4,$2
        jal     ajustaNegativo
        nop

$L14:
        lw      $2,72($fp)
        nop
        andi    $2,$2,0x1
        beq     $2,$0,$L15
        nop

        addiu   $3,$fp,40
        addiu   $2,$fp,48
        move    $5,$3
        move    $4,$2
        jal     ajustaNegativo
        nop

$L15:
        lw      $3,36($fp)
        lw      $2,40($fp)
        nop
        beq     $3,$2,$L16
        nop

        lw      $3,36($fp)
        lw      $2,40($fp)
        nop
        slt     $2,$2,$3
        beq     $2,$0,$L17
        nop

        lw      $3,36($fp)
        lw      $2,40($fp)
        nop
        subu    $2,$3,$2
        sw      $2,32($fp)
        lw      $2,36($fp)
        nop
        sw      $2,40($fp)
        lw      $3,48($fp)
        lw      $2,32($fp)
        nop
        sra     $2,$3,$2
        sw      $2,48($fp)
$L17:
        lw      $3,36($fp)
        lw      $2,40($fp)
        nop
        slt     $2,$3,$2
        beq     $2,$0,$L16
        nop

        lw      $3,40($fp)
        lw      $2,36($fp)
        nop
        subu    $2,$3,$2
        sw      $2,32($fp)
        lw      $2,40($fp)
        nop
        sw      $2,36($fp)
        lw      $3,44($fp)
        lw      $2,32($fp)
        nop
        sra     $2,$3,$2
        sw      $2,44($fp)
$L16:
        lw      $3,44($fp)
        lw      $2,48($fp)
        nop
        addu    $2,$3,$2
        sw      $2,24($fp)
        sw      $0,28($fp)
        lw      $2,24($fp)
        nop
        bgez    $2,$L18
        nop

        lw      $2,24($fp)
        nop
        nor     $2,$0,$2
        sw      $2,24($fp)
        li      $2,1                        # 0x1
        sw      $2,28($fp)
$L18:
        lw      $3,36($fp)
        lw      $2,64($fp)
        lw      $7,24($fp)
        move    $6,$3
        lw      $5,28($fp)
        move    $4,$2
        jal     normalizaNumero
        nop

        lw      $2,64($fp)
        move    $sp,$fp
        lw      $31,60($sp)
        lw      $fp,56($sp)
        addiu   $sp,$sp,64
        j       $31
        nop

main:
        addiu   $sp,$sp,-48
        sw      $31,44($sp)
        sw      $fp,40($sp)
        move    $fp,$sp
        lui     $2,%hi($LC0)
        lwc1    $f0,%lo($LC0)($2)
        nop
        swc1    $f0,24($fp)
        lui     $2,%hi($LC1)
        lwc1    $f0,%lo($LC1)($2)
        nop
        swc1    $f0,28($fp)
        addiu   $2,$fp,32
        lw      $6,28($fp)
        lw      $5,24($fp)
        move    $4,$2
        jal     add
        nop

        nop
        move    $sp,$fp
        lw      $31,44($sp)
        lw      $fp,40($sp)
        addiu   $sp,$sp,48
        j       $31
        nop

$LC0:
        .word   1065353216
$LC1:
        .word   1073741824