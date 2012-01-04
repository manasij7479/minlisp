#include<sstream>
#include "env.h"
#include "list.h"
#include "function.h"
#include "macro.h"
#include<sstream>
#include<thread>
#include<algorithm>
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
		if(v!=nullptr)return *v; //(TEMPORARY)
		
		auto f = f_scope.find(name);
		if(f!=nullptr) //This block 'simplifies' the args to a functio
		{
// 			for(auto x=args.begin();x!=args.end();x++)
// 			{
// 				list l;
// 				if(is_list(*x,l)) *x = l.eval();
// 			} /*Version without threads*/
			std::vector<std::thread> threads;
			for(auto x=args.begin();x!=args.end();x++)
			{
				threads.push_back
				(
					std::thread
					(
						[](list::iterator li)
						{
							list l;
							if(is_list(*li,l))
								*li = l.eval();
						},
						x
					)
				);
			}
			for(auto& t:threads)t.join();

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
		if(temp!="(")throw(exception("BAD_LIST: "+s));
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
		if(temp!=")")throw(exception("BAD_LIST: "+s));
		 
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