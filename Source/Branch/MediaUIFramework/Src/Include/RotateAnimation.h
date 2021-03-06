/*!
* @file RotateAnimation.h 
* 
* @brief This file defines the functions of rotate animation.
* 
* Copyright (C) 2010, Toshiba Corporation.
* 
* @author Qiao LiYun, Cui ShuYan
* @date 2010/12/28
*/

#ifdef __cplusplus
#ifndef _ROTATEANIMATION_H_
#define _ROTATEANIMATION_H_

#include "CommonInclude.h"
#include "Animation.h"

/*!
* @brief This class implements the function of the rotate animation.
*/
class CLASS_DECLSPEC RotateAnimation : public Animation
{
public:

    /*!
    * @brief The constructor.
    *
    * @param pointCenter            [I/ ] The center point.
    * @param dFormAngle             [I/ ] The start position.
    * @param dToAngle               [I/ ] The end position.
    * @param dDuration              [I/ ] The animation duration.
    * @param dAccelerationRatio     [I/ ] The accelerate ratio.
    * @param dDecelerationRatio     [I/ ] The decelerate ratio.
    */
    RotateAnimation(const D2D1_POINT_2F *pointCenter,
                    DOUBLE dFormAngle,
                    DOUBLE dToAngle,
                    DOUBLE dDuration = 1.0,
                    DOUBLE dAccelerationRatio = 0.5,
                    DOUBLE dDecelerationRatio = 0.5);

    /*!
    * @brief The default destructor.
    */
    ~RotateAnimation();

    /*!
    * @brief Get the value of the variable.
    *
    * @param pValue     [ /O] The variable value.
    * @param bUpdate    [I/ ] The flag which indicates to update the animation value or not.
    *
    * @return S_OK if success, otherwise return E_FAIL.
    */
    HRESULT GetValue(OUT DOUBLE *pValue, BOOL bUpdate = TRUE);

    /*!
    * @brief Get the duration of the rotate animation.
    *
    * @param pDuration      [ /O] The duration.
    *
    * @return S_OK if success, otherwise return E_FAIL.
    */
    virtual HRESULT GetDuration(OUT DOUBLE *pDuration);

    /*!
    * @brief Get the transform of the rotate animation.
    *
    * @param pTransform     [ /O] The transform information.
    * @param bUpdateFrame   [I/ ] The flag which indicates to update the animation value or not.
    *
    * @return S_OK if success, otherwise return E_FAIL.
    */
    virtual HRESULT GetTransform(OUT  LPTRANSFORMINFO pTransform,
                                 BOOL bUpdateFrame = TRUE) ;

    /*!
    * @brief Get the information of the rotate animation.
    *
    * @param pppVarible             [ /O] The variable information of the rotate animation.
    * @param pppTransition          [ /O] The transition information of the rotate animation.
    * @param pTransitionCount       [ /O] The count of the variable.
    * @param bUpdate                [I/ ] The flag which indicates to update the animation value or not.
    *
    * @return S_OK if success, otherwise return E_FAIL.
    */
    virtual HRESULT GetAnimationInfo(OUT  IUIAnimationVariable ***pppVarible,
                                     OUT  IUIAnimationTransition ***pppTransition,
                                     OUT  UINT32 *pTransitionCount,
                                     BOOL bUpdate = TRUE) ;

protected:

    /*!
    * @brief Initialize the storyboard of the rotate animation.
    *
    * @return S_OK if success, otherwise return E_FAIL.
    */
    virtual HRESULT InitStoryboard();

private:

    D2D1_POINT_2F                   m_centerPoint;       // The center point.
    LPTRANSITIONINFO                m_pRotateInfo;       // The information of the rotate animation.
    IUIAnimationVariable           *m_pAngleVariable;    // The variable of the rotate animation.
    IUIAnimationTransition         *m_pTransition;       // The transition of the rotate animation.
};

#endif // _ROTATEANIMATION_H_
#endif // __cplusplus
