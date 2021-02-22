
// Mandel.h: основной файл заголовка для приложения Mandel
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// CMandelApp:
// Сведения о реализации этого класса: Mandel.cpp
//

class CMandelApp : public CWinApp
{
public:
	CMandelApp() noexcept;


// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnIdle(LONG lCount);
};

extern CMandelApp theApp;
