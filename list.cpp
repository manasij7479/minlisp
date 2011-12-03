#include<sstream>
#include "env.h"
#include "list.h"
#include "function.h"
#include "macro.h"
#include<sstream>

namespace mm
{
	std::string list::eval()
	{
		if(size_val==0)return "nil";
		
		std::string name = car(),temp;
		
		std::istringstream is1(name); 
		is1>>temp;
		if(temp=="(")
			name = list(name).eval();
		
		list args = cdr();
		std::istringstream is(name);
		double d;
		
		auto v = var_scope.find(name);
		if(v!=nullptr)return *v;
		
		auto f = f_scope.find(name);
		if(f!=nullptr)
		{	
			for(auto x=args.begin();x!=args.end();x++)
			{
				std::string val = *x,temp;
				std::istringstream is2(val);
				is2>>temp;
				if(temp=="(")
				{
					list l(val);
					*x = l.eval();
				}
			}
			return (*f)(args);
		}
		auto m = m_scope.find(name);
		if(m!=nullptr)return (*m)(args);


		else if(is>>d)return name;
			
		else throw(exception(name+" : name not found."));
	}
	list::list(const std::string& s)
	{
		begin_sn = new node();
		end_ = begin_sn;
		end_->next=new node();
		size_val=0;

		std::istringstream is(s);
		int nest(0);
		std::string temp;
		std::string result;

		is>>temp;
		if(temp!="(")throw(exception("BAD_LIST"));
		while(is>>temp)
		{
			if(temp=="(")
			{
				nest++;
				result+=(" "+temp);
			}
			else if(temp==")")
			{
				nest--;
				result+=(" "+temp);
				if(nest==0){push_back(result);result="";}
			}
			else
			{
				if(nest!=0){result+=(" "+temp);}
				else push_back(temp);
			}
		}
		if(temp!=")")throw(exception("BAD_LIST"));
		 
	}
	std::string list::car()
	{
		return begin_sn->next->val;
	}
	list list::cdr()
	{
		node* new_sentinel = new node();
		new_sentinel->next = begin_sn->next->next;
		list l = list(new_sentinel,end_,size_val-1);
		return l;
		//BEWARE: Changing the cdr list will modify the original list
	}
	
}