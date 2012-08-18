#ifndef Serializable_h__
#define Serializable_h__

#include "Prec.h"

struct Serializable
{
    virtual void            Serialize(DynamicMemoryStream& dms)
    {
        APP_API_ASSERT(FALSE && "This object is not support serialization");
    };
    
    virtual size_t          Deserialize(MemoryStream& ms)
    { 
        APP_API_ASSERT(FALSE && "This object is not support serialization"); return 0;
    }
};

#endif // Serializable_h__
