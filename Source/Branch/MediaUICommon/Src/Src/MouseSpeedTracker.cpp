/*! 
* @file MouseSpeedTracker.cpp 
* 
* @brief This file defines the functions to track mouse speed.
* 
* Copyright (C) 2010, Toshiba Corporation.
* 
* @author Qiao LiYun
* @date 2010/12/28
*/

#include "CommonHelper.h"
#include "MouseSpeedTracker.h"
#include "PerformanceCounter.h"

USING_NAMESPACE_COMMON

//////////////////////////////////////////////////////////////////////////

MouseSpeedTracker::MouseSpeedTracker()
{
    m_dSpeedX       = 0.0;
    m_dSpeedY       = 0.0;
    m_firstPT.x     = 0;
    m_firstPT.y     = 0;
    m_secondPT.x    = 0;
    m_secondPT.y    = 0;
    m_deltaDist.x   = 0;
    m_deltaDist.y   = 0;
    m_dwElapseTime  = 0;

    m_isLBDown      = FALSE;
}

//////////////////////////////////////////////////////////////////////////

MouseSpeedTracker::~MouseSpeedTracker()
{
}

//////////////////////////////////////////////////////////////////////////

DOUBLE MouseSpeedTracker::GetSpeedX()
{
    return m_dSpeedX;
}

//////////////////////////////////////////////////////////////////////////

DOUBLE MouseSpeedTracker::GetSpeedY()
{
    return m_dSpeedY;
}

//////////////////////////////////////////////////////////////////////////

DWORD MouseSpeedTracker::GetSpeedSampleTime()
{
    return m_dwElapseTime;
}

//////////////////////////////////////////////////////////////////////////

void MouseSpeedTracker::OnMouseEvent(HWND hWnd, UINT32 message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(hWnd);
    UNREFERENCED_PARAMETER(message);
    UNREFERENCED_PARAMETER(wParam);
    UNREFERENCED_PARAMETER(lParam);

    int xPos = GET_X_LPARAM(lParam);
    int yPos = GET_Y_LPARAM(lParam);

    switch (message)
    {
    case WM_MOUSEMOVE:
        {
            if (m_isLBDown)
            {
                PerformanceCounter::Stop();
                m_dwElapseTime = PerformanceCounter::GetElapsedTime();
                PerformanceCounter::Start();
                if ( m_dwElapseTime != 0 )
                {
                    m_secondPT.x  = xPos;
                    m_secondPT.y  = yPos;
                    m_deltaDist.x = m_secondPT.x - m_firstPT.x;
                    m_deltaDist.y = m_secondPT.y - m_firstPT.y;
                    m_firstPT     = m_secondPT;
                    m_dSpeedX = (DOUBLE)m_deltaDist.x / (DOUBLE)m_dwElapseTime;
                    m_dSpeedY = (DOUBLE)m_deltaDist.y / (DOUBLE)m_dwElapseTime;
                }
            }
        }
        break;

    case WM_MOUSELEAVE:
        {
            m_isLBDown = FALSE;
        }
        break;

    case WM_LBUTTONDOWN:
        {
            m_isLBDown = TRUE;
            m_firstPT.x = xPos;
            m_firstPT.y = yPos;
            m_dSpeedX = 0.0f;
            m_dSpeedY = 0.0f;
        }
        break;

    case WM_LBUTTONUP:
        {
            m_isLBDown = FALSE;
        }
        break;
    }
}