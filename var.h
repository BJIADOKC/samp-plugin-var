#pragma once



#include <iostream>
#include <string>
#include <sstream>

#include <boost/unordered_map.hpp>

#define HAVE_STDINT_H

#include "SDK/plugin.h"

#include "natives.h"





#define PLUGIN_VERSION "1.0.1"

#define arguments(n) \
	(params[0] == (n << 2))





typedef void (*logprintf_t)(char *format, ...);





struct amxVars
{
	long integer;
	float floating;

	std::string string;
};