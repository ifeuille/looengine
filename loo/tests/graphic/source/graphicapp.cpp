#include "graphicapp.h"

GraphicApp::GraphicApp (const std::string & name)
	:loo::core::Application(name)
{
}

GraphicApp::~GraphicApp ()
{
}

void GraphicApp::OnCreate ()
{
}

void GraphicApp::OnDestroy ()
{
}

void GraphicApp::OnSuspend ()
{
}

void GraphicApp::OnResume ()
{
}

void GraphicApp::DoUpdateOverlay ()
{

}

uint32_t GraphicApp::DoUpdate (uint32_t pass)
{
	return 0;
}
