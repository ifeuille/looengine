#include "graphicapp.h"
#include "global/types.h"

int main (int argc, char** argv)
{
	LOO_UNUSED (argc);
	LOO_UNUSED (argv);
	GraphicApp app ("graphic_test");
	app.Create ();
	app.Run ();

	return 0;
}