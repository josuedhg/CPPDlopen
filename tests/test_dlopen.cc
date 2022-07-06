#include <gtest/gtest.h>


#include "dlopen.h"
#include "mock_dlopen.h"

testing_c::Mock_dlopen *mock_dlopen{nullptr};
testing_c::Mock_dlsym *mock_dlsym{nullptr};
testing_c::Mock_dlerror *mock_dlerror{nullptr};
testing_c::Mock_dlclose *mock_dlclose{nullptr};

void *dlopen(const char *filename, int flag) {
	return mock_dlopen->dlopen(filename, flag);
}

void *dlsym(void *handle, const char *symbol) {
	return mock_dlsym->dlsym(handle, symbol);
}

char *dlerror(void) {
	return mock_dlerror->dlerror();
}

int dlclose(void *handle) {
	return mock_dlclose->dlclose(handle);
}


TEST(DLOpenTest, ThrowExceptionOnLoadFailure) {
	std::string error_message = "dlopen error";
	std::unique_ptr<testing_c::Mock_dlerror> mock_dlerr(mock_dlerror = new testing_c::Mock_dlerror(const_cast<char *>(strdup(error_message.c_str()))));
	std::unique_ptr<testing_c::Mock_dlopen> mock(mock_dlopen = new testing_c::Mock_dlopen(NULL));

	mock->expect_filename("/path/to/lib");
	mock->expect_flag(RTLD_LAZY);
	try {
		DLOpen("/path/to/lib");
	} catch (std::runtime_error &e) {
		ASSERT_STREQ(e.what(), error_message.c_str());
	}
}

TEST(DLOpenTest, LoadLibrary) {
	void *fake_handle = reinterpret_cast<void *>(1);
	std::unique_ptr<testing_c::Mock_dlopen> mock(mock_dlopen = new testing_c::Mock_dlopen(fake_handle));
	std::unique_ptr<testing_c::Mock_dlclose> mock_close(mock_dlclose = new testing_c::Mock_dlclose(0));

	mock->expect_filename("/path/to/lib");
	mock->expect_flag(RTLD_LAZY);
	mock_close->expect_handle(fake_handle);

	DLOpen dlopen("/path/to/lib");
}

TEST(DLOpenTest, ThrowExceptionOnSymbolNotFound) {
	void *fake_handle = reinterpret_cast<void *>(1);
	std::string error_message = "dlsym error";
	std::unique_ptr<testing_c::Mock_dlerror> mock_dlerr(mock_dlerror = new testing_c::Mock_dlerror(const_cast<char *>(strdup(error_message.c_str()))));
	std::unique_ptr<testing_c::Mock_dlopen> mock(mock_dlopen = new testing_c::Mock_dlopen(fake_handle));
	std::unique_ptr<testing_c::Mock_dlsym> mock_sym(mock_dlsym = new testing_c::Mock_dlsym(NULL));
	std::unique_ptr<testing_c::Mock_dlclose> mock_close(mock_dlclose = new testing_c::Mock_dlclose(0));

	mock->expect_filename("/path/to/lib");
	mock->expect_flag(RTLD_LAZY);
	mock_sym->expect_handle(fake_handle);
	mock_sym->expect_symbol("symbol");
	mock_close->expect_handle(fake_handle);

	DLOpen dlopen("/path/to/lib");
	void *symbol = NULL;
	try {
		symbol = dlopen.getSymbol("symbol");
	} catch (std::runtime_error &e) {
		ASSERT_STREQ(e.what(), error_message.c_str());
	}
	ASSERT_EQ(symbol, (void *)NULL);
}

TEST(DLOpenTest, GetSymbol) {
	void *fake_handle = reinterpret_cast<void *>(1);
	void *fake_symbol = reinterpret_cast<void *>(2);
	std::unique_ptr<testing_c::Mock_dlopen> mock(mock_dlopen = new testing_c::Mock_dlopen(fake_handle));
	std::unique_ptr<testing_c::Mock_dlsym> mock_sym(mock_dlsym = new testing_c::Mock_dlsym(fake_symbol));
	std::unique_ptr<testing_c::Mock_dlclose> mock_close(mock_dlclose = new testing_c::Mock_dlclose(0));

	mock->expect_filename("/path/to/lib");
	mock->expect_flag(RTLD_LAZY);
	mock_sym->expect_handle(fake_handle);
	mock_sym->expect_symbol("symbol");
	mock_close->expect_handle(fake_handle);

	DLOpen dlopen("/path/to/lib");
	void *symbol = dlopen.getSymbol("symbol");
	ASSERT_EQ(symbol, fake_symbol);
}

int main()
{
	::testing::InitGoogleTest();
	return RUN_ALL_TESTS();
}
