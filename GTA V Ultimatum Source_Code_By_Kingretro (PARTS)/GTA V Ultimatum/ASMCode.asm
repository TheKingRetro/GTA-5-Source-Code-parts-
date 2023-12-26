EXTERNDEF RA_Damage:QWORD
EXTERNDEF ASMLocalPlayer:QWORD

.code
DisableDamage proc
	cmp rsi, ASMLocalPlayer
	jne OCode
	mov r15, RA_Damage
	jmp r15
DisableDamage endp

OCode proc
	addss xmm6, dword ptr[rsi + 280h]
	mov   ecx, 4
	movss dword ptr[rsi + 280h], xmm6
	mov	  r15, RA_Damage
	jmp   r15
OCode endp
end
