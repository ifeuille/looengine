#include "graphicapp.h"
#include "global/types.h"
#include "global/thread.h"

int main (int argc, char** argv)
{
	LOO_UNUSED (argc);
	LOO_UNUSED (argv);
	loo::SetCurrentThreadName ("hehe");
	//GraphicApp app ("graphic_test");
	//app.Create ();
	//app.Run ();

	return 0;
}