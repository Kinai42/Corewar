.name           "42"
.comment        "COMMENT"

live	%42			#1
ld	%64,r1			#2
ld	%70,r13			#2
ld %42, r2			#2
st r2, r5			#3
add r1,r2,r3		#4
sub r1,r2,r4		#5
and 1, 1, r6		#6
or 2,1, r7			#7
xor 2, 1, r8		#8
ldi %4, r1,r9		#10
sti r1, %1, r2		#11
##fork %100			#12
lld %0, r11			#13
lldi %0,r4,r12		#14<<
##lfork %1			#15
aff r1				#16
ld	%55,r1
		st	r1,r2
		ld	%0,r15
	#	fork	%1
		zjmp	%32
