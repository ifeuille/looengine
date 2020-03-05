#include <iostream>

extern void FW_Test2 ();
#if defined(LOO_PLATFORM_ANDROID)
void android_main (android_app* state)
{
	LOO_UNUSED (state);
	FW_Test2 ();
}
#else
int main ()
{
	FW_Test2 ();
	return 0;
}
#endif