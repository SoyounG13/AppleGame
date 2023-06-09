
// ChildView.h: CChildView 클래스의 인터페이스
//


#pragma once


// CChildView 창
class Apple
{
public:
	int x;
	int y;
	int num;
	bool select;
	bool done;

	Apple() {	}
	Apple(int x, int y, int num)
	{
		this->x = x;
		this->y = y;
		this->num = num;
		select = false;
		done = false;
	}
};

class CChildView : public CWnd
{
// 변수 선언
public:
	CImage start;
	CImage background;
	CImage apple[10];
	CImage sapple[10];
	CImage w[10];
	CImage b[10];
	CImage timeOver;

	Apple *apples[180];

	int point_x_start;
	int point_y_start;
	int point_x_end;
	int point_y_end;
	int apple_sum;
	int score;
	int timer_num;

	bool rect_draw;
	bool timer_on;
	bool start_menu_on;
	bool game_menu_on;

// 함수 선언
public:
	void DrawRectangle(CPaintDC& dc, int x1, int y1, int x2, int y2);
	void start_menu();
	void game_menu();

// 생성입니다.
public:
	CChildView();

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CChildView();

	// 생성된 메시지 맵 함수
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

