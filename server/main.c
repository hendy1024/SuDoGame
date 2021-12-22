#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

#include "call.h"

int main() {
	void* handle = dlopen("./libsudo.so", RTLD_LAZY);
	if (handle == NULL) {
		printf("dlopen: %s\n", dlerror());
		return -1;
	}
	typedef void (*TestFunc)(int a, int b, int c);
	
	TestFunc func = (TestFunc)dlsym(handle, "NewGame");
	if (func == NULL) {
		printf("dlsym: %s\n", dlerror());
		return -1;
	}
	
	int a = 1;
	int b = 2;
	int c = 40;
	//sprintf("add %d+%d=%d\n", a, b, c, add(a, b, c));
	func(a, b, c);
	dlclose(handle);
	return 0;
}
