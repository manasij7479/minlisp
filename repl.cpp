#include "repl.h"
#include <iostream>
#include "env.h"
#include "list.h"
#include "function.h"
#include "macro.h"
#include <cctype>
namespace mm
{
	void prompt()
	{
		std::cout<<"[minlisp]";
	}
	void repl::read()
	{
		prompt();
		std::string line;
		std::ostringstream result;
		int nest(0);
		std::cin.exceptions(std::ios::eofbit);
		while(true)
		{
			std::getline(std::cin,line);
			if(line==""){prompt();continue;}
			//if(iscntrl(line[0])){prompt();continue;}
			for(auto t:line)
			{
				if(t=='(')
					{nest++;result<<' '<<t<<' ';}
				else if(t==')')
					{nest--;result<<' '<<t<<' ';}
				else result<<t;
			}
			if(nest==0)break;
			if(nest<0){throw("Mismatched Parentheses.");}
		}
		input=result.str();
	}
	void repl::eval()
	{
		list l(input);
		output = l.eval();
	}
	void repl::print()
	{
		std::cout<<output<<std::endl;
	}
	void repl::init()
	{
		f_scope.new_local(global_f_map);
		m_scope.new_local(global_m_map);
	}
	void repl::clean()
	{
		std::cout<<"Bye\n";
		f_scope.exit_scope();
		m_scope.exit_scope();
	}
	int repl::operator()()
	{
		init();
		
		while(true)
		{
			try
			{
				read();
				eval();
				print();	
			}
			catch(exception e)
			{
				std::cout<<e.what()<<std::endl;
			}
			catch(const std::ios::failure& problem)
			{
				std::cout<<"Received EOF: Program will Quit."<<std::endl;
				break;
			}
		}
		clean();
		return 0;
	}
}
