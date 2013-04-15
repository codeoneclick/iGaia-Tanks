
#ifndef ILoadOperation_h
#define ILoadOperation_h

#include "HCommon.h"
#include "IResource.h"
#include "CResourceLoading_INTERFACE.h"

class ILoadOperation_INTERFACE;
typedef std::shared_ptr<ILoadOperation_INTERFACE> TSharedPtrLoadOperation;

class ILoadOperation_INTERFACE
{
private:

protected:

    std::string m_name;
    E_PARSER_STATUS m_status;
    std::set<const CResourceLoadingCommands*> m_commands;
    
    void Register_Resource(IResource_INTERFACE* _resource);

public:
    
    ILoadOperation_INTERFACE(void);
    virtual ~ILoadOperation_INTERFACE(void) {};

    virtual void Load(const std::string& _filename) = 0;
    virtual IResource_INTERFACE* Link(void) = 0;

    inline E_PARSER_STATUS Get_Status(void)
    {
        return m_status;
    };

    inline void Register_ResourceLoadingCommands(const CResourceLoadingCommands* _commands)
    {
        m_commands.insert(_commands);
    };

    inline void Unregister_ResourceLoadingCommands(const CResourceLoadingCommands* _commands)
    {
        m_commands.erase(_commands);
    };

	void Execute_CallbackCommands(TSharedPtrResource _resource);
};

#endif 
