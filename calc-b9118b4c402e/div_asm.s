            AREA |.text|, CODE, READONLY //Instructs the assembler to assemble a new code; READONLY is the default
div_asm     PROC //start of the procedure
            EXPORT div_asm //EXPORT declares the file div_asm, so it can be used by the linker when necessary
            UDIV R0, R1 //divides value in R0 by value in R1
            BX LR //Branch to link register
            ENDP //End of procedure
            ALIGN //Aligns the current location to a specified boundary by padding with 0s
            END //End of program