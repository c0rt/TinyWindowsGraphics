#ifndef TWG_WINDOW_INCLUDED
#define TWG_WINDOW_INCLUDED

#include <string>

#include "twg/basics.h"
#include "twg/point.h"
#include "twg/image.h"

namespace twg
{

	class 	WindowObject;
	class 	WindowBase;
	class 	WindowType;
	enum 	WindowStyle : int32u;

	//-------------------------------------------------------------------------
	/* Класс, который: запускает независимую обработку сообщений окна, и
	   вызывает оконную процедуру у соответствующего объекта каждый раз, когда 
	   она вызывается операционной системой.
	 */
	class WindowObject
	{
	public:
		WindowObject() {}
		~WindowObject();

		HWND getHwnd(void);
		void waitForClose(void);
		bool isClosed(void);

		ImageWin 	canvas;
	protected:
		HWND 	m_hwnd;
		HDC 	m_hdc;

		void onStart();
		virtual HWND create(void* wndProc) {}
		virtual LRESULT wndProc(HWND hwnd, 
								UINT msg,
								WPARAM wParam, 
								LPARAM lParam) {}

		friend DWORD WINAPI 	makeWindow(LPVOID data);
		friend LRESULT CALLBACK wndProc1(HWND hwnd, 
										UINT msg, 
										WPARAM wParam, 
										LPARAM lParam);
	};

	//-------------------------------------------------------------------------
	/* Класс для настройки внешнего вида окна. */
	class WindowBase : public WindowObject
	{
	public:
		WindowBase(WindowType type);
		~WindowBase();  // Окно автоматически закрывается, здесь вызывается функция по закрытия окна.

		Point_i 	getClientSize(void);
		Point_i 	getWindowSize(void);
		Point_i 	getPos(void);
		Point_i 	getMaxSize(void);
		Point_i 	getMinSize(void);
		std::string getCaption(void);
		WindowStyle getStyle(void);

		void setClientSize(Point_i size);
		void setWindowSize(Point_i size);
		void setPos(Point_i pos);
		void setMaxSize(Point_i maxSize);
		void setMinSize(Point_i minSize);
		void setCaption(std::string caption);
		void setStyle(WindowStyle style);

		void invalidateScreen(void);

		// Надо ли? Это вносит лишь лишних костылей, а пользы немного.
		// void setTaskbarColor(TaskbarColor clr);
		// void setTaskbarProgress(double progress);
		// void setFullScreen(bool isFullScreen);
	protected:
		Point_i		m_minSize;
		Point_i		m_maxSize;
		WindowType*	m_type;
		std::string m_className;
	
		HWND 	create(void* wndProc) override;
		LRESULT wndProc(HWND hwnd, 
						UINT msg,
						WPARAM wParam, 
						LPARAM lParam) override;

		// По умолчанию возвращает DefWindowProc(hwnd, msg, wParam, lParam);
		virtual LRESULT wndProcNext(HWND hwnd, 
									UINT msg,
									WPARAM wParam, 
									LPARAM lParam);
	};

	//-------------------------------------------------------------------------
	class WindowType 
	{
	public:
		WindowType(int32		iconNo,
				   Point_i		pos,
				   Point_i		size,
				   Point_i		minSize,
				   Point_i		maxSize,
				   std::string 	caption,
				   WindowStyle	style) : 
			iconNo(iconNo),
			pos(pos),
			size(size),
			minSize(minSize),
			maxSize(maxSize),
			caption(caption),
			style(style) {}

		int32		iconNo;
		Point_i		pos;
		Point_i		size;
		Point_i		minSize;
		Point_i		maxSize;
		std::string caption;
		WindowStyle	style;
	};

	enum WindowStyle : int32u
	{
		// Среди этих можно выбрать только один
		WINDOW_STANDART 	= 0,
		WINDOW_TOOL 		= 1,
		WINDOW_CAPTION 		= 2,
		WINDOW_POPUP 		= 3,
		WINDOW_NO_BORDER 	= 4,

		// Обозначает количество стилей окна
		WINDOW_MAX_TYPE 	= 5,

		//---------------------------------------------------------------------
		// Стили далее могут объединяться через оператор |
		WINDOW_ON_TOP 		= 0x010,
		WINDOW_DISABLED 	= 0x020,
		WINDOW_MAXIMIZED 	= 0x040,
		WINDOW_MAX_BUTTON 	= 0x080,
		WINDOW_MIN_BUTTON 	= 0x100,

		// Данный стиль можно задать только при создании окна
		WINDOW_DROP_SHADOW 	= 0x200
	};

	// enum TaskbarColor
	// {
	// 	TASKBAR_GREEN,
	// 	TASKBAR_YELLOW,
	// 	TASKBAR_RED,
	// 	TASKBAR_LOADING,
	// 	TASKBAR_BLINK
	// };

}

#endif // TWG_WINDOW_INCLUDED