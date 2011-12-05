#include "repl.h"
#include <iostream>
#include<fstream>
#include "env.h"
#include "list.h"
#include "function.h"
#include "macro.h"


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
			for(auto t:line)
			{
				if(t=='(')
					{nest++;result<<' '<<t<<' ';}
				else if(t==')')
					{nest--;result<<' '<<t<<' ';}
				else result<<t;
			}
			if(nest==0)break;
			if(nest<0){throw(exception("Mismatched Parentheses."));}
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
			std::map<std::string,function> local_fmap;
			f_scope.new_local(local_fmap);//This is primarily for lambda functions
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
			catch(const std::ios::failure&)
			{
				std::cout<<"Received EOF: Program will Quit."<<std::endl;
				break;
			}
			f_scope.exit_scope();
		}
		clean();
		return 0;
	}

// 	void file_repl::read()
// 	{
// 		std::ifstream ifs(filename);
// 		if(!ifs)throw(exception(filename+": Can't be opened#"));
// 		std::string line;
// 		std::ostringstream* result=new std::ostringstream();
// 		int nest(0);
// 		while(std::getline(ifs,line))
// 		{
// 			if(line=="")continue;
// 			for(auto t:line)
// 			{
// 				if(t=='(')
// 				{nest++;*result<<' '<<t<<' ';}
// 				else if(t==')')
// 				{nest--;*result<<' '<<t<<' ';}
// 				else *result<<t;
// 			}
// 			if(nest==0)
// 			{
// 				input.push_back(result->str());
// 				delete result;
// 				result = new std::ostringstream();
// 				
// 			}
// 			if(nest<0)throw(exception("Mismatched Parentheses."));
// 		}
// 		if(nest!=0)throw(exception("Mismatched Parentheses."));
// 		
// 	}
}
