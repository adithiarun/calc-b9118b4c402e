
            AREA |.text|, CODE, READONLY //Instructs the assembler to assemble a new code; READONLY is the default
add_asm     PROC //start of the procedure
            EXPORT add_asm //EXPORT declares the file add_asm, so it can be used by the linker when necessary
            ADD R0, R1 //Adds values stored in R1 and R0 and stores it in R0
            BX LR //Branch to link register
            ENDP //End of procedure
            ALIGN //Aligns the current location to a specified boundary by padding with 0s
            END //End of program