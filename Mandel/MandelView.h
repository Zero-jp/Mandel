
// MandelView.h: интерфейс класса CMandelView
//

#pragma once


class CMandelView : public CView
{
private:
	int m_Col;	// Номер следующего столбца пикселей
	int m_ColMax;	// Последний столбец
	float m_CR;	// Используются
	float m_DCI;	// при масштабировании
	float m_DCR;	// изображения
	int m_RowMax;	// Последняя строка

public:
	void DrawCol(); // Рисование очередного столбца

protected: // создать только из сериализации
	CMandelView() noexcept;
	DECLARE_DYNCREATE(CMandelView)

// Атрибуты
public:
	CMandelDoc* GetDocument() const;

// Операции
public:

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Реализация
public:
	virtual ~CMandelView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // версия отладки в MandelView.cpp
inline CMandelDoc* CMandelView::GetDocument() const
   { return reinterpret_cast<CMandelDoc*>(m_pDocument); }
#endif

