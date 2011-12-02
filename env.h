/**
 * Contains the global maps to locate identifiers
 */
#ifndef ENV_H
#define ENV_H
#include "util.h"
#include<string>
#include"function.h"
#include"macro.h"
namespace mm
{
	extern scope<std::string> var_scope;
	extern scope<function> f_scope;
	extern scope<macro> m_scope;
}
#endif