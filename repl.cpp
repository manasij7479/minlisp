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
	std::string repl::read()
	{
		std::string line;
		std::ostringstream result;
		int nest(0);
		in.exceptions(std::ios::eofbit);
		while(true)
		{
			std::getline(in,line);
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
		return result.str();
	}
	std::string repl::eval(const std::string& s)
	{
		list l(s);
		return l.eval();
	}
	void repl::print(const std::string& s)
	{
		out<<s<<std::endl;
	}
	void repl::init()
	{
		if(!in || !out){std::cout<<"File(s) was not opened correctly.\n";exit(-1);}
		f_scope.new_local(global_f_map);
		m_scope.new_local(global_m_map);
		var_scope.new_local(* new std::map<std::string,std::string>());
	}
	void repl::clean()
	{
		out<<"Bye\n";
		f_scope.exit_scope();
		m_scope.exit_scope();
		var_scope.exit_scope();
	}
	int repl::operator()()
	{
		init();
		while(true)
		{
			int var_scope_ini_size = var_scope.size();
			std::map<std::string,function> local_fmap;
			f_scope.new_local(local_fmap);//This is primarily for lambda functions
			try
			{
				std::string temp;
					prompt();
				temp=read();
					if(temp=="")continue;
				temp = eval(temp);
				print(temp);
				
			}
			catch(exception& e)
			{
				out<<e.what()<<std::endl;
			}
			catch(const std::ios::failure&)
			{
				break;
			}
			f_scope.exit_scope();
			while(var_scope.size()>var_scope_ini_size) 
				var_scope.exit_scope();
		}
		clean();
		return 0;
	}
	int file_repl::operator()()
	{
		init();
		while(true)
		{
			int var_scope_ini_size = var_scope.size();
			std::map<std::string,function> local_fmap;
			f_scope.new_local(local_fmap);//This is primarily for lambda functions
			try
			{
				std::string temp;
				temp=read();
				temp=eval(temp);
				if(f_scope.find(temp)==nullptr)
					print(temp);

			}
			catch(exception& e)
			{
				out<<e.what()<<std::endl;
			}
			catch(const std::ios::failure&)
			{
				break;
			}
			f_scope.exit_scope();
			while(var_scope.size()>var_scope_ini_size)
			var_scope.exit_scope();
		}
		return 0;
	}
}
