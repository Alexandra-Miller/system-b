#pragma once

#include <fstream>
#include <iostream>
#include <cmath>

/*
 * This is the basic system\b vm with 1024 possible indirectly addressed locations in memory. The addresses FD and FE are used for input and output, repsectively
 */
const short WORD_SIZE = 32;
const short IMM_ADDR_SPACE_SIZE = 256;
const unsigned int IDR_ADDR_SPACE_SIZE = 1024;

class SystemBvm1024
{
private:
	bool immediateAddressSpace[IMM_ADDR_SPACE_SIZE][WORD_SIZE];
	bool indirectAddressSpace[IDR_ADDR_SPACE_SIZE][WORD_SIZE];
	short instructionCounter;


	short addressToShort(short start) 
	{
		short address = 0;
		for (int i = 8; i > 0; i--)
		{
			if (immediateAddressSpace[instructionCounter][i + start - 1])
			{
				address += pow(2,(8 - i));
			}
		}
		return address;
	}

	unsigned int addrToInt(short addr)
	{
		unsigned int address = 0;
		for (int i = WORD_SIZE; i > 0; i--)
		{
			if (immediateAddressSpace[instructionCounter][i - 1])
			{
				address += pow(2, (8 - i));
			}
		}
		return address;
	}
	/*
	instruction : JIE
	binary representatioin : 0000 1010
	usage :
	JIE [argument address] [argument address] [argument address]
	jumps to the third argument address if the value of the first argument
	address equals the second argumet address
	*/
	void JIE()
	{
		bool addrEquality = true;
		const short argAddr0 = addressToShort(8);
		const short argAddr1 = addressToShort(16);
		const short argAddr2 = addressToShort(24);

		for (int i = 0; i < WORD_SIZE; i++)
		{
			if (immediateAddressSpace[argAddr0][i] != immediateAddressSpace[argAddr1][i])
			{
				addrEquality = false;
			}
		}

		if(addrEquality)
		{
			instructionCounter = argAddr2;
		}
		else
		{
			instructionCounter++;
		}
	}
	/*
	instruction : JMP
	binary representatioin : 0000 0101
	usage :
	JMP [argument address]
	unconditionally jumps to the argument address provided
	*/
	void JMP()
	{
		instructionCounter = addressToShort(8);
	}
	/*
	instruction : MOV
	binary representatioin : 0000 1100
	usage :
	MOV [argument address] [argument address]
	copies the value stored in the first argument address to the second argument
	address unconditionally
	*/
	void MOV()
	{
		const short argAddr0 = addressToShort(8);
		const short argAddr1 = addressToShort(16);
	
		for (int i = 0; i < WORD_SIZE; i++)
		{
			immediateAddressSpace[argAddr1][i] = immediateAddressSpace[argAddr0][i];
		}

		instructionCounter++;
	}
	/*
	instruction : ADD
	binary representatioin : 0000 1011
	usage :
	ADD [argument address] [argument address] [argument address]
	adds the contents of the first argument address to the second argument
	address and then places the result in the third argument address
	*/
	void ADD()
	{
		const short argAddr0 = addressToShort(8);
		const short argAddr1 = addressToShort(16);
		const short argAddr2 = addressToShort(24);

		bool carry = false,
			 bit0 = false,
			 bit1 = false;

		for (int i = WORD_SIZE; i >= 0; i--)
		{
			bit0 = immediateAddressSpace[argAddr0][i];
			bit1 = immediateAddressSpace[argAddr1][i];
			if ((bit0 + bit1 == 1) && (carry == 0))
			{
				immediateAddressSpace[argAddr2][i] = 1;
				std::cout << "1";
			}
			else if ((bit0 + bit1 == 0) && (carry == 1))
			{
				immediateAddressSpace[argAddr2][i] = 1;
				carry = 0;
				std::cout << "2";
			}
			else if (bit0 + bit1 + carry == 0)
			{
				immediateAddressSpace[argAddr2][i] = 0;
				carry = 0;
				std::cout << "3";
			}
			else if (bit0 + bit1 + carry == 2)
			{
				immediateAddressSpace[argAddr2][i] = 0;
				carry = 1;
				std::cout << "4";
			}
			else if (bit0 + bit1 + carry == 3)
			{
				immediateAddressSpace[argAddr2][i] = 1;
				carry = 1;
				std::cout << "5";
			}
		}
		std::cout << std::endl;
		std::cout << argAddr0 << "::" << argAddr1 << "::" << argAddr2 << std::endl;

		instructionCounter++;
	}
	/*
	instruction : FLP
	binary representatioin : 0000 0100
	usage :
	FLP [argument address]
	flips the bits in the argument address provided
	*/
	void FLP()
	{
		const short argAddr0 = addressToShort(8);
		for (int i = 0; i < WORD_SIZE; i++)
		{
			immediateAddressSpace[argAddr0][i] = !immediateAddressSpace[argAddr0][i];
		}
		instructionCounter++;
	}
	/*
	instruction : RED
	binary representatioin : 0000 1101
	usage :
	RED [argument address] [argument address]
	special instruction, reads the value located in the directly addressed
	space to the second argument address, the first argument address provides
	the pointer to the location of the data in the directly addressed space
	*/
	void RED()
	{
		const short argAddr0 = addressToShort(8);
		const short argAddr1 = addressToShort(16);
		const unsigned int idrAddr = addrToInt(argAddr0);

		for (int i = 0; i < WORD_SIZE; i++)
		{
			immediateAddressSpace[argAddr1][i] = indirectAddressSpace[idrAddr][i];
		}
		instructionCounter++;
	}
	/*
	instruction : WRT
	binary representatioin : 0000 0010
	usage :
	WRT [argument address] [argument address]
	special instruction, writes the value located in the second argument
	address to an address located in the directly addressed space, the first
	argument address provides the pointer to the location of the data in the
	directly addresssed space
	*/
	void WRT()
	{
		const short argAddr0 = addressToShort(8);
		const short argAddr1 = addressToShort(16);
		const unsigned int idrAddr = addrToInt(argAddr0);

		for (int i = 0; i < WORD_SIZE; i++)
		{
			indirectAddressSpace[idrAddr][i] = immediateAddressSpace[argAddr1][i];
		}
		instructionCounter++;
	}
	/*
	instruction : STP
	binary representatioin : 0000 1111
	usage :
	STP
	Stops the execution of code by system/b
	*/
	void STP()
	{

	}

public:
	void stepCycle()
	{
		bool i0, i1, i2, i3;

		
		i0 = immediateAddressSpace[instructionCounter][4];
		i1 = immediateAddressSpace[instructionCounter][5];
		i2 = immediateAddressSpace[instructionCounter][6];
		i3 = immediateAddressSpace[instructionCounter][7];

		//JIE
		if (i0 && !i1 && i2 && !i3) 
		{
			JIE();
		}
		//JMP
		else if (!i0 && i1 && !i2 && i3)
		{
			JMP();
		}
		//MOV
		else if (i0 && i1 && !i2 && !i3)
		{
			MOV();
		}
		//ADD
		else if (i0 && !i1 && i2 && i3)
		{
			ADD();
		}
		//FLP
		else if (!i0 && i1 && !i2 && !i3)
		{
			FLP();
		}
		//RED
		else if (i0 && i1 && !i2 && i3)
		{
			RED();
		}
		//WRT
		else if (!i0 && !i1 && i2 && !i3)
		{
			WRT();
		}
		//STP
		else if (i0 && i1 && i2 && i3)
		{
			STP();
		}
		else
		{
			instructionCounter++;
		}
	}

	void writeInput(bool input[WORD_SIZE])
	{
		for (int i = 0; i < WORD_SIZE; i++)
		{
			input[i] = immediateAddressSpace[254][i];
		}
	}

	std::string getOutput()
	{
		std::string output = "";
		for (int i = 0; i < WORD_SIZE; i++)
		{
			if (immediateAddressSpace[254][i])
			{
				output += "1";
			}
			else
			{
				output += "0";
			}
		}
		return output;
	}

	void setInput(std::string input)
	{
		for (int i = 0; i < WORD_SIZE; i++)
		{
			if (input[i] == '1')
			{
				immediateAddressSpace[253][i] = 1;
			}
			else
			{
				immediateAddressSpace[253][i] = 0;
			}
		}
	}

	short getinstructionCounter()
	{
		return instructionCounter;
	}

	/* 
	 * this is a dummy bootloader designed to clear the immediately addressable space and load the 
	 * relevant system/b machine code file into the immediately addressable file space
	 */
	void boot(std::string filename)
	{
		std::ifstream inFile(filename);
		char bit;

		instructionCounter = 0;
		for (int i = 0; i < IMM_ADDR_SPACE_SIZE; i++)
		{
			for (int j = 0; j < WORD_SIZE; j++)
			{
				immediateAddressSpace[i][j] = 0;
			}
		}

		for (int i = 0; i < IMM_ADDR_SPACE_SIZE; i++)
		{
			for (int j = 0; j < WORD_SIZE; j++)
			{
				inFile >> bit;
				if (inFile)
				{
					if (bit == '1')
					{
						immediateAddressSpace[i][j] = 1;
					}
					else if (bit == '0')
					{
						immediateAddressSpace[i][j] = 0;
					}
				}
				else
				{
					immediateAddressSpace[i][j] = 0;
				}
			}
		}
		instructionCounter = 0;
	}

	void immDump()
	{
		std::ofstream otFile("immDump.txt");

		otFile << "current instruction counter : " << instructionCounter << std::endl;
		otFile << "Immediate Address Space State :" << std::endl;
		for (int i = 0; i < IMM_ADDR_SPACE_SIZE; i++)
		{
			for (int j = 0; j < WORD_SIZE; j++)
			{
				otFile << immediateAddressSpace[i][j];
			}
			otFile << " " << i << std::endl;
		}
		otFile.close();
	}
	void idrDump()
	{
		std::ofstream otFile("idrDump.txt");
		otFile << "current instruction counter : " << instructionCounter << std::endl;
		otFile << "indirect address space state : " << std::endl;
		for (int i = 0; i < IDR_ADDR_SPACE_SIZE; i++)
		{
			for (int j = 0; j < WORD_SIZE; j++)
			{
				otFile << indirectAddressSpace[i][j];
			}
			otFile << " " << i << std::endl;
		}
		otFile.close();
	}
};
