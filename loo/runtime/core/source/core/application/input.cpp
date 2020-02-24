#include "core/application/input.h"
#include "core/application/application.h"

loo::core::Input::Input (loo::core::Window & win)
{
	windowptr = &win;
}

loo::core::Input::~Input ()
{
}

void loo::core::Input::Init ()
{
	windowptr->OnChar ().connect (&Input::cb_CharEvent,this);

}

void loo::core::Input::CleanUp ()
{
}

void loo::core::Input::Update ()
{
}

void loo::core::Input::cb_CharEvent (Window const &, wchar_t)
{
}

void loo::core::Input::InitEvent (SAppEvent & event, SAppEventType type)
{
	memset (&event, 0, sizeof (event));
	Application* app = windowptr->GetApp ();

	event.type = type;
	event.frameCount = app->TotalNumFrames ();
	auto cfg = app->Config ();
	event.windowWidth = cfg.graphic_settings.width;
	event.windowHeight = cfg.graphic_settings.height;
	event.framebufferWidth = cfg.graphic_settings.framebufferWidth;
	event.framebufferHeight = cfg.graphic_settings.framebufferHeight;
}

