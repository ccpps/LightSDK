/*!
* @file AnimationTimerEventHandler.h 
* 
* @brief This file defines the event handler of animation timer.
* 
* Copyright (C) 2010, Toshiba Corporation.
* 
* @author Qiao LiYun
* @date 2011/02/15
*/

#ifdef __cplusplus
#ifndef _ANIMATIONTIMEREVENTHANDLER_H_
#define _ANIMATIONTIMEREVENTHANDLER_H_

#include "CommonInclude.h"
#include <UIAnimation.h>
#include "Animation.h"
#include "IAnimationTimerListener.h"

/*!
* @brief This class defines the event handler of animation timer.
*/
class CLASS_DECLSPEC AnimationTimerEventHandler : public IUIAnimationTimerEventHandler
{
public:

    /*!
    * @brief The constructor.
    */
    AnimationTimerEventHandler();

    /*!
    * @brief Add the listener of animation timer.
    *
    * @param pListener     [I/ ] The listener.
    * @param pAnimation    [I/ ] The animation.
    */
    void AddListener(IAnimationTimerListener *pListener, Animation *pAnimation);

    /*!
    * @brief Remove the listener of animation timer.
    *
    * @param pListener     [I/ ] The listener.
    */
    void RemoveListener(IAnimationTimerListener *pListener);

    /*!
    * @brief Called when the timer is about to update.
    * 
    * @return S_OK if success, otherwise return E_FAIL.
    */
    virtual HRESULT __stdcall OnPreUpdate();

    /*!
    * @brief Called when the timer update.
    * 
    * @return S_OK if success, otherwise return E_FAIL.
    */
    virtual HRESULT __stdcall OnPostUpdate();

    /*!
    * @brief Called when the rendering slow.
    * 
    * @param fps            [I/ ] The fps value.
    * 
    * @return S_OK if success, otherwise return E_FAIL.
    */
    virtual HRESULT __stdcall OnRenderingTooSlow( UINT32 fps );

    /*!
    * @brief Called to decide to query the interface or not.
    *
    * @param riid          [I/ ] Identifier of the interface being queried.
    * @param ppvObject     [I/O] Pointer to a buffer that receives a pointer to the object whose 
    *                            interface is queried or NULL when an interface is not supported.
    *
    * @return S_OK if success, otherwise return E_FAIL.
    */
    virtual HRESULT __stdcall QueryInterface( 
        REFIID riid,
        __RPC__deref_out void __RPC_FAR *__RPC_FAR *ppvObject);

    /*!
    * @brief Called to add one to the animation count.
    *
    * @return The count of existing animation.
    */
    virtual ULONG __stdcall AddRef();

    /*!
    * @brief Called to release the event handler of storyboard.
    *
    * @return The count of existing animation.
    */
    virtual ULONG __stdcall Release();

private:

    /*!
    * @brief The default destructor.
    */
    ~AnimationTimerEventHandler();

private:

    Animation               *m_pAnimation;              // The animation.
    LONG                    m_lRefCount;                // The animation count.
    vector<IAnimationTimerListener *> m_vecAnimationTimerListener; // The animation timer listener.
};

#endif // _ANIMATIONTIMEREVENTHANDLER_H_
#endif // __cplusplus
