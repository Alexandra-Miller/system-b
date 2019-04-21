#pragma once

#include <string>

std::string welcomeText()
{
	return
	"                    __                       __   __  \n"
	"   _______  _______/ /____  ____ ___       _/_/  / /_ \n"
	"  / ___/ / / / ___/ __/ _ \\/ __ `__ \\    _/_/   / __ \\\n"
	" (__  ) /_/ (__  ) /_/  __/ / / / / /  _/_/    / /_/ /\n"
	"/____/\\__, /____/\\__/\\___/_/ /_/ /_/  /_/     /_.___/ \n"
	"	 /____/                                            \n"
	"a simple virtual machine\n"
	"\n"
	"\n";
}

std::string errorText()
{
	return
		"Invalid input, could not parse.\n"
		"Abort, Retry, Fail?\n"
		"\n";
}

std::string manualText()
{
	return
		"system/b manual : \n"
		"\n"
		"system/b is an evolution on the earlier system/a virtual machine archictecture using\n"
		"a similar 32 bit word size and word addressed memory, but now with direct addressing\n"
		"allowing for a signifigant expansion in the size of programs that can be run by\n"
		"system/b from 1024 bytes to up to 17179869184 bytes of code. This is divided between\n"
		"the 1024 bytes of immediately addressed space and 17179869184 bytes of directly\n"
		"addressed space. Direct addressing is conducted using the RED and WRT instructions. An\n"
		"explination of the instructions used by system/b and their use is contained in the\n"
		"\"instruction setsection\" of the system/b manual.\n"
		"\n"
		"sections :\n"
		"0 basic operation \\ shell commands\n"
		"1 instruction set\n"
		"2 debugging code\n"
		"3 system implmentation\n"
		"\n"
		"\n"
		"\n"
		"0 basic operation \\ shell commands :\n"
		"command, alias | arguments                          | description \n"
		"assemble,  a   | input_file(sba), output_file(sbm)  | assembles the input file\n"
		"manual,    m   | null                               | displays this manual\n"
		"quit,      q   | null                               | quits the shell\n"
		"boot,      b   | input_file(sbm)                    | boots the systm/b vm with\n"
		"               |                                    | the code in the immediately\n"
		"               |                                    | addressed space.\n"
		"stepCycle, sc  | null                               | steps the system/b vm one cycle\n"
		"immDump,   imm | null                               | dumps the immediately addressed\n"
		"               |                                    | space to the file \"immDump.txt\"\n"
		"idrDump,   idr | null                               | dumps the indirectly addressed\n"
		"               |                                    | space to the file \"idrDump.txt\"\n"
		"\n"
		"\n"
		"\n"
		"1 instruction set :\n"
		"The system/b instruction set is a fixed width instructon set containing eight\n"
		"instructions, MOV, ADD, FLP, JIE, JMP, RED, WRT and STP. All instructions except the\n"
		"special instructions RED and WRT only access data from the immediately addressed space.\n"
		"\n"
		"\n"
		"standard instruction format :\n"
		"[instruction] [argument address] [argument address] [argument address]\n"
		"     JIE              AB                 10                23         \n"
		"  0000 1010        1010 1011          0001 0000         0010 0011     \n"
		"\n"
		"\n"
		"instruction : JIE\n"
		"binary representatioin : 0000 1010\n"
		"usage : \n"
		"JIE [argument address] [argument address] [argument address]\n"
		"jumps to the third argument address if the value of the first argument\n"
		"address equals the second argumet address\n"
		"\n"
		"\n"
		"instruction : JMP\n"
		"binary representatioin : 0000 0101\n"
		"usage : \n"
		"JMP [argument address]\n"
		"unconditionally jumps to the argument address provided\n"
		"\n"
		"\n"
		"instruction : MOV\n"
		"binary representatioin : 0000 1100\n"
		"usage : \n"
		"MOV [argument address] [argument address]\n"
		"copies the value stored in the first argument address to the second argument\n"
		"address unconditionally\n"
		"\n"
		"\n"
		"instruction : ADD\n"
		"binary representatioin : 0000 1011\n"
		"usage : \n"
		"ADD [argument address] [argument address] [argument address]\n"
		"adds the contents of the first argument address to the second argument\n"
		"address and then places the result in the third argument address\n"
		"\n"
		"\n"
		"instruction : FLP\n"
		"binary representatioin : 0000 0100\n"
		"usage : \n"
		"FLP [argument address]\n"
		"flips the bits in the argument address provided\n"
		"\n"
		"\n"
		"instruction : RED\n"
		"binary representatioin : 0000 1101\n"
		"usage : \n"
		"RED [argument address] [argument address]\n"
		"special instruction, reads the value located in the directly addressed\n"
		"space to the second argument address, the first argument address provides\n"
		"the pointer to the location of the data in the directly addressed space\n"
		"\n"
		"\n"
		"instruction : WRT\n"
		"binary representatioin : 0000 0010\n"
		"usage : \n"
		"WRT [argument address] [argument address]\n"
		"special instruction, writes the value located in the second argument\n"
		"address to an address located in the directly addressed space, the first\n"
		"argument address provides the pointer to the location of the data in the\n"
		"directly addresssed space\n"
		"\n"
		"\n"
		"instruction : STP\n"
		"binary representatioin : 0000 1111\n"
		"usage : \n"
		"STP\n"
		"Stops the execution of code by system/b\n"
		"\n"
		"\n"
		"\n"
		"debugging code :\n"
		"To debug system/b assembly programs, simply create a system/b instance\n"
		"and load a system/b machine code file into the machine. Then step through\n"
		"the code using the included assembler using the \"stepCycle\" command, it\n"
		"may be advisable to use the immDump and idrDump commands to gain a \n"
		"snapshot of the immediate address space and the indirect address space.\n"
		"Viewing these snapshots, translate the binary to the assembly yourself and\n"
		"use that to identify how the program is running\n"
		"\n"
		"\n"
		"\n"
		"system implmentation :\n"
		"system/b is a simple machine modled loosely on the Analytical Engine\n"
		"as created by Charles Babbage. The operation of system/b is simple to,\n"
		"visualize. The code is loaded into the immediately addressable space as\n"
		"a series of binary instructions that are read by the machine and then\n"
		"executed, with all non-jump instructions iterating the instruction counter\n"
		"by, causing the next instruction in the immediately addressed space to \n"
		"be executed. Code can be loaded into the directly addressed space using the\n"
		"special WRT instruction and read from it using the RED instruction. All numbers\n"
		"are stored in a little endian two's complment format.";
}

std::string quitText()
{
	return
		"Thank you for using system/b, have a nice day.\n";
}