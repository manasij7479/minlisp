#include "repl.h"
#include <iostream>
int main(int argc,char** argv)
{
	if(argc==1)
	{
		mm::repl main_loop(std::cin,std::cout);
		return main_loop();
	}
	if(argc==2)
	{
		mm::file_repl fmain_loop(std::string(argv[1]),std::cout);
		return fmain_loop();
	}
	else
		return 1;
}
