#include <stdexcept>

#include "dlopen.h"

DLOpen::DLOpen(std::string path, int flag) {
	this->handle = dlopen(path.c_str(), RTLD_LAZY);
	if (this->handle == NULL) {
		throw std::runtime_error(dlerror());
	}
}

void *DLOpen::getSymbol(std::string name) {
	void *symbol = dlsym(this->handle, name.c_str());
	if (symbol == NULL) {
		throw std::runtime_error(dlerror());
	}
	return symbol;
}

void *DLOpen::getSymbolNext(std::string name) {
	void *symbol = dlsym(RTLD_NEXT, name.c_str());
	if (symbol == NULL) {
		throw std::runtime_error(dlerror());
	}
	return symbol;
}

void *DLOpen::getSymbolDefault(std::string name) {
	void *symbol = dlsym(RTLD_DEFAULT, name.c_str());
	if (symbol == NULL) {
		throw std::runtime_error(dlerror());
	}
	return symbol;
}

DLOpen::~DLOpen() {
	dlclose(this->handle);
}
