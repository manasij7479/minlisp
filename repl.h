/**
 * The Read-Eval-Print Loop functor class 
 */
#ifndef REPL
#define REPL
#include <string>
#include<vector>
#include<ostream>
#include<istream>
#include<fstream>
namespace mm
{
	class repl
	{
	protected :
		std::ostream& out;
		std::istream& in;
		
		std::string read();
		std::string eval(const std::string& s);
		void print(const std::string& s);
		void clean();
	public:
		void init();
		int operator()();
		repl(std::istream& i,std::ostream& o):out(o),in(i){};
		repl();
	};
	class file_repl:public repl
	{
	public:
		int operator()();
		file_repl(std::string filename,std::ostream& o)
			:repl(*(new std::ifstream(filename)),o){};		
	};

}
#endif