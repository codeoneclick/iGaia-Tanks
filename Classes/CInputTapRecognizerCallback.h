//
//  CInputTapRecognizerCallback.h
//  iGaia-CartoonPanzers
//
//  Created by Sergey Sergeev on 3/27/13.
//
//

#ifndef CInputTapRecognizerCallback_h
#define CInputTapRecognizerCallback_h

#include "HCommon.h"

typedef std::function<void(i32 _x, i32 _y)> __TAP_RECOGNIZER_DID_PRESSED;
typedef std::function<void(i32 _x, i32 _y)> __TAP_RECOGNIZER_DID_MOVED;
typedef std::function<void(i32 _x, i32 _y)> __TAP_RECOGNIZER_DID_RELEASED;

class CInputTapRecognizerCallback final
{

private:

    friend class CInputTapRecognizerCallback_INTERFACE;
    __TAP_RECOGNIZER_DID_PRESSED m_inputTapRecognizerDidPressedCallback;
    __TAP_RECOGNIZER_DID_MOVED m_inputTapRecognizerDidMovedCallback;
    __TAP_RECOGNIZER_DID_RELEASED m_inputTapRecognizerDidReleasedCallback;

protected:

    CInputTapRecognizerCallback(void) {};

    void ConnectInputTapRecognizerDidPressedCallback(const __TAP_RECOGNIZER_DID_PRESSED& _listener);
    void ConnectInputTapRecognizerDidMovedCallback(const __TAP_RECOGNIZER_DID_MOVED& _listener);
    void ConnectInputTapRecognizerDidReleasedCallback(const __TAP_RECOGNIZER_DID_RELEASED& _listener);

public:

    ~CInputTapRecognizerCallback(void) {};

    void DispatchInputTapRecognizerDidPressed(i32 _x, i32 _y);
    void DispatchInputTapRecognizerDidMoved(i32 _x, i32 _y);
    void DispatchInputTapRecognizerDidReleased(i32 _x, i32 _y);
};

class CInputTapRecognizerCallback_INTERFACE
{
private:

    CInputTapRecognizerCallback m_inputTapRecognizerCallback;
    void ConnectCallbacks(void);

protected:

    CInputTapRecognizerCallback_INTERFACE(void);

    virtual void OnInputTapRecognizerPressed(i32 _x, i32 _y) = 0;
    virtual void OnInputTapRecognizerMoved(i32 _x, i32 _y) = 0;
    virtual void OnInputTapRecognizerReleased(i32 _x, i32 _y) = 0;

public:

    virtual ~CInputTapRecognizerCallback_INTERFACE(void) {};

    inline CInputTapRecognizerCallback* Get_Commands(void)
    {
        return &m_inputTapRecognizerCallback;
    };
};


#endif 
