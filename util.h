/**
 * Scope, boolean and exception lives here.
 */
#ifndef SCOPE
#define SCOPE
#include<vector>
#include<map>
#include<sstream>

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
        void exit_scope(){data.pop_back();};
    };
	extern scope<std::string> var_scope;
	/*Converts a string to a double
	 * If the string is an identifier....
	 * it fetches the value from the scope object supplied. 
	 */
	double get_num(const std::string& s,scope<std::string>& ss=var_scope);

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