#include "macro.h"
#include "util.h"
#include "function.h"
#include "env.h"
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
	std::string defun_(list& l)
	{
		if(l.size()!=3)throw(exception("BAD_DEFUN"));
		std::string name = l.car();
		list arg_list = list(l.cdr().car());
		list body_list = list(l.cdr().cdr().car());
		f_scope.new_global_val(name,function(arg_list,body_list));
		return name;
	}

	std::string if__(list& l)
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
	
	macro defun(defun_);
	macro if_(if__);
	
	std::map<std::string,macro> global_m_map=
	{
		{"defun",defun},
		{"if",if_}
	};
}