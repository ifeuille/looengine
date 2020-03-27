#include <iostream>
#include "global/global.h"

//#ifdef LOO_PLATFORM_ANDROID
//extern void FW_Test2 (struct android_app* app);
//extern void android_main (struct android_app* app)
//{
//	FW_Test2 (app);
//}
//int main ()
//{
//	return 0;
//}
//#else
extern void FW_Test2 ();
int main ()
{
	FW_Test2 ();
	return 0;
}
//#endif
