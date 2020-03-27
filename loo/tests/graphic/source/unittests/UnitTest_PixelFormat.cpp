
#include "vkfg/fg/enumutils.h"
#include "UnitTest_Common.h"


static void PixelFormat_Test1 ()
{
	for (EPixelFormat fmt = EPixelFormat(0); fmt < EPixelFormat::_Count; fmt = EPixelFormat(uint(fmt) + 1))
	{
		auto&	info = EPixelFormat_GetInfo( fmt );
		TEST( info.format == fmt );
	}
}


extern void UnitTest_PixelFormat ()
{
	PixelFormat_Test1();
	LOO_LOGI( "UnitTest_PixelFormat - passed" );
}
