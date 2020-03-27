#include "graphicapp.h"
#include "global/types.h"
#include "global/thread.h"

int main (int argc, char** argv)
{
	LOO_UNUSED (argc);
	LOO_UNUSED (argv);
	loo::SetCurrentThreadName ("hehe");
	loo::core::ContextConfig config = loo::core::ContextConfig();
	config.graphic_settings.width = 800;
	config.graphic_settings.width = 600;

	GraphicApp app ("graphic_test",loo::core::MainAppID, config);
	app.Create ();
	app.Run ();

	return 0;
}