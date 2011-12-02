/**
 * Builtin Macros...(User defined macros not yet supported)
 */
#ifndef MACRO_H
#define MACRO_H
#include "list.h"
#include<map>
namespace mm
{
	typedef std::string (*m_ptr)(list& l);
	class macro
	{
		m_ptr body;
	public:
		macro(m_ptr b_):body(b_){};
		std::string operator()(list& l);
	};
	extern std::map<std::string,macro> global_m_map;
}

#endif