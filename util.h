/**
 * Scope, boolean and exception lives here.
 */
#ifndef SCOPE
#define SCOPE
#include<vector>
#include<map>
#include<sstream>
#include<iostream>
#include "list.h"
namespace mm
{
    template<typename T>
    class scope
    {
        std::vector< std::map<std::string,T> > data;
    public:
        T* find(const std::string& s)
        {
            for(auto m=data.rbegin();m!=data.rend();m++)
            {
                auto p = m->find(s);
                if(p!=m->end())return &(p->second);
            }
            return nullptr;
        };
        void new_local(const std::map<std::string,T>& sm){data.push_back(sm);};
		void new_global_val(std::string s,T t )
		{
			(data[0])[s]=t;
		}
		void new_local_val(std::string s,T t )
		{
			data.back()[s]=t;
		}
        void exit_scope(){data.pop_back();};
		int get_local_num()//Number of items on the scope on the 'back'
		{
			return data.back().size();
		}
		int size(){return data.size();}
		void debug_print()
		{
			for(auto m:data)
			{
				for(auto p:m)
				{
					std::cout<<"("<<p.first<<","<<p.second<<") ";
				}
				
			}
			std::cout<<"Size="<<size()<<std::endl;
		}
    };
	/*Converts a string to a double
	 * If the string is an identifier....
	 * it fetches the value from the scope object supplied.
	 */
	extern scope<std::string> var_scope;

	double get_num(const std::string& s,scope<std::string>& ss=var_scope);
	std::string get_data_str(const std::string& s,scope<std::string>& ss=var_scope);
	list get_data_list(const std::string& s,scope<std::string>& ss=var_scope);

	class boolean
	{
	public:
		bool val;
		std::string str(){return val?"t":"nil";};
		template<typename T>boolean(const T& t){val=!(t==T());}
		boolean(const std::string& s)
		{
			std::istringstream is(s);
			double d;
			if(is>>d)
			{
				if(d==double())val=false;
				else val=true;	
			}
			else val= !(s=="Nil"||s=="nil"||s=="NIL"||s=="");

		}
		boolean(const bool& b)
		{
			val=b;
		}
		boolean operator&&(boolean b){return boolean(val&&b.val);}
		boolean operator||(boolean b){return boolean(val||b.val);}
		boolean operator!(){return boolean(!val);}
		
	};
	class exception
	{
		std::string data;
	public:
		exception(std::string s):data(s){};
		std::string what(){return data;}
	};
}
#endif