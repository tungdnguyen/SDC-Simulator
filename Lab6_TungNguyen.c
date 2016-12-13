
// *** Tung D. Nguyen Section 01***

// CS 350, Fall 2016
// Lab 6: SDC Simulator, part 1
//
// Illinois Institute of Technology, (c) 2016, James Sasaki

#include <stdio.h>
#include <stdlib.h>	  // For error exit()

// CPU Declarations -- a CPU is a structure with fields for the
// different parts of the CPU.
//
	typedef short int Word;		 // type that represents a word of SDC memory
	typedef unsigned char Address;	 // type that represents an SDC address

	#define MEMLEN 100
	#define NREG 10

	struct CPU {
		Word mem[MEMLEN];
		Word reg[NREG];	     // Note: "register" is a reserved word
		Address pc;	     // Program Counter
		int running;	     // running = 1 iff CPU is executing instructions
		Word ir;	     // Instruction Register
		int instr_sign;	     //	  sign of instruction
		int opcode;	     //	  opcode field
		int reg_R;	     //	  register field
		int addr_MM;	     //	  memory field
	};
	typedef struct CPU CPU;


// Prototypes [note the functions are also declared in this order]
//
	// *** STUB *** Lab 5 items omitted ....
    int main(int argc, char *argv[]);
    void initialize_control_unit(CPU *cpu);
    void initialize_memory(int argc, char *argv[], CPU *cpu);
    FILE *get_datafile(int argc, char *argv[]);

	void dump_control_unit(CPU *cpu);
    void dump_memory(CPU *cpu);
    void print_instr(int instr);
   	void dump_registers(CPU *cpu);


	int read_execute_command(CPU *cpu);
	int execute_command(char cmd_char, CPU *cpu);
	void help_message(void);
	void many_instruction_cycles(int nbr_cycles, CPU *cpu);
	void one_instruction_cycle(CPU *cpu);

	void exec_HLT(CPU *cpu);
	// *** STUB ***

// Main program: Initialize the cpu, and read the initial memory values.
// Then run the command loop to let the user execute the program.
//
int main(int argc, char *argv[]) {
	printf("SDC Simulator pt 2 *** STUB ***\n");
	CPU cpu_value, *cpu = &cpu_value;

	// *** STUB *** Lab 5 items omitted (initialize CPU and memory) ....

	printf("Student: Tung D Nguyen. Lab Section: 01\n\n\n\n");
    initialize_control_unit(cpu);
    dump_control_unit(cpu);
    initialize_memory(argc, argv, cpu);
    dump_memory(cpu);

	// Run the command loop
	//
	char *prompt = "> ";
	printf("\nBeginning execution; type h for help\n%s", prompt);

	int done = read_execute_command(cpu);
	while (!done) {
		printf(">");
		printf("%s\n", prompt);
		done = read_execute_command(cpu);
	}
	return 0;
}


// *** STUB ***	 Rest of Lab 5 items omitted
// (initialize_control_unit, ..., print_instr)
void initialize_control_unit(CPU *cpu) {

        // *** STUB ***
		cpu -> instr_sign=1;
		cpu -> pc=0;
		cpu -> ir=0;
		cpu -> opcode=0;
        cpu -> reg_R=0;
        cpu -> addr_MM=0;
        cpu -> running=1;

        //initializing reg 
        for(int i = 0;i<= NREG;i++)
        {
        	cpu -> reg[i]=0;
        }
        printf("\n");
}

// Read and dump initial values for memory
//
void initialize_memory(int argc, char *argv[], CPU *cpu) {
        FILE *datafile = get_datafile(argc, argv);

// Buffer to read next line of text into
#define DATA_BUFFER_LEN 256
        char buffer[DATA_BUFFER_LEN];

        // Will read the next line (words_read = 1 if it started
        // with a memory value). Will set memory location loc to
        // value_read
        //
        int value_read, words_read, loc = 0, done = 0;

        char *read_success;    // NULL if reading in a line fails.

        read_success = fgets(buffer, DATA_BUFFER_LEN, datafile);

        while (read_success != NULL && !done) {
                // If the line of input begins with an integer, treat
                // it as the memory value to read in.  Ignore junk
                // after the number and ignore blank lines and lines
                // that don't begin with a number.
                //
                words_read = sscanf(buffer, "%d", &value_read);

                // *** STUB *** 
                int upperbound = 9999;
                int lowerbound = -9999;
                if(words_read==1)
                {
                	if(loc>99)
                	{
                		printf("The location value exceed 100\n");
                		break;
                	}
                	else if((value_read<lowerbound)||(value_read>upperbound))
                	{
                		printf("The value is sentinel at memory location %d\n",loc);
                		break;
                	}
                	else
                	{
                		cpu -> mem[loc]=value_read;
                		loc++;
                	}
                }
                // if an integer was actually read in, then
                // set memory value at current location to
                // value_read and increment location.  Exceptions: If
                // loc is out of range, complain and quit the loop. If
                // value_read is outside -9999...9999, then it's a
                // sentinel -- we should say so and quit the loop.

                // Get next line and continue the loop
                //
                // *** STUB ***
                read_success = fgets(buffer, DATA_BUFFER_LEN, datafile);


        }

        // Initialize rest of memory
        //
        while (loc < MEMLEN) {
                cpu -> mem[loc++] = 0;
        }
}

// Get the data file to initialize memory with.  If it was
// specified on the command line as argv[1], use that file
// otherwise use default.sdc.  If file opening fails, complain
// and terminate program execution with an error.
// See linux command man 3 exit for details.
//
FILE *get_datafile(int argc, char *argv[]) {
        char *default_datafile_name = "default.sdc";
        char *datafile_name = NULL;

        // *** STUB *** set datafile name to argv[1] or default
        datafile_name = default_datafile_name;  // *** STUB ***
        //if there exist argv[1], change the file name
        if(argv[1]!=NULL)
        {
        	datafile_name=argv[1];
        }
        FILE *datafile = fopen(datafile_name, "r");

        // *** STUB *** if the open failed, complain and call
        // exit(EXIT_FAILURE); to quit the entire program
        if(datafile==NULL)
        {
        	printf("Cannot open the file!!!\n");
        	exit(EXIT_FAILURE);
        }
        return datafile;
}

// dump_control_unit(CPU *cpu): Print out the control unit
// (PC, IR, running flag, and general-purpose registers).
// 
void dump_control_unit(CPU *cpu) {
        // *** STUB ****
	//PRinting out all the neccesary variable
	printf("SDC SIMULATOR\n");
	printf("PC:		%d\n",cpu -> pc);
	printf("IR:		%d\n",cpu -> ir);
	printf("RUNNING:	%d\n",cpu -> running);
	dump_registers(cpu);
}

// dump_memory(CPU *cpu): For each memory address that
// contains a non-zero value, print out a line with the
// address, the value as an integer, and the value
// interpreted as an instruction.
//
void dump_memory(CPU *cpu) {
        printf("Memory: @Loc, value, instr (nonzero values only):\n");

        // *** STUB ****

        //looping through the memory to outprint the value and the prnt_str
        for(int i = 0;i<100;i++)
        {
        	if(cpu -> mem[i]!=0)
        	{
        		printf("@%02d   ",i);
        		print_instr(cpu -> mem[i]);
        		printf("\n");
        	}
        }
        // for each location, if the value is nonzero, then
        // print the location and value (as an integer),
        // and call print_instr on the value to print out
        // the value as an instruction
}

// dump_registers(CPU *cpu): Print register values in two rows of
// five.
//
void dump_registers(CPU *cpu) {
        // *** STUB ****
	//using a for loop to print out the value of the first 5 registers 
	for(int i=0;i<5;i++)
	{
		printf("R%d:%d\t",i,cpu -> reg[i]);
	}
	printf("\n");
	//using a for loop to print out the value of the last 5 registers 
	for(int j=5;j<10;j++)
	{
		printf("R%d:%d\t",j,cpu -> reg[j]);
	}
	printf("\n");
}

// print_instr(instr) prints the 4-digit instruction in a mnemonic format.
//
void print_instr(int instr) {
        // *** STUB ***
		//getting the Memory Location Value 
		//since the instruction is 4 digit, the last 2 digits are memory
		//to find out the digit memory location, take the modulus of 100
		//make a copy of instr

		int copy = instr;
		int memory = instr%100;
		//making a check value to check if opcode is -5,-6 or -8
		int check=0;
		//getting the value left 
		instr = (instr-memory)/100;
		//if the instr value left is >= 90 that mean the OPCODE is 9x
		//we can ignore the refister value if OPCODE is 9x
		int op,reg=0;

		if((instr>=90)||(instr<=-90))
		{
			op = instr;
		}
		//else the first digit will be opcode, the second digit will be register
		else 
		{
			//register value
			reg = instr%10;
			//calculate what left in instr
			instr=(instr-reg)/10;
			op=instr; 
			if((op==-6)||(op==-8)||(op==-5))
			{
				check = 1;
			}

		}
		//convert all the reg and memory and opcode(if differrent than 5,6,8) to absolute value
		memory = abs(memory);
		
		reg = abs(reg);
		//if check =1 => the number cant be convert since it will cause error
		if(check == 0)
		{
			op= abs(op);

		}

		//The codes above finish assigning value to op code, memory, register
		//translating opcode to semantics value
		//in each of the case, we will return the printing line also 
		//along with the opcode, the instruction and the memory
		//char semantic is the instruction semantic 
		//char pr is the string that will be printed
		if(op==0)
		{
			char semantic[]="HALT";
			printf("%04d  %s",copy,semantic);
		}
		else if(op==1)
		{
			char semantic2[]="LD";
			printf("%d  %s  R%d,%d",copy,semantic2,reg,memory);
		}
		else if(op==2)
		{
			char semantic3[]="ST";
			printf("%d  %s  R%d,%d",copy,semantic3,reg,memory);
		}
		else if(op==3)
		{
			char semantic4[]="ADD";
			printf("%d  %s  R%d,%d",copy,semantic4,reg,memory);
		}
		else if(op==4)
		{
			char semantic5[]="NEG";
			printf("%d  %s  R%d",copy,semantic5,reg);
		}
		else if(op==5)
		{
			char semantic6[]="LDM";
			printf("%d  %s  R%d,%d",copy,semantic6,reg,memory);
		}
		else if(op==-5)
		{
			char semantic7[]="LDM";
			printf("%d  %s  R%d,-%d",copy,semantic7,reg,memory);
		}
		else if(op==6)
		{
			char semantic8[]="ADDM";
			printf("%d  %s  R%d,%d",copy,semantic8,reg,memory);
		}
		else if(op==-6)
		{
			char semantic9[]="SUBM";
			printf("%d  %s  R%d,%d",copy,semantic9,reg,memory);
		}
		else if(op==7)
		{
			char semantic10[]="BR";
			printf("%d  %s  %d",copy,semantic10,memory);
		}
		else if(op==8)
		{
			char semantic11[]="BRGE";
			printf("%d  %s  R%d,%d",copy,semantic11,reg,memory);
		}
		else if(op==-8)
		{
			char semantic12[]="BRLE";
			printf("%d  %s  R%d,%d",copy,semantic12,reg,memory);
		}
		else if(op==90)
		{
			char semantic13[]="GETC";
			printf("%d  %s",copy,semantic13);
		}
		else if(op==91)
		{
			char semantic14[]="OUT";
			printf("%d  %s",copy,semantic14);
		}
		else if(op==92)
		{
			char semantic15[]="PUTS";
			printf("%d  %s  %d",copy,semantic15,memory);
		}
		else if(op==93)
		{
			char semantic16[]="DMP";
			printf("%d  %s",copy,semantic16);
		}
		else if(op==94)
		{
			char semantic17[]="MEM";
			printf("%04d  %s",copy,semantic17);
		}
		else if((op>=95)&&(op<=99))
		{
			char semantic18[]="NOP";
			printf("%04d  %s",copy,semantic18);
		}

}

// Read a simulator command from the keyboard (q, h, ?, d, number,
// or empty line) and execute it.  Return true if we hit end-of-input
// or execute_command told us to quit.	Otherwise return false.
//
int read_execute_command(CPU *cpu) {
// Buffer to read next command line into
#define CMD_LINE_LEN 80
	char cmd_line[CMD_LINE_LEN];
	char *read_success;		// NULL if reading in a line fails

	int check=0;

	int nbr_cycles;		// Number of instruction cycles to execute
	char cmd_char;		// Command 'q', 'h', '?', 'd', or '\n'
	int done = 0;		// Should simulator stop?

	read_success = fgets(cmd_line, CMD_LINE_LEN, stdin);

	// *** STUB ***	 Quit if read_success indicates end-of-file
	if (*read_success == EOF)
	{
		exit(0);
	}

	// *** STUB ***
	// while not done,
	// Handle q, h, ?, d commands, integer (nbr of instruction cycles),
	// or empty line (one instruction cycle)
	// Read next command line, check for eof
	while(!done)
	{	
		check = sscanf(cmd_line,"%d",&nbr_cycles);
		if (check == 0)
		{
			check = sscanf(cmd_line,"%c",&cmd_char);
			execute_command(cmd_char,cpu);
		}
		else
		{
			many_instruction_cycles(nbr_cycles,cpu);
		}
		read_success = fgets(cmd_line, CMD_LINE_LEN, stdin);
		if(*read_success == EOF)
		{
			exit(0);
		}
	}

	return done;
}

// Execute a nonnumeric command; complain if it's not 'h', '?',
// 'd', 'q' or '\n'. Return true for the q command, false otherwise.
//
int execute_command(char cmd_char, CPU *cpu) {
	if (cmd_char == '?' || cmd_char == 'h') {
		help_message();
	}
	// *** STUB ****
	else if(cmd_char=='q')
	{
		printf("quitting");
		exit(1);
		return 1;
	}
	else if(cmd_char=='d')
	{
		dump_control_unit(cpu);
		dump_memory(cpu);
	}
	else if(cmd_char=='\n')
	{

		one_instruction_cycle(cpu);
	}
	else
	{
		printf("not a nonnumeric command");
	}
	return 0;
}

// Print standard message for simulator help command ('h' or '?')
//
void help_message(void) {
	// *** STUB ****
	printf("Simulator command:\n");
	printf("h or ? for help ( print this message)\n");
	printf("d to dump the CPU\n");
	printf("An integer > 0 to excecute that many instruction cycles \n or just return, which executes one instruction cycle\n");
}

// Execute a number of instruction cycles.  Exceptions: If the
// number of cycles is <= 0, complain and return; if the CPU is
// not running, say so and return; if the number of cycles is
// insanely large, warn the user and substitute a saner limit.
//
// If, as we execute the many cycles, the CPU stops running,
// stop and return.
//
void many_instruction_cycles(int nbr_cycles, CPU *cpu) {
	int INSANE_NBR_CYCLES = 100;

	// *** STUB ****
	if(nbr_cycles>=INSANE_NBR_CYCLES)
	{
		printf("the number is too large\n");
		nbr_cycles=99;
	}
	else if(nbr_cycles<=0)
	{
		printf("number off cycle too small\n");
		return;
	}
	
	if(cpu -> running != 1 )
	{
		printf("HALTED! CPU is not running\n");
		return;
	}

	for(int i=0;i< nbr_cycles;i++)
	{
		if(cpu ->running != 1)
		{
			printf("the CPU is not running\n");
			return;
		}
		else
		{
			one_instruction_cycle(cpu);
		}
	}


}

// Execute one instruction cycle
//
void one_instruction_cycle(CPU *cpu) {
	// If the CPU isn't running, say so and return.
	// If the pc is out of range, complain and stop running the CPU.
	if(cpu -> running == 0)
	{
		printf("Halted");
		return;
	}
	if(!(cpu -> pc >= 0 && cpu -> pc <= 99))
	{
		printf("Out of range");
		return;
	}
	//
	// *** STUB ****

	// Get instruction and increment pc
	//
	// For printing purposes, we'll save the location of
	// the instruction (the pc before the increment).
	//
	int instr_loc = cpu -> pc;
	cpu -> ir = cpu -> mem[cpu -> pc];
	(cpu -> pc)++;

	// Decode instruction into opcode, reg_R, addr_MM, and instruction sign
	//
	// *** STUB ***
	if (abs(cpu -> ir) < 9000)
	{
		cpu -> opcode = abs(cpu -> ir/1000);
	}
	else 
	{
		cpu -> opcode = abs(cpu -> ir/100);
	}
	cpu -> reg_R = abs((cpu -> ir/100)%10);
	cpu -> addr_MM = abs(cpu -> ir%100);
	if (cpu -> ir < 0)
	{
		cpu -> instr_sign = -1;
	}
	else
	{
		cpu -> instr_sign = 1;
	}


	// Echo instruction
	// *** STUB ***
	char *instr[MEMLEN];
	instr[0] = "HALT";
	instr[1] = "LD";
	instr[2] = "ST";
	instr[3] = "ADD";
	instr[4] = "NEG";
	instr[5] = "LDM";
	instr[6] = "ADDM";
	instr[7] = "BR";
	instr[8] = "BRGE";
	instr[90] = "GETC";
	instr[91] = "OUT";
	instr[92] = "PUTS";
	instr[93] = "DMP";
	instr[94] = "MEM";
	instr[95] = "NOP";

	int temp=0;
	char out;
	char cmd_line[CMD_LINE_LEN];
	char usr_char;
	char *read_success;

	switch (cpu -> opcode) {
	case 0: exec_HLT(cpu); break;
	// *** STUB ****
	case 1:
		cpu -> reg[cpu->reg_R] = cpu -> mem[cpu -> addr_MM];
		printf("%.2d % .4d   %s\tR%d, % .2d  |  R%d <- M[%d] = %d\n", instr_loc, cpu -> ir, instr[cpu -> opcode], cpu -> reg_R, cpu -> addr_MM, cpu -> reg_R, cpu -> addr_MM, cpu -> reg[cpu -> reg_R]);
		break;
	case 2:
	cpu -> mem[cpu -> addr_MM] = cpu -> reg[cpu -> reg_R];
	printf("%.2d % .4d   %s\tR%d, % .2d  |  M[%d] <- R%d = %d\n", instr_loc, cpu -> ir, instr[cpu -> opcode], cpu -> reg_R, cpu -> addr_MM, cpu -> addr_MM, cpu -> reg_R, cpu -> mem[cpu -> addr_MM]);
		break;
	case 3: 
		temp = cpu -> reg[cpu -> reg_R];
		cpu -> reg[cpu -> reg_R] += cpu -> mem[cpu -> addr_MM];
		printf("%.2d % .4d   %s\tR%d, % .2d  |  R%d <- R%d + M[%d] = %d + %d = %d\n", instr_loc, cpu -> ir, instr[cpu -> opcode], cpu -> reg_R, cpu -> addr_MM, cpu -> reg_R, cpu -> reg_R, cpu -> addr_MM, temp, cpu -> mem[cpu -> addr_MM], cpu -> reg[cpu -> reg_R]);
		break;
	case 4:
		cpu -> reg[cpu -> reg_R] *= -1;
		printf("%.2d % .4d   %s\tR%d\t |  R%d <- -R%d = %d\n", instr_loc, cpu -> ir, instr[cpu -> opcode], cpu -> reg_R, cpu -> reg_R, cpu -> reg_R, cpu -> reg[cpu -> reg_R]);
		break;
	case 5:
		cpu -> reg[cpu -> reg_R] = cpu -> addr_MM * cpu -> instr_sign;
		printf("%.2d % .4d   %s\tR%d, % .2d  |  R%d <- %d\n", instr_loc, cpu -> ir, instr[cpu -> opcode], cpu -> reg_R, cpu -> addr_MM*cpu -> instr_sign, cpu -> reg_R, cpu -> reg[cpu -> reg_R]);
		break;
	case 6:
		cpu -> reg[cpu -> reg_R] += cpu -> instr_sign * cpu -> addr_MM;
		if(cpu -> ir <0)
		{
			instr[6]="SUBM";
		}
		printf("%.2d % .4d   %s\tR%d, % .2d  |  R%d <- R%d + %d = %d + %d = %d\n", instr_loc, cpu -> ir, instr[cpu -> opcode], cpu -> reg_R, cpu -> addr_MM*cpu -> instr_sign, cpu -> reg_R, cpu -> reg_R, cpu -> addr_MM*cpu -> instr_sign, temp, cpu -> addr_MM*cpu -> instr_sign, cpu -> reg[cpu -> reg_R]); 
		break;
	case 7:
		cpu -> pc = cpu -> addr_MM;
		printf("%.2d % .4d   %s\t    % .2d  |  PC <- %d\n", instr_loc, cpu -> ir, instr[cpu -> opcode], cpu -> addr_MM, cpu -> pc);
		break;
	case 8:
		 if (cpu -> ir < 0)
		{
			instr[8] = "BRLE";
		}
		if ((cpu -> ir > 0 && cpu -> instr_sign == 1) || (cpu -> ir < 0 && cpu -> instr_sign == -1))
		{
			cpu -> pc = cpu -> addr_MM;
		}
		if (cpu -> reg[cpu -> reg_R] >= 0)
		{
			printf("%.2d % .4d   %s\tR%d, % .2d  |  PC <- %d if R%d = %d > 0\n", instr_loc, cpu -> ir, instr[cpu -> opcode], cpu -> reg_R, cpu -> addr_MM, cpu -> pc, cpu -> reg_R, cpu -> reg[cpu -> reg_R]);
		}
		else
		{
			printf("%.2d % .4d   %s\tR%d, % .2d  |  PC <- %d if R%d = %d < 0\n", instr_loc, cpu -> ir, instr[cpu -> opcode], cpu -> reg_R, cpu -> addr_MM, cpu -> pc, cpu -> reg_R, cpu -> reg[cpu -> reg_R]);
		}
		break;
	case 90: 
		#define CMD_LINE_LEN 80
		printf("%.2d % .4d   %s\t\t |  ", instr_loc, cpu -> ir, instr[ cpu -> opcode]);
		printf("Enter a char: ");
		read_success = fgets(cmd_line, CMD_LINE_LEN, stdin);
		usr_char = *read_success;
		cpu -> reg[0] = usr_char;
		printf("  R0 <- %d\n", cpu -> reg[0]);
		break;
	case 91:
		out  = cpu -> reg[0];
		printf("%.2d % .4d   %s\t\t |  Print char in R%d (= %d): ", instr_loc, cpu -> ir, instr[cpu -> opcode], cpu -> reg_R, out);
		printf("%c\n", out);
		break;
	case 92: 
		printf("%.2d % .4d   %s\t    % .2d  |  String: ", instr_loc, cpu -> ir, instr[cpu -> opcode], cpu -> addr_MM);
		int temp = cpu -> addr_MM;
		
		while (cpu -> mem[temp] != 0)
		{
			printf("%c", cpu -> mem[temp]);
			temp++;
		}
		printf("\n");
		break;
	case 93:
		printf("%.2d % .4d   %s\t\t \n", instr_loc, cpu -> ir, instr[cpu -> opcode]);
		printf("\n");
		dump_control_unit(cpu);
		break;
	case 94: 
		printf("%.2d % .4d   %s\t\t \n", instr_loc, cpu -> ir, instr[cpu -> opcode]);
		dump_memory(cpu);
		printf("\n\n");
		break;
	case 95:
	case 96:
	case 97:
	case 98:
	case 99:
		printf("%.2d % .4d   %s\t \n", instr_loc, cpu -> ir, instr[cpu -> opcode]);
		break;



	default: printf("Bad opcode!? %d\n", cpu -> opcode);
	}
}

// Execute the halt instruction (make CPU stop running)
//
void exec_HLT(CPU *cpu) {
	// *** STUB *** Print a message?
	printf("halted\n");
	cpu -> running = 0;
}
