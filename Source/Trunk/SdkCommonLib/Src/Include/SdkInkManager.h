/*!
* @file SdkInkManager.h
* 
* @brief This class provides functions to operate ink, such as recognize, clear .etc. This class 
* defines events for _IInkRecognitionEventsImpl and IInkOverlayEventsImpl. The detail information 
* of parameters of each function, please see MSDN or Windows 7 SDK Documentation.
*
* Copyright (C) 2009, LZT Corporation.
* 
* @author Li Hong
* @date 2011/05/19 12:00
* @version 1.0.0
*/

#ifdef __cplusplus
#ifndef _SDKINKMANAGER_H_
#define _SDKINKMANAGER_H_

#include "SdkCommon.h"
#include "SdkInkEvents.h"

BEGIN_NAMESPACE_COMMON

typedef void (CALLBACK *GETRECOGLIST_CALLBACK)(IN LPVOID pSender, IN HWND hWnd);

class CLASS_DECLSPEC SdkInkManager : public SdkInkEvents
{
public:

    /*
    * @brief The default constructor function.
    */
    SdkInkManager();

    /*
    * @brief The destructor function.
    */
    virtual ~SdkInkManager();

    /*
    * @brief Initialize interface instances.
    *
    * @param bRegisterRecognizeEvent [I/ ] Indicates register recognition event or not.
    *                                      Register event if TRUE, otherwise not register, default value is TRUE.
    * @param bRegisterOverlayEvent   [I/ ] Indicate register ink overlay event or not. The default value is TRUE.
    *
    * @return BOOL TRUE is successful, FALSE is failure.
    */
    BOOL Initialize(BOOL bRegisterRecognizeEvent = TRUE, BOOL bRegisterOverlayEvent = TRUE);

    /*
    * @brief Attach Ink object to the window specified by hWnd.
    *
    * @param hWnd       [I/ ] The Handle of Window to be attached.
    *
    * @return BOOL TRUE is successful, FALSE is failure.
    */
    BOOL AttachHWND(IN HWND hWnd);

    /*
    * @brief Detach Ink object and the window specified by Handler used in AttachHwnd function.
    *        If you want attach a Window to Ink overlay again after calling this method, you must call
    *        Init function first and then call AttahHWND function.
    */
    void DetachHWND();

    /*
    * @brief Clear all ink in Ink Collection.
    *
    * @param bClearAllOrSelected [I/ ] This parameter indicates this function clear
    *                                  all strokes or selected strokes.
    *                                  TRUE is clear all strokes, FALSE is clear selected strokes.
    *                                  The default value is TRUE
    *
    * @return BOOL TRUE is successful, FALSE is failure.
    */
    BOOL ClearStrokes(BOOL bClearAllOrSelected = TRUE);

    /*
    * @brief Gets the bounding box in ink space coordinates for either all of the strokes 
    *        in an InkDisp object, an individual stroke, or an InkStrokes collection.
    * 
    * @param lpRect         [ /O] The pointer to RECT structure.
    *
    * @return BOOL TRUE is successful, FALSE is failure.
    */
    BOOL GetBoundingBox(OUT LPRECT lpRect);

    /*
    * @brief Gets the bounding box of selected stroked.
    * 
    * @param lpRect         [ /O] The pointer to RECT structure.
    *
    * @return BOOL TRUE is successful, FALSE is failure.
    */
    BOOL GetSelectionRect(OUT LPRECT lpRect);

    /*
    * @brief Adds a specified Strokes collection into this InkDisp object at a default rectangle.
    * 
    * @param pSrcInkManager [I/ ] The pointer to SdkInkManager class to specify the source strokes
    *                             to be added current strokes collection.
    *
    * @return BOOL TRUE is successful, FALSE is failure.
    */
    BOOL AddInkStrokes(IN const SdkInkManager* pSrcInkManager);

    /*
    * @brief Adds a specified Strokes collection into this InkDisp object at a specified rectangle.
    * 
    * @param pSrcInkManager [I/ ] The pointer to CInkManager class to specify the source strokes
    *                             to be added current strokes collection.
    * @param rect           [I/ ] The reference to RECT structure.
    *
    * @return BOOL TRUE is successful, FALSE is failure.
    */
    BOOL AddInkStrokes(IN const SdkInkManager* pSrcInkManager, IN const RECT& rect);

    /*
    * @brief Move specified strokes to specified rectangle.
    * 
    * @param pInkRectangle  [I/ ] The pointer to IInkRectangle to indicate where strokes to be moved.
    *                             TRUE is to move all strokes, FALSE is to move selection strokes.
    *                             The default value is TRUE.
    * @param bMoveAllOrSelected [I/ ] This indicates move all strokes or selected strokes.
    *
    * @return BOOL TRUE is successful, FALSE is failure.
    */
    BOOL MoveTo(IN IInkRectangle* pInkRectangle, IN BOOL bMoveAllOrSelected = TRUE);

    /*
    * @brief Applies a translation to the ink of an IInkStrokeDisp object or InkStrokes collection.
    * 
    * @param offsetX    [I/ ] The distance in ink space coordinates to translate
    *                         the view transform in the X dimension.
    * @param offsetY    [I/ ] The distance in ink space coordinates to translate the view transform in the Y dimension.
    *
    * @return BOOL TRUE is successful, FALSE is failure.
    */
    BOOL MoveSelection(IN FLOAT offsetX, IN FLOAT offsetY);

    /*
    * @brief Save ink to a local file, the default format is InkSerializedFormat(.isf).
    *
    * @param lpfilePath [I/ ] The file path to be saved data.
    *
    * @return BOOL TRUE is successful, FALSE is failure.
    */
    BOOL SaveToFile(IN LPCWSTR lpfilePath);

    /*
    * @brief Load ink data from a file specified by lpfilePath, the file extension is .isf.
    *
    * @param lpfilePath [I/ ] The file path to be read data.
    *
    * @return BOOL TRUE is successful, FALSE is failure.
    */
    BOOL LoadFromFile(IN LPCWSTR lpfilePath);

    /*
    * @brief Draw inks on specified DC.
    *
    * @param hDC        [I/ ] The handle to the DC.
    *
    * @return BOOL TRUE is successful, FALSE is failure.
    */
    BOOL DrawInks(IN HDC hDC);

    /*
    * @brief Get the recognizer names.
    *
    * @param pvtNames   [ /O] The pointer of pointer to vector<TCHAR*>.
    *                         This function will malloc memory for pvtNames.
    *                         You should call Free function to release this pointer.
    *
    * @return BOOL TRUE is successful, FALSE is failure.
    */
    BOOL GetRecognizerNames(OUT vector<BSTR>** pvtNames);

    /*
    * @brief Set the ink draw attributes.
    *
    * @param fNewWidth  [I/ ] The y-axis dimension, or width, of the pen tip when drawing ink.The default value is 53.0f.
    *
    * @param newColor   [I/ ] The color of the ink that is drawn with this InkDrawingAttributes object. 
    *                         The default value is BLACK (RGB(0,0,0)).
    *                         The using sample of this parameter as following:
    *                         long newColor = RGB(255, 0, 0) (Red);
    *
    * @return BOOL TRUE is successful, FALSE is failure.
    */
    BOOL SetInkDrawAttribute(IN float fNewWidth = 53.0f, IN long newColor = RGB(0, 0, 0));

    /*
    * @brief Sets a value that specifies whether the object/control is in ink mode, 
    *        deletion mode, or selecting/editing mode.
    *
    * @param EditingMode [I/ ] A value that specifies whether the control is in ink mode, deletion mode, or 
    *                          selection/editing mode. The default value is IOEM_Ink, which specifies ink mode.
    *
    * @return BOOL TRUE is successful, FALSE is failure.
    */
    BOOL SetEditingMode(InkOverlayEditingMode editingMode = IOEM_Ink);

    /*
    * @brief Set selected strokes to unselected status.
    *
    * @return BOOL TRUE is successful, FALSE is failure.
    */
    BOOL CancelSelection();

    /*
    * @brief Check selected strokes rectangle is in attached window rectangle or not.
    *
    * @param rect           [I/ ] The reference to RECT structure.
    *
    * @return BOOL Return value is TRUE if in client rectangle, otherwise return value is FALSE.
    */
    BOOL IsSelectedRectInClientRect(IN const RECT& rect);

    /*
    * @brief This method will create a new recognizer context and put recognizer guide to the context.
    *
    * @param pInkRecognizer [I/ ] The pointer to IInkRecognizer;
    *
    * @return BOOL Return value is TRUE if succeed, otherwise return value is FALSE.
    */
    BOOL CreateNewRecogContext(IN IInkRecognizer* pInkRecognizer);

    /*
    * @brief Get the language id supported by current recognizer.
    *
    * @param langID         [I/O] The language ID of current recognizer.
    *
    * @return BOOL Return value is TRUE if succeed, otherwise return value is FALSE.
    *              if the function fails, the langID will be the default language id.
    */
    BOOL GetLanguageID(OUT LANGID* langID);

    /*
    * @brief Set a new recognizer at the specified index in recognizer collection.
    *
    * @param nIndex         [I/ ] The index of the recognizer.
    *
    * @return BOOL Return value is TRUE if succeed, otherwise return value is FALSE.
    */
    BOOL SetNewRecognizer(LONG nIndex);

    /*
    * @brief Insert the ink recognition result.
    *
    * @return BOOL Return value is TRUE if succeed, otherwise return value is FALSE.
    */
    BOOL InsertRecognitionResult();

    /*
    * @brief Get the recognize result. You should enumerate to call this function to get all recognized result.
    *        Before calling this function, you should call GetRecogResultCount function to get result count first.
    *
    * @param nIndex        [I/ ] The index of the result item.
    * @param szRecogResult [ /O] The buffer to be stored the result.
    * @param DWORD dwSize The size of the szRecogResult buffer.
    *
    * @return BOOL Return value is TRUE if succeed, otherwise return value is FALSE.
    */
    BOOL RecogResultItem(LONG nIndex, OUT LPTSTR szRecogResult, DWORD dwSize);

    /*
    * @brief Get the recognizer installed on current machine. You should enumerate to call this function to get all recognizers.
    *        Before calling this function, you should call GetRecognizerCount function to get recognizer count first.
    *
    * @param nIndex         [I/ ] The index of the result item.
    * @param szRecognizer   [ /O] The buffer to be stored the result.
    * @param dwSize         [I/ ] The size of the szRecogResult buffer.
    *
    * @return BOOL Return value is TRUE if succeed, otherwise return value is FALSE.
    */
    BOOL RecognizerItem(LONG nIndex, OUT LPTSTR szRecognizer, DWORD dwSize);

    /*
    * @brief Get the count of the recognized result list.
    *
    * @return LONG The count of the result list.
    */
    LONG GetRecogResultCount();

    /*
    * @brief Get the count of the recognizer installed on the machine.
    *
    * @return LONG The count of the recognizer.
    */
    LONG GetRecognizerCount();

    /*
    * @brief Set the callback to notification window to get recognize result list.
    *
    * @param pGetRecogListFunction  [I/ ] The pointer of function address.
    * @param hClientWnd             [I/ ] The handle to the client window to receive the message or callback.
    */
    void SetRecogNotification(GETRECOGLIST_CALLBACK pGetRecogListFunction, IN HWND hClientWnd);

    /*
    * @brief Set the recognize guid.
    *
    * @param inkGuide               [I/ ] The InkRecoGuide structure.
    */
    void SetRecognizeGuide(IN InkRecoGuide inkGuide);

    /*
    * @brief Free the memory malloc by SdkInkManager class. When you call GetRecognizerNames function 
    *        to get a pointer to vector<BSTR>. You must call this method to prevent memory leak.
    *
    * @param ppvtNames  [I/O] The pointer to vector<BSTR>**.
    *                         After call this function, memory pointed by pvtNames will be deleted.
    */
    void Free(IN OUT vector<BSTR>** pvtNames);

protected:

    /*
    * @brief Begin to recognize the ink and convert it to literal words.
    *
    * @param pIInkRecogResult [I/ ] The recognition result object.
    *
    * @return BOOL TRUE is successful, FALSE is failure.
    */
    BOOL Recognize(IN IInkRecognitionResult* pIInkRecoResult);

    /*
    * @brief Occurs when the InkRecognizerContext has generated results after calling the BackgroundRecognizeWithAlternates method.
    */
    virtual void OnRecognitionWithAlternates(IInkRecognitionResult* pIInkRecoResult, VARIANT vCustomParam, InkRecognitionStatus RecognitionStatus);

    /*
    * @brief Occurs when the user draws a new stroke on any tablet.
    */
    virtual void OnStroke(IInkCursor* pIInkCursor, IInkStrokeDisp* pInkStroke, VARIANT_BOOL* pbCancel);

    /*
    * @brief Occurs when an application-specific gesture is recognized.
    *
    * @param OldSelectionRect   [I/ ] The bounding rectangle of the selected InkStrokes collection as it existed
    *                                 before the SelectionMoved event fired.
    *
    * @remark There is limit that the selection strokes can be moved out of client rectangle. The function will implement this function.
    */
    virtual void OnSelectionMoved(IInkRectangle *OldSelectionRect);

private:

    LANGID                     m_langID;                    // The language id supported by current recognizer.
    HWND                       m_hClientWnd;                // The handle to client window to receive the message or callback.
    HWND                       m_hAttachedWnd;              // The handler of attached window to the InkOverlay object. This object need not use DestroyWindow to release it.
    vector<BSTR>              *m_vtRecogResult;             // The pointer to vector to indicate the recognize result.
    vector<TCHAR*>            *m_vtRecognizerList;          // The recognizers installed on current machine.
    GETRECOGLIST_CALLBACK      m_pGetRecoglistCallback;     // The callback function.
    IInkRecognitionResult     *m_pInkRecogResult;           // The recognition result pointer. Do NOT release this object.
    IHandwrittenTextInsertion *m_pHandWrittenTextInsertion; // It is used to insert recognition result to both the text field and the Text Services backing-store.
    IInkRenderer              *m_pInkRender;                // The pointer to IInkRenderer
    IInkDisp                  *m_pInkDisp;                  // The pointer to IInkDisp to indicate ink collection.
    IInkStrokes               *m_pInkStrokes;               // The pointer to IInkStrokes. The stroke collection.
    IInkOverlay               *m_pInkOverlay;               // The pointer to IInkOverlay, the core object of Ink.
    IInkRecognizer            *m_pInkRecognizer;            // The current recognizer object.
    IInkRecognizers           *m_pInkRecognizers;           // The pointer to IInkRecognizers.
    IInkRecognizerContext     *m_pInkRecogContext;          // The pointer to IInkRecognizerContext, used to recognize strokes.
    IInkRecognizerGuide       *m_pInkRecogGuide;            // The pointer to IInkRecognizerGuide, Represents the area that the recognizer uses in which ink can be drawn. 
    IInkDrawingAttributes     *m_pInkDrawingAttr;           // The pointer to IInkDrawingAttributes, indicate the draw attribute of ink
};

END_NAMESPACE_COMMON

#endif // _SDKINKMANAGER_H_
#endif // __cplusplus
