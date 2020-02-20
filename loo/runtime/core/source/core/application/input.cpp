#include "core/application/input.h"

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
