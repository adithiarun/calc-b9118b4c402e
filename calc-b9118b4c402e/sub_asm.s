            AREA |.text|, CODE, READONLY //Instructs the assembler to assemble a new code; READONLY is the default
sub_asm     PROC //start of the procedure
            EXPORT sub_asm //EXPORT declares the file sub_asm, so it can be used by the linker when necessary
            SUB R0, R1 //Subtracts value in R1 from value in R0 and stores it in R0
            BX LR //Branch to link register
            ENDP //End of procedure
            ALIGN //Aligns the current location to a specified boundary by padding with 0s
            END //End of program