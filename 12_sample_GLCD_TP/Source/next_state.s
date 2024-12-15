                AREA    next_state_area, CODE, READONLY
; Reset Handler

Next_state   	PROC
                EXPORT  Next_state 
				PUSH{R4-R7,LR}
				MOV R4,R0 ;CURRENTSTATE
				MOV R5,R1 ;TAPS_VAR
				MOV R6,#0
				MOV R7,R4 ;COPY OF CURRENTSTATE TO SHIFT
				;AND R7,R7,R5 ;COPY_CURRENTSTATE_MASKED
				MOV R12,#0
				
cycle			
				AND R8, R7,#0x00000001 ;selects the lsb
				AND R9,	R5,#0X00000001 
				CMP R9,#1
				IT EQ
				EOREQ r12,r8,r12
				
				
			
				
				LSR R7,#1
				LSR R5,#1
				
				
				ADD R6,#1
				CMP R6,#7
				BNE cycle
				
				AND R3, R4,#0x00000001 ;OUTPUT BIT
				LSR R4,R4,#1
				LSL R12,R12,#7
				ORR R4,R4,R12
				
				;STR R3,[R2]
				MOV R0,R4
				POP{R4-R7,LR}
				;SAVE IN R0 THE OUTPUT BIT
				BX LR
                ENDP
				END	