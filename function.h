/**
 * Function class and the various builtin functions
 */
#ifndef FUNCTION_H
#define FUNCTION_H
#include "list.h"
#include "util.h"
#include<string>
namespace mm
{
	typedef std::string (*f_ptr)(list& l);
	class function
	{
		bool compiled;
		f_ptr body_c;
		list body_l;
		list arg_list;

	public:
		function(list arg_l,f_ptr body):compiled(true),body_c(body),arg_list(arg_l){};
		function(list arg_l,list body):compiled(false),body_l(body),arg_list(arg_l){};
		function(){};
		std::string operator()(list& l);
		/**eg: void foo(int x,int y){}
		 * Here arg_list will contain x and y
		 * AND the argument to operator() must have the values of x and y
		*/
	};
	extern std::map<std::string,function> global_f_map;
}
#endif