/*!
* @file AlphaAnimation.cpp 
* 
* @brief This file defines the functions of alpha animation.
* 
* Copyright (C) 2010, Toshiba Corporation.
* 
* @author Qiao LiYun, Cui ShuYan
* @date 2010/12/28
*/

#include "AlphaAnimation.h"

//////////////////////////////////////////////////////////////////////////

AlphaAnimation::AlphaAnimation(DOUBLE dFromAlpha,
                               DOUBLE dToAlpha,
                               DOUBLE dDuration,
                               DOUBLE dAccelerationRatio,
                               DOUBLE dDecelerationRatio):
                m_pAlphaVariable(NULL),
                m_pTransition(NULL)
{
    m_nAnimationType = TRANSFORM_TYPE_ALPHA;

    if(dToAlpha < 0)
    {
        dToAlpha = 0;
    }
    else if(dToAlpha > 1.0)
    {
        dToAlpha = 1.0;
    }

    m_pAlphaInfo = new TRANSITIONINFO();
    m_pAlphaInfo->dFrom = dFromAlpha;
    m_pAlphaInfo->dTo = dToAlpha;
    m_pAlphaInfo->dDuration = dDuration;
    m_pAlphaInfo->dAccelerationRatio = dAccelerationRatio;
    m_pAlphaInfo->dDecelerationRatio = dDecelerationRatio;
}

//////////////////////////////////////////////////////////////////////////

AlphaAnimation::~AlphaAnimation(void)
{
    SAFE_DELETE(m_pAlphaInfo);
    SAFE_RELEASE(m_pAlphaVariable);
    SAFE_RELEASE(m_pTransition);
}

//////////////////////////////////////////////////////////////////////////

HRESULT AlphaAnimation::GetValue(OUT DOUBLE  *pValue, 
                                 BOOL        bUpdate)
{
    HRESULT hr = GetVariableValue(pValue, m_pAlphaVariable, bUpdate);

    return hr;
}

//////////////////////////////////////////////////////////////////////////

HRESULT AlphaAnimation::GetDuration(OUT DOUBLE *pDuration)
{
    HRESULT hr = E_FAIL;

    if(NULL != m_pTransition)
    {
        hr = m_pTransition->GetDuration(pDuration);
    }

    return hr;
}

//////////////////////////////////////////////////////////////////////////

HRESULT AlphaAnimation::GetTransform(OUT LPTRANSFORMINFO pTransform,
                                     IN  BOOL bUpdate)
{
    HRESULT hr = S_OK;

    if(NULL != pTransform)
    {
        if(bUpdate)
        {
            hr = this->Update();
        }

        if(SUCCEEDED(hr))
        {
            if(NULL != m_pAlphaVariable && NULL != m_pAlphaInfo)
            {
                DOUBLE dValue = 0.0; 
                hr = m_pAlphaVariable->GetValue(&dValue);

                if(SUCCEEDED(hr))
                {
                    pTransform->typeTransform = m_nAnimationType;
                    pTransform->matrixTransform = D2D1::Matrix3x2F::Identity();
                    pTransform->dAlpha = dValue;
                }
            }
            else
            {
                hr = E_FAIL;
            }
        }
    }

    return hr;
}

//////////////////////////////////////////////////////////////////////////

HRESULT AlphaAnimation::GetAnimationInfo(OUT  IUIAnimationVariable ***pppVarible,
                                         OUT  IUIAnimationTransition ***pppTransition,
                                         OUT  UINT32 *pTransitionCount,
                                         BOOL bUpdate)
{
    HRESULT hr = E_FAIL;

    if((NULL != m_pAlphaInfo)
        && (NULL != pppVarible)
        && (NULL != pppTransition)
        && (NULL != pTransitionCount))
    {
        *pTransitionCount = 1;
        *pppVarible = new IUIAnimationVariable *[1];
        *pppTransition = new IUIAnimationTransition *[1];

        hr = CreateVariable(m_pAlphaInfo, &m_pAlphaVariable, bUpdate);

        if(SUCCEEDED(hr))
        {
            hr = CreateTransition(m_pAlphaInfo, &m_pTransition, bUpdate);

            if(SUCCEEDED(hr))
            {
                (*pppVarible)[0] = m_pAlphaVariable;
                m_pAlphaVariable->AddRef();

                (*pppTransition)[0] = m_pTransition;
                m_pTransition->AddRef();
            }
        }
    }

    return hr;
}

//////////////////////////////////////////////////////////////////////////

HRESULT AlphaAnimation::InitStoryboard()
{
    HRESULT hr = CreateVariable(m_pAlphaInfo, &m_pAlphaVariable, TRUE);

    if(SUCCEEDED(hr))
    {
        hr = CreateTransition(m_pAlphaInfo, &m_pTransition, TRUE);

        if(SUCCEEDED(hr))
        {
            SAFE_RELEASE(m_pStoryBoard);

            hr = m_pAnimationCom->CreateStoryboard(&m_pStoryBoard);

            if(SUCCEEDED(hr))
            {
                hr = m_pStoryBoard->AddTransition(m_pAlphaVariable, m_pTransition);
            }
        }
    }

    return hr;
}
