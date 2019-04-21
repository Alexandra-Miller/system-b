#include <iostream>
#include <string>
#include "ioStrings.h"
#include "assembler.h"
#include "SystemBvm.h"

/*
 * This is the system/b "shell" allows the user to interact with it. Feel free to write your own if you want.
 * note : the shell is not complete and needs more work to add full functionality to system/b
 */

int main()
{
	bool quit = false;
	SystemBvm1024 vm;
	std::string cmdInput,
		command,
		argument1,
		argument2;


	std::cout << welcomeText();
	do
	{
		std::cin.clear();
		std::cout << "system/b> "; std::cin >> command;
		if (command == "m") 
		{
			std::cout << manualText();
			std::cout << std::endl;
		} 
		else if ((command == "assemble") || (command == "a"))
		{
			try 
			{
				std::cout << "inFile> "; std::cin >> argument1;
				std::cout << "outFile> "; std::cin >> argument2;
				assemble(argument1, argument2);
				std::cout << "file assembled sucessfully " << std::endl;
			}
			catch (const std::invalid_argument& e)
			{
				std::cout << e.what() << std::endl;
			}
			std::cout << std::endl;
		}
		else if ((command == "boot") || (command == "b"))
		{
			try 
			{
				std::cout << "inFile> "; std::cin >> argument1;
				vm.boot(argument1);
				std::cout << "boot completed " << std::endl;
			}
			catch (const std::invalid_argument& e)
			{
				std::cout << e.what() << std::endl;
			}
		}
		else if ((command == "immDump") || (command == "imm"))
		{
			try 
			{
				vm.immDump();
				std::cout << "imm dump completed " << std::endl;
			}
			catch (const std::invalid_argument& e)
			{
				std::cout << e.what() << std::endl;
			}
		}
		else if ((command == "immDump") || (command == "idr"))
		{
			try 
			{
				vm.idrDump();
				std::cout << "idr dump completed " << std::endl;
			}
			catch (const std::invalid_argument& e)
			{
				std::cout << e.what() << std::endl;
			}
		}
		else if ((command == "stepCycle") || (command == "sc"))
		{
			try 
			{
				vm.stepCycle();
				std::cout << "cycle step completed " << std::endl;
			}
			catch (const std::invalid_argument& e)
			{
				std::cout << e.what() << std::endl;
			}
		}
		else if ((command == "checkCounter") || (command == "cc"))
		{
			try
			{
				std::cout << "current instruction counter : " << vm.getinstructionCounter() << std::endl;
			}
			catch (const std::invalid_argument& e)
			{
				std::cout << e.what() << std::endl;
			}
		}
		else if ((command == "getOutput") || (command == "go"))
		{
			try
			{
				std::cout << "output address contains : " << vm.getOutput() << std::endl;
			}
			catch (const std::invalid_argument& e)
			{
				std::cout << e.what() << std::endl;
			}
		}
		else if ((command == "setInput") || (command == "si"))
		{
			try
			{
				std::cin >> argument1;
				vm.setInput(argument1);
			}
			catch (const std::invalid_argument& e)
			{
				std::cout << e.what() << std::endl;
			}
		}
		else if ((command == "quit") || (command == "q"))
		{
			quit = true;
		} 
		else 
		{
			std::cout << errorText();
		}
	} while (!quit);
	std::cout << quitText();

	return 0;
}