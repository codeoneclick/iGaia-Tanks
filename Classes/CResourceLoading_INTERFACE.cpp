
#include "CResourceLoading_INTERFACE.h"

void CResourceLoadingCommands::Register_OnResourceLoadedCallback(const __ON_RESOURCE_LOADED_CALLBACK& _callback)
{
	assert(_callback != nullptr);
	m_onResourceLoadedCallback = _callback;
}

void CResourceLoadingCommands::Execute_OnResourceLoadedCallback(TSharedPtrResource _resource) const
{
	assert(m_onResourceLoadedCallback != nullptr);
    m_onResourceLoadedCallback(_resource);
}


CResourceLoading_INTERFACE::CResourceLoading_INTERFACE(void)
{
	RegisterResourceLoadingCommands();
}

void CResourceLoading_INTERFACE::RegisterResourceLoadingCommands(void)
{
	m_resourceLoadingCommands.Register_OnResourceLoadedCallback(std::bind(&CResourceLoading_INTERFACE::OnResourceLoaded, this, std::placeholders::_1));
}