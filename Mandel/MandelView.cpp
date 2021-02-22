
// MandelView.cpp: реализация класса CMandelView
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "Mandel.h"
#endif

#include "MandelDoc.h"
#include "MandelView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Набор констант для построения изображения:
#define CIMAX 1.2
#define CIMIN -1.2
#define CRMAX 1.0
#define CRMIN -2.0
#define NMAX 128
// Используемые цвета:
DWORD ColorTable[6] =
{ 0x0000ff, // красный
0x00ff00,  // зеленый
0xff0000,  // синий
0x00ffff,  // желтый
0xffff00,  // бирюзовый
0xff00ff }; // сиреневый

// CMandelView

IMPLEMENT_DYNCREATE(CMandelView, CView)

BEGIN_MESSAGE_MAP(CMandelView, CView)
	ON_WM_SIZE()
END_MESSAGE_MAP()

// Создание или уничтожение CMandelView

CMandelView::CMandelView() noexcept
{
	// TODO: добавьте код создания
	m_Col = 0;
}

CMandelView::~CMandelView()
{
}

BOOL CMandelView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Рисование CMandelView

void CMandelView::OnDraw(CDC* /*pDC*/)
{
	CMandelDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: добавьте здесь код отрисовки для собственных данных
	m_Col = 0;
	m_CR = (float)CRMIN;
}


// Диагностика CMandelView

#ifdef _DEBUG
void CMandelView::AssertValid() const
{
	CView::AssertValid();
}

void CMandelView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMandelDoc* CMandelView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMandelDoc)));
	return (CMandelDoc*)m_pDocument;
}
#endif //_DEBUG

void CMandelView::DrawCol()
{
	CClientDC ClientDC(this);
	float CI;
	int ColorVal;
	float I;
	float ISqr;
	float R;
	int Row;
	float RSqr;

	if (m_Col >= m_ColMax || GetParentFrame()->IsIconic())
		return;
	CI = (float)CIMAX;
	for (Row = 0; Row < m_RowMax; ++Row)
	{
		R = (float)0.0;
		I = (float)0.0;
		RSqr = (float)0.0;
		ISqr = (float)0.0;
		ColorVal = 0;
		while (ColorVal < NMAX && RSqr + ISqr < 4)
		{
			++ColorVal;
			RSqr = R * R;
			ISqr = I * I;
			I *= R;
			I += I + CI;
			R = RSqr - ISqr + m_CR;
		}
		ClientDC.SetPixelV(m_Col, Row, ColorTable[ColorVal % 6]);
		CI -= m_DCI;
	}
	m_Col++;
	m_CR += m_DCR;
}

// Обработчики сообщений CMandelView


void CMandelView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: добавьте свой код обработчика сообщений
	if (cx <= 1 || cy <= 1) // предотвратим деление на ноль
		return;
	m_ColMax = cx; // Текущие размеры окна представления
	m_RowMax = cy; // в единицах устройства (пикселях)
	m_DCR = (float)((CRMAX - CRMIN) / (m_ColMax - 1));
	m_DCI = (float)((CIMAX - CIMIN) / (m_RowMax - 1));
}
