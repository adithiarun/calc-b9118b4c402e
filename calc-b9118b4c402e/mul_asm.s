            AREA |.text|, CODE, READONLY //Instructs the assembler to assemble a new code; READONLY is the default
mul_asm     PROC //start of the procedure
            EXPORT mul_asm //EXPORT declares the file mul_asm, so it can be used by the linker when necessary
            MUL R0, R1 //Multiplies values stored in R1 and R0 and stores it in R0
            BX LR //Branch to link register
            ENDP //End of procedure
            ALIGN //Aligns the current location to a specified boundary by padding with 0s
            END //End of program