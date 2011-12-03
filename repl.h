/**
 * The Read-Eval-Print Loop functor class 
 */
#ifndef REPL
#define REPL
#include <string>
#include<vector>
namespace mm
{
	class repl
	{
		std::string input,output;
		void read();
		void eval();
		void print();
		void clean();
	public:
		static void init();
		int operator()();
		friend class file_repl;
	};

}
#endif