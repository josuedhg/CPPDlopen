#include <memory>
#include <stdio.h>

#include "polygon.h"
#include "dlopen.h"

int main(void)
{
	DLOpen dlopen("./triangle.so");
	create_t *create = (create_t *)dlopen.getSymbol("create");

	std::unique_ptr<Polygon> p(create(3.0));
	printf("%f\n", p->area());

	return 0;
}
