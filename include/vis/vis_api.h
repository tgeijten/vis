#pragma once

#if defined(_MSC_VER)
#	ifdef VIS_EXPORTS
#		define VIS_API __declspec(dllexport)
#	else
#		define VIS_API __declspec(dllimport)
#	endif
#else
#	define VIS_API
#endif
