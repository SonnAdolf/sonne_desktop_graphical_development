#if 0

#pragma once

#include <string>
#include "finger_register.h"
namespace GETUSRNAME
{	
	CWINDOWS g_cWindow;
	HINSTANCE hInst;

	/**
	* 作者:	sonne
	* 备注:  HTMLayout按钮响应函数
	* 日期： 2017-04-19
	*/
	void OnButtonClick(HELEMENT button)
	{
		htmlayout::dom::element root = htmlayout::dom::element::root_element(g_cWindow.GetHandle());
		htmlayout::dom::element cBut = button;
		htmlayout::dom::element usrname;
		if (!wcscmp(cBut.get_attribute("id"),L"EXIT"))
		{
			PostMessage(g_cWindow.GetHandle(), WM_DESTROY, NULL, NULL);
		}
		if (!wcscmp(cBut.get_attribute("id"),L"OK"))
		{
			usrname = root.get_element_by_id("txt_username");
			json::string strUsrname = usrname.text();
			const wchar_t* usrname_c_str = strUsrname.c_str();

			input_usrname = new wchar_t[wcslen(usrname_c_str)+1];
			wcscpy(input_usrname, usrname_c_str);
			FINGERREGISTER::fingerRegister(hInst);
			PostMessage(g_cWindow.GetHandle(), WM_DESTROY, NULL, NULL);
		}
	}

	/**
	* 作者:	sonne
	* 日期: 2017-04-19
	* 备注:  HTMLayout通知响应函数
	*/
	LRESULT CALLBACK HTMLayoutNotifyHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, LPVOID vParam)
	{
		// all HTMLayout notification are comming here.
		NMHDR*  phdr = (NMHDR*)lParam;

		switch(phdr->code)
		{
		case HLN_CREATE_CONTROL:    break; //return OnCreateControl((LPNMHL_CREATE_CONTROL) lParam);
		case HLN_CONTROL_CREATED:   break; //return OnControlCreated((LPNMHL_CREATE_CONTROL) lParam);
		case HLN_DESTROY_CONTROL:   break; //return OnDestroyControl((LPNMHL_DESTROY_CONTROL) lParam);
			//	case HLN_LOAD_DATA:         return OnLoadData((LPNMHL_LOAD_DATA) lParam);
		case HLN_DATA_LOADED:       break; //return OnDataLoaded((LPNMHL_DATA_LOADED)lParam);
		case HLN_DOCUMENT_COMPLETE: break; //return OnDocumentComplete();
			//	case HLN_ATTACH_BEHAVIOR:   return OnAttachBehavior((LPNMHL_ATTACH_BEHAVIOR)lParam );
		}
		return 0;
	}


	struct DOMEventsHandlerType: htmlayout::event_handler
	{
		DOMEventsHandlerType(): event_handler(0xFFFFFFFF) {}
		/**
		* 作者:	sonne
		* 备注:  HTMLayout事件响应函数
		* 日期:  2017-04-19
		*/
		virtual BOOL handle_event (HELEMENT he, BEHAVIOR_EVENT_PARAMS& params ) 
		{ 
			switch( params.cmd )
			{
			case BUTTON_CLICK:              OnButtonClick(params.heTarget); break;// click on button
			case BUTTON_PRESS:              break;// mouse down or key down in button
			case BUTTON_STATE_CHANGED:      break;
			case EDIT_VALUE_CHANGING:       break;// before text change
			case EDIT_VALUE_CHANGED:        break;//after text change
			case SELECT_SELECTION_CHANGED:  break;// selection in <select> changed
			case SELECT_STATE_CHANGED:      break;// node in select expanded/collapsed, heTarget is the node
			case POPUP_REQUEST:				break;// request to show popup just received, 
				//     here DOM of popup element can be modifed.
			case POPUP_READY:               break;// popup element has been measured and ready to be shown on screen,
				//     here you can use functions like ScrollToView.
			case POPUP_DISMISSED:           break;// popup element is closed,
				//     here DOM of popup element can be modifed again - e.g. some items can be removed
				//     to free memory.
			case MENU_ITEM_ACTIVE:                // menu item activated by mouse hover or by keyboard
				break;
			case MENU_ITEM_CLICK:                 // menu item click 
				break;


				// "grey" event codes  - notfications from behaviors from this SDK 
			case HYPERLINK_CLICK:           break;// hyperlink click
			case TABLE_HEADER_CLICK:        break;// click on some cell in table header, 
				//     target = the cell, 
				//     reason = index of the cell (column number, 0..n)
			case TABLE_ROW_CLICK:           break;// click on data row in the table, target is the row
				//     target = the row, 
				//     reason = index of the row (fixed_rows..n)
			case TABLE_ROW_DBL_CLICK:       break;// mouse dbl click on data row in the table, target is the row
				//     target = the row, 
				//     reason = index of the row (fixed_rows..n)

			case ELEMENT_COLLAPSED:         break;// element was collapsed, so far only behavior:tabs is sending these two to the panels
			case ELEMENT_EXPANDED:          break;// element was expanded,

			}
			return FALSE; 
		}

	} DOMEventsHandler;

	/**
	*     作者：sonne
	*     日期：2017-04-19
	*     备注: 初始化获取用户名窗口
	*/
	VOID InitGetUsrnameWin()
	{
	}

	/**
	*     作者：sonne
	*     日期：2017-04-19
	*     备注: 创建获取用户名窗口
	*/
	VOID getUsrname(HINSTANCE hInstance)
	{
		hInst = hInstance;
		g_cWindow.Create(hInstance,&HTMLayoutNotifyHandler,&DOMEventsHandler,L"GetUsrname.html",InitGetUsrnameWin,NULL);

		return;
	}
}	

#endif