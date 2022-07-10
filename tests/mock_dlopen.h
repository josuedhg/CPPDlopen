#ifndef __MOCK_DLOPEN_H__
#define __MOCK_DLOPEN_H__

#include <gtest/gtest.h>

namespace testing_c {
class Mock_dlopen {
	void *return_value;
	const char *filename;
	int flag;
public:
	Mock_dlopen(void *return_value): return_value(return_value) {}
	void *dlopen(const char *filename, int flag) {
		EXPECT_STRCASEEQ(filename, this->filename);
		EXPECT_EQ(flag, this->flag);
		return this->return_value;
	}
	void expect_filename(const char *filename) {
		this->filename = filename;
	}
	void expect_flag(int flag) {
		this->flag = flag;
	}
};

class Mock_dlsym {
	void *return_value;
	void *handle;
	const char *symbol;
public:
	Mock_dlsym(void *return_value): return_value(return_value) {}
	void *dlsym(void *handle, const char *symbol) {
		EXPECT_EQ(handle, this->handle);
		EXPECT_STREQ(symbol, this->symbol);
		return this->return_value;
	}
	void expect_handle(void *handle) {
		this->handle = handle;
	}
	void expect_symbol(const char *symbol) {
		this->symbol = symbol;
	}
};

class Mock_dlerror {
	char *return_value;
public:
	Mock_dlerror(char *return_value): return_value(return_value) {}
	char *dlerror() {
		return this->return_value;
	}
};

class Mock_dlclose {
	int return_value;
	void *handle;
public:
	Mock_dlclose(int return_value): return_value(return_value) {}
	int dlclose(void *handle) {
		EXPECT_EQ(handle, this->handle);
		return this->return_value;
	}
	void expect_handle(void *handle) {
		this->handle = handle;
	}
};
};

#endif /* end of include guard: __MOCK_DLOPEN_H__ */
