/*!
* @file IInkRecognitionEventsImpl.h
* 
* @brief The template is derived from the ATL's IDispEventSimpleImpl to implement a sink for the 
*        IInkRecognitionEvents, fired by the InkCollector object Since the IDispEventSimpleImpl doesn't require 
*        to supply implementation code for every event, this template has a handler for the Gesture event only.
*
* Copyright (C) 2009, LZT Corporation.
* 
* @author Li Hong
* @date 2009/10/19 12:00
* @version 1.0.0
*/

#ifdef __cplusplus
#ifndef _IInkRecognitionEventsImplE_H_
#define _IInkRecognitionEventsImplE_H_

#include "SdkInkCommon.h"

BEGIN_NAMESPACE_COMMON

#define SINK_ID                 1
#define COUNT_RECOG_EVENTS      2

template <class T>
class ATL_NO_VTABLE IInkRecognitionEventsImpl : 
    public IDispEventSimpleImpl<SINK_ID, IInkRecognitionEventsImpl<T>, &(__uuidof(_IInkRecognitionEvents))>
{
public:
    // ATL structure with the type information for the event, 
    // handled in this template. (Initialized in the AdvReco.cpp)
    static const _ATL_FUNC_INFO mc_AtlFuncInfo[COUNT_RECOG_EVENTS];

    BEGIN_SINK_MAP(IInkRecognitionEventsImpl)
        SINK_ENTRY_INFO(SINK_ID, 
        __uuidof(_IInkRecognitionEvents), // DIID__IInkRecognitionEvents will cause complier error 2970 
        DISPID_IRERecognitionWithAlternates,
        &RecognitionWithAlternates, 
        const_cast<_ATL_FUNC_INFO*>(&mc_AtlFuncInfo[0]))
    END_SINK_MAP()

    /*!
    * @brief Occurs when the InkRecognizerContext has generated results after calling the 
    *        BackgroundRecognizeWithAlternates method.
    */
    void __stdcall RecognitionWithAlternates(
    IInkRecognitionResult* pIInkRecoResult, 
    VARIANT vCustomParam, 
    InkRecognitionStatus RecognitionStatus)
    {
        T* pT = static_cast<T*>(this);
        pT->OnRecognitionWithAlternates(pIInkRecoResult, vCustomParam, RecognitionStatus);
    }
};

END_NAMESPACE_COMMON

#endif // _IInkRecognitionEventsImplE_H_
#endif // __cplusplus
