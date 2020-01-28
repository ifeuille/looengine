#include "graphicapp.h"


int main (int argc, char** argv)
{
	GraphicApp app ("graphic_test");
	app.Create ();
	app.Run ();

	return 0;
}