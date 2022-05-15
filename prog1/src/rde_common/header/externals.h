#pragma once
#include "global.h"

extern	void				tracelog(std::string msg);
extern  void				throwError(std::string msg);

extern	std::string			format(const char8* fmt, ...);
extern	void				formatExt(std::string* str, const char8* fmt, ...);
extern	std::string	        trim(const std::string& t );