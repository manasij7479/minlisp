#include "function.h"
#include <sstream>
namespace mm
{
	static list bi_arg("( a1 a2 )");
	static list un_arg("( a1 )");

	std::string to_str(double d)
	{
		std::ostringstream os;
		os<<d;
		return os.str();
	}
	
	std::string plus_(list& l)
	{
		double d(0);
		for(auto x=l.begin();x!=l.end();x++)
			d+=get_num(*x);
		return to_str(d);
	}
	std::string minus_(list& l)
	{
		double d;
		d = get_num(l.car())-get_num(l.cdr().car());
		return to_str(d);
	}
	std::string mul_(list& l)
	{
		double d(1);
		for(auto x=l.begin();x!=l.end();x++)
			d*=get_num(*x);
		return to_str(d);
	}
	std::string div_(list& l)
	{
		double d;
		d = get_num(l.car())/get_num(l.cdr().car());
		return to_str(d);
	}
	std::string and__(list& l)
	{
		return (boolean(get_num(l.car()))&&boolean(get_num(l.cdr().car()))).str();
	}
	std::string or__(list& l)
	{
		return (boolean(get_num(l.car()))||boolean(get_num(l.cdr().car()))).str();
	}
	std::string not__(list& l)
	{
		return (!boolean(get_num(l.car()))).str();
	}
	std::string gt_(list& l)
	{
		double a(get_num(l.car())),b(get_num(l.cdr().car()));
		return boolean(a>b).str();
	}
	std::string lt_(list& l)
	{
		double a(get_num(l.car())),b(get_num(l.cdr().car()));
		return boolean(a<b).str();
	}
	std::string function::operator()(list& l)
	{
		std::string result;
		if(l.size()!=arg_list.size())throw(exception("Wrong no. of Args."));
		std::map<std::string,std::string> scope_map;
		auto x=arg_list.begin();auto y = l.begin();
		for(;x!=arg_list.end();x++,y++)
		{
			std::string foo(*x),bar(*y);
			scope_map[foo]=bar;
		}
		var_scope.new_local(scope_map); //Iff a more generic scope is needed 
		
		if(compiled)
		{
			result = (*body_c)(arg_list);
		}
		else
		{
			result = body_l.eval();
		}
		
		
		
		var_scope.exit_scope();
		return result;
	}

	function plus(bi_arg,plus_);
	function minus(bi_arg,minus_);
	function mul(bi_arg,mul_);
	function div(bi_arg,div_);
	function and_(bi_arg,and__);
	function or_(bi_arg,or__);
	function not_(un_arg,not__);
	function gt(bi_arg,gt_);
	function lt(bi_arg,lt_);
	std::map<std::string,function> global_f_map=
	{
		{"+",plus},
		{"-",minus},
		{"*",mul},
		{"/",div},
		{"&",and_},
		{"|",or_},
		{"!",not_},
		{">",gt},
		{"<",lt}
	};
}