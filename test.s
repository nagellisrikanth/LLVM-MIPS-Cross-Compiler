__entry:
	addi $29, $29, -4
	move $32, $29
	addi $29, $29, -4
	move $33, $29
L0:
	lw $34, 0($32)
	lw $35, 0($33)
	slt $36, $35, $34
	beq $36, $0, L2
	j L1
L1:
	li $37, 10
	sw $37, 0($32)
	j L3
L2:
	li $38, 20
	sw $38, 0($33)
	j L3
L3:
	j __exit
__exit:
	addi $29, $29, 4
	addi $29, $29, 4
	jr $31

