#include <stdio.h>

typedef struct
{
	int a;
	int b;
}	Context;

Context *context(void)
{
	static Context ctx = {0};
	return (&ctx);
}

int main(int argc, char const *argv[])
{
	Context *ctx = context();
	ctx->a = 10;
	ctx->b = 5; // Setting "global" variables

	printf("a = %d, b = %d\n", context()->a, context()->b); // Getting globals
	return 0;
}
