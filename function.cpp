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
	
	std::string plus(list& l)
	{
		double d(0);
		for(auto x=l.begin();x!=l.end();x++)
			d+=get_num(*x);
		return to_str(d);
	}
	std::string minus(list& l)
	{
		double d;
		d = get_num(l.car())-get_num(l.cdr().car());
		return to_str(d);
	}
	std::string mul(list& l)
	{
		double d(1);
		for(auto x=l.begin();x!=l.end();x++)
			d*=get_num(*x);
		return to_str(d);
	}
	std::string div(list& l)
	{
		double d;
		d = get_num(l.car())/get_num(l.cdr().car());
		return to_str(d);
	}
	std::string and_(list& l)
	{
		return (boolean(get_num(l.car()))&&boolean(get_num(l.cdr().car()))).str();
	}
	std::string or_(list& l)
	{
		return (boolean(get_num(l.car()))||boolean(get_num(l.cdr().car()))).str();
	}
	std::string not_(list& l)
	{
		return (!boolean(get_num(l.car()))).str();
	}
	std::string gt(list& l)
	{
		double a(get_num(l.car())),b(get_num(l.cdr().car()));
		return boolean(a>b).str();
	}
	std::string lt(list& l)
	{
		double a(get_num(l.car())),b(get_num(l.cdr().car()));
		return boolean(a<b).str();
	}
	std::string equ(list& l)
	{
		double a(get_num(l.car())),b(get_num(l.cdr().car()));
		return boolean(a==b).str();		
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
		var_scope.new_local(scope_map);
		
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

	std::map<std::string,function> global_f_map=
	{
		{"+",function(bi_arg,plus)},
		{"-",function(bi_arg,minus)},
		{"*",function(bi_arg,mul)},
		{"/",function(bi_arg,div)},
		{"&",function(bi_arg,and_)},
		{"|",function(bi_arg,or_)},
		{"!",function(un_arg,not_)},
		{">",function(bi_arg,gt)},
		{"<",function(bi_arg,lt)},
		{"=",function(bi_arg,equ)}
	};
}