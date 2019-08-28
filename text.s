.name       "Batman"
.comment    "This city needs me"

#loop:
#        sti r1, %:live, %1    # <-- На эту операцию указывает метка loop
#live:
#        live %0               # <-- На эту операцию указывает метка live
#        ld %0, r2             # <-- А на эту операцию никакая метка не указывает
#       zjmp %1
	add r1, r1, r0
	add r0, r0, r2
	st r0, 20
	zjmp %100
#	add r2, r3, r1
#	add r2, r3, r1
#	add r2, r3, r1
#	add r2, r3, r1
#	add r2, r3, r1
#	add r2, r3, r1
#	add r2, r3, r1
#	add r2, r3, r1
#	zjmp %5
#	ld r1, :abc
#	abc:
#
