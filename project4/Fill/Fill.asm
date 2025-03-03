
// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, 
// the screen should be cleared.

//// Replace this comment with your code.

//define screen size
@8192
D=A
@screen_size
M=D
//listen for keys to blacken a white screen
(LISTENforBLACK)
@KBD
D=M
@BLACKEN
D;JNE
@LISTENforBLACK
0;JMP

//listen for keys to whiten a black screen
(LISTENforWHITE)
@KBD
D=M
@WHITEN
D;JEQ
@LISTENforWHITE
0;JMP

(BLACKEN)
@i
M=0
(LOOPBLACK)
//condition
@i
D=M
@screen_size
D=M-D
@STOPBLACK
D;JLE
//operation
@SCREEN
D=A
@i
A=D+M
M=-1
//increment
@i
M=M+1
@LOOPBLACK
0;JMP
(STOPBLACK)
//back to keyboard
@LISTENforWHITE
0;JMP

(WHITEN)
@i
M=0
(LOOPWHITE)
//condition
@i
D=M
@screen_size
D=M-D
@STOPWHITE
D;JLE
//operation
@SCREEN
D=A
@i
A=D+M
M=0
//increment
@i
M=M+1
@LOOPWHITE
0;JMP
(STOPWHITE)
//back to keyboard
@LISTENforBLACK
0;JMP
