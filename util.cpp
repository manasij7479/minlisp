#include "util.h"
namespace mm
{
	double get_num(const std::string& s,scope<std::string>& ss)
	{
		std::string numstr(s);
		std::istringstream is(s);
		double d;
		if(s=="t")return 1;else if (s=="nil")return 0;
		if(is>>d)
			return d;
		else while(true)
		{
			std::string* x = ss.find(numstr);
			if(x!=nullptr)numstr=*x;
			else break;// throw(std::string(numstr +"Not found"));//change later
		}
		std::istringstream is_2(numstr);
		if(is_2>>d)
			return d;
		else if(numstr=="t")return 1;
		else if (numstr=="nil")return 0;
		else throw(exception(numstr+" is not a number."));//change later

	}
	std::string get_data_str(const std::string& s,scope<std::string>& ss)
	{
		if(s[0]=='`')return s.substr(1,s.size()-1);
		auto v = ss.find(s);
		if(v!=nullptr)return get_data_str(*v);
		else throw(exception(s+" is not a data string."));
	}
	list get_data_list(const std::string& s,scope<std::string>& ss)
	{
		return list(get_data_str(s,ss));
	}
	bool is_list(std::string s, list& l)
	{
		try{l=list(s);}
		catch(exception e){if(e.what()==std::string("BAD_LIST: "+s))return false;}
		return true;
	}
	
}