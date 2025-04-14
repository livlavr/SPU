    PUSH 2
    PUSH 0
    POP [0]
    POP [1]

BEGIN:
    PUSH [0]
    PUSH -15
    ADD
    PUSH [1]
    PUSH -15
    ADD
    POP AX
    POP BX

    CALL LEFT_SIDE

    CALL RIGHT_SIDE

    JAE PRINT
END_OF_PRINT:

    PUSH [0]
    PUSH 30
    MUL
    PUSH [1]
    ADD
    PUSH 900

    JAE END

    PUSH [1]
    PUSH 30

    JNE SMALL_STEP

    PUSH [1]
    PUSH 30

    JE BIG_STEP

HLT

RIGHT_SIDE:
    PUSH [0]
    PUSH -15
    ADD
    POP BX
    PUSH [1]
    PUSH -15
    ADD
    POP AX

    PUSH AX
    PUSH AX
    MUL

    PUSH BX
    PUSH BX
    PUSH BX
    MUL
    MUL

    MUL
RETURN

LEFT_SIDE:
    PUSH AX
    CALL SQUARE
    PUSH 3
    DIV
    POP AX

    PUSH BX
    CALL SQUARE
    PUSH 3
    DIV
    POP BX

    PUSH AX
    PUSH BX
    PUSH -20
    ADD
    ADD
    CALL CUBIC
RETURN

SQUARE:
    POP DX
    PUSH DX
    PUSH DX
    MUL
RETURN

CUBIC:
    POP DX
    PUSH DX
    PUSH DX
    PUSH DX
    MUL
    MUL
RETURN

PRINT:
    PUSH [0]
    PUSH 30
    MUL

    PUSH [1]
    ADD
    POP CX

    PUSH 35
    POP [CX]
JMP END_OF_PRINT

BIG_STEP:
    PUSH 0
    POP [1]

    PUSH [0]
    PUSH 1
    ADD
    POP [0]
JMP BEGIN

SMALL_STEP:
    PUSH 1
    PUSH [1]
    ADD
    POP [1]
JMP BEGIN

END:
    DRAW
HLT
