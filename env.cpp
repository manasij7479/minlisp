#include "env.h"
#include<iostream>
namespace mm
{
	scope<std::string> var_scope;
	scope<function> f_scope;
	scope<macro> m_scope;
}