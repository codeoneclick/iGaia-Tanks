
#include "CResourceLoading_INTERFACE.h"

void CResourceLoadingCommands::Register_OnResourceLoadCallback(const __ON_RESOURCE_DID_LOAD_CALLBACK& _callback)
{
	assert(_callback != nullptr);
	m_onResourceDidLoadCallback = _callback;
}

void CResourceLoadingCommands::Execute_OnResourceDidLoadCallback(TSharedPtrResource _resource)
{
	assert(m_onResourceDidLoadCallback != nullptr);
    m_onResourceDidLoadCallback(_resource);
}


CResourceLoading_INTERFACE::CResourceLoading_INTERFACE(void)
{
	RegisterCommands();
}

void CResourceLoading_INTERFACE::RegisterCommands(void)
{
	m_commands.Register_OnResourceLoadCallback(std::bind(&CResourceLoading_INTERFACE::OnResourceDidLoad, this, std::placeholders::_1));
}