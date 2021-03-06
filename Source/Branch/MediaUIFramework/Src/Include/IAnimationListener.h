/*!
* @file IAnimationListener.h 
* 
* @brief This file defines the event interface of animation.
* 
* Copyright (C) 2010, Toshiba Corporation.
* 
* @author Qiao LiYun
* @date 2010/12/28
*/

#ifdef __cplusplus
#ifndef _IANIMATIONLISTENER_H_
#define _IANIMATIONLISTENER_H_

class Animation;

/*!
* @brief The interface defines the common event handler for animation.
*/
class CLASS_DECLSPEC IAnimationListener
{
public:

    /*!
    * @brief The destructor function.
    */
    virtual ~IAnimationListener(){}

    /*!
    * @brief This method can be called when the animation is about to start.
    */
    virtual VOID OnAnimationStart(Animation *pAnimation) = 0;

    /*!
    * @brief This method can be called when the animation is about to play.
    */
    virtual VOID OnAnimationPlaying(Animation *pAnimation) = 0;

    /*!
    * @brief This method can be called when the animation has ended.
    */
    virtual VOID OnAnimationEnd(Animation *pAnimation) = 0;
};

#endif // _IANIMATIONLISTENER_H_
#endif //__cplusplus
