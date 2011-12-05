#include "macro.h"
#include "util.h"
#include "function.h"
#include "env.h"
#include <sstream>
namespace mm
{
	std::string macro::operator()(list& l)
	{
		std::string result;
		std::map<std::string,std::string> v,f;
		var_scope.new_local(v);

		result = (*body)(l);

		var_scope.exit_scope();
		return result;
	}
	std::string defun(list& l)
	{
		if(l.size()!=3)throw(exception("Wrong Defun syntax."));
		std::string name = l.car();
		list arg_list = list(l.cdr().car());
		list body_list = list(l.cdr().cdr().car());
		f_scope.new_global_val(name,function(arg_list,body_list));
		return name;
	}
	std::string lambda(list& l)
	{
		if(l.size()!=2)throw(exception("You got the lambda syntax wrong."));
		list arg_list = list(l.car());
		list body_list = list(l.cdr().car());
		int lambda_num_append=f_scope.get_local_num();
		std::ostringstream os; os<<"_lambda_"<<lambda_num_append;
		std::string name(os.str());
		f_scope.new_local_val(name,function(arg_list,body_list));
		return name;
	}

	std::string if_(list& l)
	{
		if(l.size()!=2&&l.size()!=3)
			throw(exception("BAD_IF"));
		std::string cond = l.car();
		boolean test = list(cond).eval();
		if(test.val==true)
			return list(l.cdr().car()).eval();
		else if(l.size()==3)
			return list(l.cdr().cdr().car()).eval();
		else return "nil";
		
	}
	
	std::map<std::string,macro> global_m_map=
	{
		{"defun",macro(defun)},
		{"if",macro(if_)},
		{"lambda",macro(lambda)}
	};
}