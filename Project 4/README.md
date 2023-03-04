This project was about making a program that simulated logic gates and circuits. The program would take a text file that describes inputs to the circuits, the output,
and whatever gates that would occur within the circuit. the program would calculate the result of the circuit with every possible combination of inputs to the circuit.
The inputs of the circuits only take values 1 and 0. 1 represents "true" while 0 is "false".
Here's an example of what an input would look like:

INPUT 3 a b c
OUTPUT 1 d
AND a b   x
AND c x   d

The result would be:

0 0 0 | 0
0 0 1 | 0
0 1 0 | 0
0 1 1 | 0
1 0 0 | 0
1 0 1 | 0
1 1 0 | 0
1 1 1 | 1

The program should take any number of inputs and outputs. The gates that can be used are AND, OR, NOT, NAND (NOT AND), NOR (NOT OR), XOR, DECODER, and MULTIPLEXER.
