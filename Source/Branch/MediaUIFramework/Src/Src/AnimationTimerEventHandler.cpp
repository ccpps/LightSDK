/*!
* @file AnimationTimerEventHandler.cpp 
* 
* @brief This file defines the event handler of animation timer.
* 
* Copyright (C) 2010, Toshiba Corporation.
* 
* @author Qiao LiYun
* @date 2011/02/15
*/

#include "AnimationTimerEventHandler.h"

//////////////////////////////////////////////////////////////////////////

AnimationTimerEventHandler::AnimationTimerEventHandler() : 
                                        m_pAnimation(NULL),
                                        m_lRefCount(1)
{
}

//////////////////////////////////////////////////////////////////////////

AnimationTimerEventHandler::~AnimationTimerEventHandler()
{
}

//////////////////////////////////////////////////////////////////////////

VOID AnimationTimerEventHandler::AddListener(IAnimationTimerListener *pListener, Animation *pAnimation)
{
    this->m_pAnimation = pAnimation;

    if(NULL != pListener)
    {
        BOOL bFind = FALSE;
        for(vector<IAnimationTimerListener*>::iterator iter = m_vecAnimationTimerListener.begin();
            iter != m_vecAnimationTimerListener.end();
            ++iter)
        {
            if(*iter == pListener)
            {
                bFind = TRUE;
                break;
            }
        }

        if(!bFind)
        {
            m_vecAnimationTimerListener.push_back(pListener);
        }
    }
}

//////////////////////////////////////////////////////////////////////////

void AnimationTimerEventHandler::RemoveListener(IAnimationTimerListener *pListener)
{
    if(NULL != pListener)
    {
        for(vector<IAnimationTimerListener*>::iterator iter = m_vecAnimationTimerListener.begin();
            iter != m_vecAnimationTimerListener.end();
            ++iter)
        {
            if(*iter == pListener)
            {
                m_vecAnimationTimerListener.erase(iter);
                break;
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////////

HRESULT AnimationTimerEventHandler::OnPreUpdate()
{
    return S_OK;
}

//////////////////////////////////////////////////////////////////////////

HRESULT AnimationTimerEventHandler::OnPostUpdate()
{
    for(vector<IAnimationTimerListener*>::iterator iter = m_vecAnimationTimerListener.begin();
        iter != m_vecAnimationTimerListener.end();
        ++iter)
    {
        if(*iter != NULL)
        {
            (*iter)->OnAnimationTimerUpdate(m_pAnimation);
            break;
        }
    }

    return S_OK;
}

//////////////////////////////////////////////////////////////////////////

HRESULT AnimationTimerEventHandler::OnRenderingTooSlow( UINT32 /*fps*/ )
{
    return S_OK;
}

//////////////////////////////////////////////////////////////////////////

HRESULT AnimationTimerEventHandler::QueryInterface( REFIID riid,
                                               __RPC__deref_out void __RPC_FAR *__RPC_FAR * ppvObject)
{
    if(NULL != ppvObject)
    {
        if(IID_IUIAnimationTimerEventHandler == riid)
        {
            *ppvObject = this;
        }
        else
        {
            *ppvObject = NULL;
        }

        return S_OK;
    }

    return E_FAIL;
}

//////////////////////////////////////////////////////////////////////////

ULONG AnimationTimerEventHandler::AddRef()
{
    return InterlockedIncrement(&m_lRefCount);
}

//////////////////////////////////////////////////////////////////////////

ULONG AnimationTimerEventHandler::Release()
{
    LONG lRef = InterlockedDecrement(&m_lRefCount);
    if ( 0 == lRef )
    {
        delete this;
    }

    return lRef;
}
