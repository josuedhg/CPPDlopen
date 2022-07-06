#ifndef __DLOPEN_H__
#define __DLOPEN_H__

#include <dlfcn.h>
#include <string>

class DLOpen {
	void *handle;
public:
	DLOpen(std::string path, int flag = RTLD_LAZY);
	~DLOpen();
	void *getSymbol(std::string name);
};

#endif /* end of include guard: __DLOPEN_H__ */
