@mult
M=0
@i
M=0
@R2
M=0
//loop and condition
(LOOP)
@i
D=M
@R1
D=D-M
@STOP
D;JGE
//operaton
@R0
D=M
@mult
M=D+M
//increment i
@i
M=M+1
@LOOP
0;JMP
(STOP)
@mult
D=M
@R2
M=D
(END)
@END
0;JMP
