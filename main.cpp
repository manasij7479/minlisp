#include<iostream>
#include "list.h"
#include "util.h"
#include "env.h"
#include "function.h"
#include "repl.h"
#include<iostream>
int main()
{
	mm::repl main_loop;
	return main_loop();
// 	std::cout<<foo(0,0).str();
}

// @
/**
 * TODO
 * 1) Boolean class
 * 2) Builtin Functions and macros
 * 3) Proper Exceptions
*/