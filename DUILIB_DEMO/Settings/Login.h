#if 0
#pragma once
namespace LOGIN {
	
	CWINDOWS g_cWindow;
	HANDLE g_hThread;
	HANDLE g_get_conn_state_thread;
	BOOL g_bFinger = FALSE;
	BOOL g_bSucceed = TRUE;
	char g_szName[MAX_PATH] = { 0 };
	char g_szPwd[MAX_PATH] = { 0 };
	static BOOL g_bExitThread = FALSE;
	htmlayout::dom::element g_html_conn;


	void OnButtonClick(HELEMENT button)
	{
		htmlayout::dom::element cBut = button;
		if (!wcscmp(cBut.get_attribute("id"),L"EXIT"))
		{
			TerminateThread(g_get_conn_state_thread,0);

			g_bExitThread = TRUE;
			WaitForSingleObject(g_hThread, 1000);
			g_bSucceed = FALSE;
			PostMessage(g_cWindow.GetHandle(), WM_DESTROY, NULL, NULL);
		}
	}
	


	void OnPopup(HELEMENT hPOPUP)
	{
		htmlayout::dom::element Popup = hPOPUP;
		Popup.destroy();
	}
	


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
		//************************************
		// 作      者:	李峰
		// 函  数  名:  handle_event
		// 功      能:  HTMLayout事件响应函数
		// 完  整  名:  LOGIN::DOMEventsHandlerType::handle_event
		// 访  问  权:  virtual public 
		// 返回值类型:  BOOL
		// 方法限定符: 	
		// 参      数: 	HELEMENT he
		// 参      数: 	BEHAVIOR_EVENT_PARAMS & params
		//************************************
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
			case POPUP_REQUEST:				OnPopup(params.heTarget);		break;// request to show popup just received, 
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
	*    作者：sonne
	*    功能：设备端验证，流程：1PC发送本地证书到设备 2设备验证
	*    日期：2017-06-22
	*/
	void validate_by_dev() {
		int num;
		// 验证测试
		sel_admin_ret *sel_admins = MYSQL_INTERFACES::select_all_admins("", &num);
		admin_login(sel_admins, num, g_chLoginAdminName);
		delete[] sel_admins;
		sel_admins = NULL;
	}


	DWORD WINAPI ValidateFinger(LPVOID lpParameter) {
		validate_by_dev();
		//TerminateThread(g_get_conn_state_thread,0);
		SendMessage(g_cWindow.GetHandle(), WM_DESTROY, NULL, NULL);
		return 0;
	}


	static VOID CALLBACK TimerProc(HWND hwnd, UINT uMsg, _In_ UINT_PTR idEvent, DWORD dwTime) {
		g_bExitThread = TRUE;
		Sleep(1000);
		KillTimer(hwnd, idEvent);
		//MessageBoxA(hwnd, "扫描指静脉超时!", NULL, NULL);
		//MSG_TIP::create_my_tip(g_hInst,L"扫描指静脉超时!");
		ExitProcess(0);
	}


	DWORD WINAPI get_conn_state(LPVOID lpParameter) {
		for(;;) {
			htmlayout::dom::element root = htmlayout::dom::element::root_element(g_cWindow.GetHandle());
			g_html_conn = root.get_element_by_id("MSG");
			Sleep(200);
			json::value value;
			if (g_is_conn == true)
				value = "设备已连接";
			else 
				value = "设备未连接";
			g_html_conn.set_value(value);
		}
		return 0;
	}

	/**
	 *   窗口初始化函数
	 */
	VOID init_login() {
		g_hThread = CreateThread(NULL,NULL,ValidateFinger,NULL,NULL,NULL);
		//g_get_conn_state_thread = CreateThread(NULL,NULL,get_conn_state,NULL,NULL,NULL);
		//SetTimer(g_cWindow.GetHandle(), 1, 60000, TimerProc);
		SetForegroundWindow( g_cWindow.GetHandle() );
		SetWindowText(g_cWindow.GetHandle(),"身份认证系统");
		return;
	}
	

	/**
	 *   创建登录窗口
	 */
	BOOL login(HINSTANCE hInstance) {
		WCHAR ws_path[20];
		wcscpy(ws_path,L"login1.html");
		g_bFinger = FALSE;
		g_bExitThread = FALSE;
		g_cWindow.Create(hInstance,&HTMLayoutNotifyHandler,&DOMEventsHandler,ws_path,init_login,NULL);
		return g_bSucceed;
	}

}

#endif