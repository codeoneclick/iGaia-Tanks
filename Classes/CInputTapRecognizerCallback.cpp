//
//  CInputTapRecognizerCallback.cpp
//  iGaia-CartoonPanzers
//
//  Created by Sergey Sergeev on 3/27/13.
//
//

#include "CInputTapRecognizerCallback.h"

void CInputTapRecognizerCallback::ConnectInputTapRecognizerDidPressedCallback(const __TAP_RECOGNIZER_DID_PRESSED &_listener)
{
    assert(_listener != nullptr);
    m_inputTapRecognizerDidPressedCallback = _listener;
}

void CInputTapRecognizerCallback::ConnectInputTapRecognizerDidMovedCallback(const __TAP_RECOGNIZER_DID_MOVED &_listener)
{
    assert(_listener != nullptr);
    m_inputTapRecognizerDidMovedCallback = _listener;
}

void CInputTapRecognizerCallback::ConnectInputTapRecognizerDidReleasedCallback(const __TAP_RECOGNIZER_DID_RELEASED &_listener)
{
    assert(_listener != nullptr);
    m_inputTapRecognizerDidReleasedCallback = _listener;
}

void CInputTapRecognizerCallback::DispatchInputTapRecognizerDidPressed(i32 _x, i32 _y)
{
    assert(m_inputTapRecognizerDidPressedCallback != nullptr);
    m_inputTapRecognizerDidPressedCallback(_x, _y);
}

void CInputTapRecognizerCallback::DispatchInputTapRecognizerDidMoved(i32 _x, i32 _y)
{
    assert(m_inputTapRecognizerDidMovedCallback != nullptr);
    m_inputTapRecognizerDidMovedCallback(_x, _y);
}

void CInputTapRecognizerCallback::DispatchInputTapRecognizerDidReleased(i32 _x, i32 _y)
{
    assert(m_inputTapRecognizerDidReleasedCallback != nullptr);
    m_inputTapRecognizerDidReleasedCallback(_x, _y);
}

CInputTapRecognizerCallback_INTERFACE::CInputTapRecognizerCallback_INTERFACE(void)
{
    ConnectCallbacks();
}

void CInputTapRecognizerCallback_INTERFACE::ConnectCallbacks(void)
{
    m_inputTapRecognizerCallback.ConnectInputTapRecognizerDidPressedCallback(std::bind(&CInputTapRecognizerCallback_INTERFACE::OnInputTapRecognizerPressed, this, std::placeholders::_1, std::placeholders::_2));
    m_inputTapRecognizerCallback.ConnectInputTapRecognizerDidMovedCallback(std::bind(&CInputTapRecognizerCallback_INTERFACE::OnInputTapRecognizerMoved, this, std::placeholders::_1, std::placeholders::_2));

    m_inputTapRecognizerCallback.ConnectInputTapRecognizerDidReleasedCallback(std::bind(&CInputTapRecognizerCallback_INTERFACE::OnInputTapRecognizerReleased, this, std::placeholders::_1, std::placeholders::_2));

}
