//
//  CGuiView.h
//  iGaia-CartoonPanzers
//
//  Created by Sergey Sergeev on 3/28/13.
//
//

#ifndef IUIView_h
#define IUIView_h

#include "HCommon.h"

class IUIView_INTERFACE
{
private:

protected:

    Rocket::Core::ElementDocument* m_document;

public:

    IUIView_INTERFACE(void);
    ~IUIView_INTERFACE(void);

    inline void Set_Document(Rocket::Core::ElementDocument* _document)
    {
        assert(_document != nullptr);
        m_document = _document;
    };
};

#endif 
