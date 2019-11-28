*Es wird ja fleißig gearbeitet und viel programmiert, aber es müsste mal wieder einer einen gescheiten Gedanken haben. - abgeändert, ursprünglich von Rudolf Virchow*

# Koopman TOY CPU Interpreter 

This is a CPU interpreter, based on the specification of Phil Koopmans paper: [Microcoded Versus Hard-wired Control](https://users.ece.cmu.edu/~koopman/misc/byte87a.pdf).<br>
For more details, have a look at /doc or press `toy_cpu -h` (for help) or `toy_cpu -a` (for cpu architecture overview)

<table><tr>
    <td> <img alt="Image of main window on linux" width="100%" src="doc/program_flow.png"> </td>
    <td> <img alt="Image of main window on Windows" width="100%" src="doc/architectural_overview.png"> </td>
</tr></table>


##  Build

The project can be built by using `make`.<br>
You do not have to pay attention to external dependencies. This is standard C99 code.

## Usage 

Transfer the RAM content to the machine via a text file.<br>
The program call is: `toy_cpu` SOURCE.toy<br>
The following is the specification for a 16 BIT machine word. With it, you can create the RAM content.<br>
(Do not forget: this is a pure John von Neumann architecture, data and program are in the same memory)<br>


<pre>
OP_Code 0 (0000b):	   STORE<12 BIT ADDRESS>
OP_Code 1 (0001b):	   LOAD	<12 BIT ADDRESS>
OP_Code 2 (0010b):	   JMPZ	<12 BIT ADDRESS>
OP_Code 3 (0011b):	   ADD	<12 BIT ADDRESS>
OP_Code 4 (0100b):	   SUB	<12 BIT ADDRESS>
OP_Code 5 (0101b):	   OR	<12 BIT ADDRESS>
OP_Code 6 (0110b):	   AND	<12 BIT ADDRESS>
OP_Code 7 (0111b):	   XOR	<12 BIT ADDRESS>
OP_Code 8 (1000b):	   NOT	<12 BIT undefined>
OP_Code 9 (1001b):	   INC	<12 BIT undefined>
OP_Code 10 (1010b):	   DEC	<12 BIT undefined>
OP_Code 11 (1011b):	   ZERO	<12 BIT undefined>
OP_Code 12 (1100b):	   NOP	<12 BIT undefined>
OP_Code 13 (1101b):	   NOP	<12 BIT undefined>
OP_Code 14 (1110b):	   NOP	<12 BIT undefined>
OP_Code 15 (1111b):	   NOP	<12 BIT undefined>



BIT |15 14 13 12|11 10 9 8 7 6 5 4 3 2 1 0|
	---------------------------------------
	|  OP-CODE  |		ADDRESS	          |
	---------------------------------------
</pre>

This machine has the following registers:

* 16 BIT Instruction Register (4 BIT OP, 12 BIT Addr)
* 16 BIT Accumulator
* 12 BIT Program Counter

Example: 0001000000001010 at RAM position 0 <br>
0001 means: LOAD the content of ADDRESS 000000001010 into the ACCU


## Licence

This program by Michael Krause is licenced under the terms of the [GPLv3](https://www.gnu.org/licenses/gpl-3.0.de.html).

