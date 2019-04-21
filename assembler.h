#pragma once

#include <fstream>
#include <bitset>

void assemble(std::string inputFile, std::string outputFile)
{
	std::ifstream inFile;
	std::ofstream otFile(outputFile);
	std::string instruction,
		argumentAddr1,
		argumentAddr2,
		argumentAddr3,
		machineLine,
		ignore;
	bool complete = false;

	inFile.open(inputFile);
	if (!inFile)
	{
		throw std::invalid_argument("infile not accessable");
	}
	while (!complete) {
		inFile >> instruction;
		if (inFile)
		{
			/*
			 * this checks if the instruction is actually a comment
			 */
			if (instruction == ";")
			{
				std::getline(inFile, ignore);
			}

			else
			{
				/*
				instruction : JIE
				binary representatioin : 0000 1010
				usage :
				JIE [argument address] [argument address] [argument address]
				jumps to the third argument address if the value of the first argument
				address equals the second argumet address
				*/
				if (instruction == "JIE")
				{
					inFile >> argumentAddr1;
					inFile >> argumentAddr2;
					inFile >> argumentAddr3;
					machineLine = "00001010" + std::bitset<8>(stoi(argumentAddr1)).to_string() + std::bitset<8>(stoi(argumentAddr2)).to_string() + std::bitset<8>(stoi(argumentAddr3)).to_string();
				}

				/*
				instruction : JMP
				binary representatioin : 0000 0101
				usage :
				JMP [argument address]
				unconditionally jumps to the argument address provided
				*/
				else if (instruction == "JMP")
				{
					inFile >> argumentAddr1;
					machineLine = "00000101" + std::bitset<8>(stoi(argumentAddr1)).to_string() + "0000000000000000";
				}

				/*
				instruction : MOV
				binary representatioin : 0000 1100
				usage :
				MOV [argument address] [argument address]
				copies the value stored in the first argument address to the second argument
				address unconditionally
				*/
				else if (instruction == "MOV")
				{
					inFile >> argumentAddr1;
					inFile >> argumentAddr2;
					machineLine = "00001100" + std::bitset<8>(stoi(argumentAddr1)).to_string() + std::bitset<8>(stoi(argumentAddr2)).to_string() + "00000000";
				}


				/*
				instruction : ADD
				binary representatioin : 0000 1011
				usage :
				ADD [argument address] [argument address] [argument address]
				adds the contents of the first argument address to the second argument
				address and then places the result in the third argument address
				*/
				else if (instruction == "ADD")
				{
					inFile >> argumentAddr1;
					inFile >> argumentAddr2;
					inFile >> argumentAddr3;
					machineLine = "00001011" + std::bitset<8>(stoi(argumentAddr1)).to_string() + std::bitset<8>(stoi(argumentAddr2)).to_string() + std::bitset<8>(stoi(argumentAddr3)).to_string();
				}


				/*
				instruction : FLP
				binary representatioin : 0000 0100
				usage :
				FLP [argument address]
				flips the bits in the argument address provided
				*/
				else if (instruction == "FLP")
				{
					inFile >> argumentAddr1;
					machineLine = "00000100" + std::bitset<8>(stoi(argumentAddr1)).to_string() + "0000000000000000";
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
				else if (instruction == "RED")
				{
					inFile >> argumentAddr1;
					inFile >> argumentAddr2;
					machineLine = "00001101" + std::bitset<8>(stoi(argumentAddr1)).to_string() + std::bitset<8>(stoi(argumentAddr2)).to_string() + "00000000";
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
				else if (instruction == "WRT")
				{
					inFile >> argumentAddr1;
					inFile >> argumentAddr2;
					machineLine = "00000010" + std::bitset<8>(stoi(argumentAddr1)).to_string() + std::bitset<8>(stoi(argumentAddr2)).to_string() + "00000000";
				}


				/*
				instruction : STP
				binary representatioin : 0000 1111
				usage :
				STP
				Stops the execution of code by system/b
				*/
				else if (instruction == "STP")
				{
					machineLine = "00001111000000000000000000000000";
				}

				/*
				this ignores comments on lines
				*/
				else
				{
					machineLine = std::bitset<32>(stoi(instruction)).to_string();
				}
				otFile << machineLine << std::endl;
			}
		}
		else
		{
			complete = true;
		}
	}
	otFile.close();
	inFile.close();
}
