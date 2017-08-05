#ifndef TWG_WINDOW_EVENTS_INCLUDED
#define TWG_WINDOW_EVENTS_INCLUDED

#include "twg/events.h"
#include "twg/window.h"
#include "twg/basics.h"
#include "twg/point.h"

namespace twg
{

	class WindowEvents : public WindowBase, public EventsHandler
	{
	public:
		WindowEvents(WindowType type) : 
			WindowBase(type), 
			EventsHandler(nullptr) {}
	protected:
		// Эта функция посылает все необычные сообщения в onMessage
		LRESULT wndProcNext(HWND hwnd, 
							UINT msg,
							WPARAM wParam, 
							LPARAM lParam);
	};
	
}

#endif // TWG_WINDOW_EVENTS_INCLUDED