#include "mbed.h" //includes library mbed.h
extern "C" int add_asm(int a, int b); //declaration of function used for addition. Extern keyword makes it visible to the entire program.
extern "C" int sub_asm(int a, int b); //declaration of function used for subtraction.
extern "C" int mul_asm(int a, int b); //declaration of function used for multiplication.
extern "C" int div_asm(int a, int b); //declaration of function used for division.
DigitalIn columns[3]= {PB_6,PB_7,PD_0}; //Initializes input pin columns.
DigitalOut row[4]= {PA_5,PA_1,PA_2,PA_3}; //Initializes output pin rows.
int numpad[4][3] = {
    {1,2,3},
    {4,5,6},
    {7,8,9},
    {-1,0,-2},
}; //2 D array representing keypad inputs. Integer array is created to make calculation easier. -1 represents '*' and -2 represents '#'
//main function:
int main()
{
    int detected = 0; //holds the intermediate values of each operand. Once an operand is fully entered(ie # is pressed), it is stored in the array op[2].
    int op[2] = {0,0}; //stores each of the operands once '#' is pressed.
    int inc = 0; //counts the number of operands entered. If inc = 2, code looks for operation to be performed.
    int read; //holds keypad inputs while the code is reading operands.
    int operation = -1; //variable that holds keypad code for the operation (1 – add, 2 – subtract, 3 – multiply, 4 – divide)
    int y = 0; //changes values so that the program does not repeatedly execute 'if statements' on lines 29 and 33.

    columns[0].mode(PullUp); //Pull up resistor on column 0
    columns[1].mode(PullUp); //Pull up resistor on column 1
    columns[2].mode(PullUp); //Pull up resistor on column 2
//while(1) makes the microcontroller repeatedly execute the code inside it
    while(1) {
        if (inc == 0 && y == 0) { //if inc = 0 (0 operands have been entered) and y = 0 ('Enter the first number:' has not been printed on terminal)
            y = 1; //y is incremented to 1 so that 'Enter the first number:' is not printed again
            printf("Enter the first number:\n"); //print statement prompting the user to enter the 1st operand
        }
        if (inc == 1 && y == 1)  { //if inc = 1 (1 operand has been entered) and y = 1 ('Enter the second number:' has not been printed on terminal)
            y = 2; //y is incremented to 2 so that this if statement is not repeated.
            printf("Enter the second number:\n"); //prompts user to enter the 2nd operand
        }
        for(int i=0; i<4; i++) { //loops through the rows (adds 1 to i until i reaches 4, which is when the loop terminates)
            row[0]=1; //Initializes first row
            row[1]=1; //Initializes Second row
            row[2]=1; //Initializes third row
            row[3]=1; //Initializes fourth row
            row[i]=0; //Holds the last value of i
            wait(0.01); //delay of 0.01 seconds
            for(int j=0; j<3; j++)  {  //loops through columns (adds 1 to j until j reaches 3)
                if(columns[j] == 0 && numpad[i][j] == -1)   { //if statement for column[j]=0 and numpad[i][j]=-1 ('*' is pressed)
                    inc = 0; //pressing * on the keypad resets the calculator and makes it go back to line 29 prompting user to enter the 1st number.
                    y = 0; //inc = 0 and y = 0 are the conditions needed to enter the if statement on line 29
                }
                if(columns[j]==0 && y!=3)   {//if statement for column[j] = 0 and y!=3 (if y != 3, it means 2 operands have not yet been entered)
                    read=numpad[i][j]; //read holds integer at row i and column j from 2x2 array based on keypad press
                    if (read == -2) { //if the key pressed is -2, it means an operand has been entered
                        op[inc] = detected; //operand is stored in array op[2] at location inc
                        printf("%d\n",op[inc]); //prints the operand
                        inc++; //increments location of operand array
                        detected = 0; //intermediate value of operand is reset to 0
                    }
                    if (read >= 0)  { //if the keypad input is not * or #
                        detected = detected*10 + read; //intermediate value of operand before it is stored in array op[2]
                    }
                    wait(0.005); //delay of 0.005s
                    while(columns[j]==0); //acts as a wait
                }
                if(columns[j] == 0 && y == 3)  { //if y = 3 (calculator has received 2 operands) and a key is pressed, the following lines are ezecuted
                    operation = numpad[i][j]; //'operation' variable holds operator value read by keypad
                    if(operation>4 || operation<=0)  { //if key pressed is not 1,2,3, or 4
                        printf("invalid char\n"); //prints 'invalid character'
                        y = 3; //makes y = 3 so that if statement on line 63 can be re-entered to accept a valid operator
                    } else if(operation==1)   { //if operator is 1, addition is performed
                        printf("%d + %d = %d\n", op[0], op[1], add_asm(op[0],op[1])); //prints addition result
                        y = 0; //when y is reset to 0, if statement from line 29 can be executed again ('Enter the first number' is output on terminal)
                    } else if(operation == 2) { //if operator is 2, subtraction is performed
                        printf("%d - %d = %d\n", op[0], op[1], sub_asm(op[0],op[1])); //prints subtraction result
                        y = 0; //when y is reset to 0, if statement from line 29 can be executed again ('Enter the first number' is output on terminal)
                    } else if(operation == 3) { //if operator is 3, multiplication is performed
                        printf("%d * %d = %d\n", op[0], op[1], mul_asm(op[0],op[1])); //prints multiplication result
                        y = 0; //when y is reset to 0, if statement from line 29 can be executed again ('Enter the first number' is output on terminal)
                    } else    { //if operator is 4, division is performed
                        printf("%d / %d = %d\n", op[0], op[1],div_asm(op[0],op[1])); //prints division result
                        y = 0; //when y is reset to 0, if statement from line 29 can be executed again ('Enter the first number' is output on terminal)
                    }
                    wait(0.005); //waits 0.005s
                    while(columns[j]==0); //acts as a wait
                }
            }
        }
        if(inc == 2) { //if 2 operands have been stored into array op[2]
            detected = 0; //variable that stores intermediate values of the operand is reset to 0
            printf("The numbers are %d and %d\n",op[0],op[1]); //prints the 2 operands.
            printf("Press '*' to reset or Select 1:Addition   2:Subtraction   3:Multiplication    4:Division\n:"); //prints this statement on terminal
            y = 3; //changes value of y to 3 so that program can enter if statement on line 63 so that operator is accepted and result is output
            inc = 0; //inc is reset to 0
        }
    }
}