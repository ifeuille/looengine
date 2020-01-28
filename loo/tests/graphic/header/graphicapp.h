#include "config.h"
#include "core/application/application.h"

class GraphicApp :public loo::core::Application
{
public:
	GraphicApp (const std::string& name);
	virtual ~GraphicApp ();
	virtual void OnCreate () override;
	virtual void OnDestroy () override;
	virtual void OnSuspend () override;
	virtual void OnResume () override;
	virtual void DoUpdateOverlay () override;
	virtual uint32_t DoUpdate (uint32_t pass) override;

private:


};