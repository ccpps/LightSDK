/*!
* @file SdkAnimation.cpp 
* 
* @brief This file defines the base functions of animation.
* 
* Copyright (C) 2010, LZT Corporation.
* 
* @author Qiao LiYun
* @date 2010/12/28
*/

#include "stdafx.h"
#include "SdkAnimation.h"
#include "SdkAnimationCom.h"
#include "SdkStoryboardEventHandler.h"
#include "IAnimationListener.h"
#include "IAnimationTimerListener.h"

USING_NAMESPACE_ANIMATION

SdkAnimation::SdkAnimation(): m_pStoryBoard(NULL),
                              m_pStoryboardEventHandler(NULL),
                              m_pAnimationCom(NULL),
                              m_nAnimationType(TRANSFORM_TYPE_UNKNOWN),
                              m_bStart(FALSE)
{
    m_pAnimationCom = new SdkAnimationCom();
}

//////////////////////////////////////////////////////////////////////////

SdkAnimation::~SdkAnimation()
{
    SAFE_DELETE(m_pAnimationCom);

    SAFE_RELEASE(m_pStoryBoard);
    SAFE_RELEASE(m_pStoryboardEventHandler);
}

//////////////////////////////////////////////////////////////////////////

INT32 SdkAnimation::GetAnimationType()
{
    return m_nAnimationType;
}

//////////////////////////////////////////////////////////////////////////

HRESULT SdkAnimation::Start(DOUBLE dDelaySeconds)
{
    UI_ANIMATION_SECONDS timeNow;
    HRESULT hr = m_pAnimationCom->GetTime(&timeNow);
    if (SUCCEEDED(hr))
    {
        m_bStart = TRUE;
        hr = this->StartAnimation(timeNow + dDelaySeconds);
    }

    return hr;
}

//////////////////////////////////////////////////////////////////////////

HRESULT SdkAnimation::Stop()
{
    return this->Finish();
}

//////////////////////////////////////////////////////////////////////////

HRESULT SdkAnimation::Finish()
{
    return (NULL != m_pStoryBoard) ? m_pStoryBoard->Finish(0) : E_FAIL;
}

//////////////////////////////////////////////////////////////////////////

HRESULT SdkAnimation::GetElapsedTime(OUT DOUBLE &dElapsedTime)
{
    if (NULL != m_pStoryBoard)
    {
        return m_pStoryBoard->GetElapsedTime(&dElapsedTime);
    }

    return E_FAIL;
}

//////////////////////////////////////////////////////////////////////////

HRESULT SdkAnimation::IsFinish(OUT BOOL *bFinish)
{
    HRESULT hr = (NULL != m_pStoryBoard || NULL == bFinish) ? S_OK : E_FAIL;

    if ( SUCCEEDED(hr) )
    {
        UI_ANIMATION_STORYBOARD_STATUS status;
        hr = m_pStoryBoard->GetStatus(&status);
        if ( SUCCEEDED(hr) )
        {
            if ( (status == UI_ANIMATION_STORYBOARD_READY) ||
                 (status == UI_ANIMATION_STORYBOARD_BUILDING) )
            {
                *bFinish = TRUE;
            }
            else
            {
                *bFinish = FALSE;
            }
        }
    }

    return hr;
}

//////////////////////////////////////////////////////////////////////////

BOOL SdkAnimation::IsStart()
{
    return m_bStart;
}

//////////////////////////////////////////////////////////////////////////

HRESULT SdkAnimation::GetDuration(OUT DOUBLE *pDuration)
{
    UNREFERENCED_PARAMETER(pDuration);

    return E_NOTIMPL;
}

//////////////////////////////////////////////////////////////////////////

HRESULT SdkAnimation::GetTransform(OUT LPTRANSFORMINFO pTransform, IN BOOL bUpdateValue)
{
    UNREFERENCED_PARAMETER(pTransform);
    UNREFERENCED_PARAMETER(bUpdateValue);

    return E_NOTIMPL;
}

//////////////////////////////////////////////////////////////////////////

HRESULT SdkAnimation::AddAnimationListener(IAnimationListener *pListener)
{
    return this->SetStoryBoardListener(pListener);
}

//////////////////////////////////////////////////////////////////////////

HRESULT SdkAnimation::RemoveAnimationListener(IAnimationListener *pListener)
{
    if ( (NULL != pListener) && (NULL != m_pStoryboardEventHandler) )
    {
        m_pStoryboardEventHandler->RemoveAnimationListener(pListener);
    }

    return S_OK;
}

//////////////////////////////////////////////////////////////////////////

HRESULT SdkAnimation::AddAnimationTimerListener(IAnimationTimerListener *pListener)
{
    return m_pAnimationCom->AddTimerListener(pListener, this);
}

//////////////////////////////////////////////////////////////////////////

HRESULT SdkAnimation::RemoveAnimationTimerListener(IAnimationTimerListener *pListener)
{
    return m_pAnimationCom->RemoveTimerListener(pListener);
}

//////////////////////////////////////////////////////////////////////////

HRESULT SdkAnimation::GetAnimationInfo(
    OUT IUIAnimationVariable ***pppVarible,
    OUT IUIAnimationTransition ***pppTransition,
    OUT UINT32 *pTransitionCount,
    BOOL bUpdate)
{
    UNREFERENCED_PARAMETER(pppVarible);
    UNREFERENCED_PARAMETER(pppTransition);
    UNREFERENCED_PARAMETER(pTransitionCount);
    UNREFERENCED_PARAMETER(bUpdate);

    return E_NOTIMPL;
}

//////////////////////////////////////////////////////////////////////////

HRESULT SdkAnimation::InitStoryboard()
{
    return E_NOTIMPL;
}

//////////////////////////////////////////////////////////////////////////

HRESULT SdkAnimation::StartAnimation(IN UI_ANIMATION_SECONDS timeNow)
{
    HRESULT hr = E_FAIL;
    SAFE_RELEASE(m_pStoryBoard);

    if ( SUCCEEDED(InitStoryboard()) )
    {
        SetStoryBoardListener(NULL);
        hr = m_pStoryBoard->Schedule(timeNow, NULL);
    }

    return hr;
}

//////////////////////////////////////////////////////////////////////////

HRESULT SdkAnimation::Update()
{
    return (NULL != m_pAnimationCom) ? m_pAnimationCom->Update() : E_FAIL;
}

//////////////////////////////////////////////////////////////////////////

HRESULT SdkAnimation::SetStoryBoardListener(IAnimationListener *pListener)
{
    HRESULT hr = S_OK;

    if (NULL == m_pStoryboardEventHandler)
    {
        m_pStoryboardEventHandler = new SdkStoryboardEventHandler();
    }

    m_pStoryboardEventHandler->AddAnimationListener(pListener, this);
    if (NULL != m_pStoryBoard)
    {
        hr = m_pStoryBoard->SetStoryboardEventHandler(m_pStoryboardEventHandler);
    }

    return hr;
}

//////////////////////////////////////////////////////////////////////////

HRESULT SdkAnimation::CreateVariable(
    LPTRANSITIONINFO pTransitionInfo,
    IUIAnimationVariable **pTransitionVarible,
    BOOL bUpdate)
{
    HRESULT hr = (NULL != pTransitionVarible) ? S_OK : E_FAIL;

    if ( SUCCEEDED(hr) )
    {
        if (bUpdate)
        {
            SAFE_RELEASE((*pTransitionVarible));
        }

        if (NULL == (*pTransitionVarible))
        {
            hr = m_pAnimationCom->CreateVariable(
                pTransitionInfo->dFrom,
                pTransitionVarible);
        }
    }

    return hr;
}

//////////////////////////////////////////////////////////////////////////

HRESULT SdkAnimation::CreateTransition(
    LPTRANSITIONINFO pTransitionInfo,
    IUIAnimationTransition **pTransition,
    BOOL bUpdate)
{
    HRESULT hr = (NULL != pTransition) ? S_OK : E_FAIL;

    if ( SUCCEEDED(hr) )
    {
        if (bUpdate)
        {
            SAFE_RELEASE(*pTransition);
        }

        if (NULL == (*pTransition))
        {
            hr = m_pAnimationCom->CreateAccelerateDecelerateTransition(
                pTransitionInfo->dDuration,
                pTransitionInfo->dTo,
                pTransitionInfo->dAccelerationRatio,
                pTransitionInfo->dDecelerationRatio,
                pTransition);
        }
    }

    return hr;
}

//////////////////////////////////////////////////////////////////////////

HRESULT SdkAnimation::GetVariableValue(
    OUT DOUBLE *pVariableValue,
    IUIAnimationVariable *pTransitionVarible,
    BOOL bUpdate)
{
    HRESULT hr = E_FAIL;

    if (NULL != pVariableValue && NULL != pTransitionVarible)
    {
        if (bUpdate)
        {
            hr = this->Update();
        }

        hr = (NULL != pTransitionVarible) ? S_OK : E_FAIL;
        if (SUCCEEDED(hr))
        {
            hr = pTransitionVarible->GetValue(pVariableValue);
        }
    }

    return hr;
}
