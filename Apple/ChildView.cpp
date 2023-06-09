
// ChildView.cpp: CChildView 클래스의 구현
//

#include "stdafx.h"
#include "Apple.h"
#include "ChildView.h"
#include <cstdlib>
#include <ctime>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WIDTH_S		43
#define WIDTH_E		1367
#define WIDTH_B		8

#define HEIGHT_S	40
#define HEIGHT_E	756
#define HEIGHT_B	6

#define APPLE_P		65
#define APPLE_NUM	180

#define GAME_TIMER	0
#define APPLE_TIMER	1

// CChildView

CChildView::CChildView()
{
	CString s_apple;
	CString s_sapple;
	CString w_num;
	CString b_num;

	start.Load(L"image/start.png");
	background.Load(L"image/background.png");
	timeOver.Load(L"image/timeover.png");

	for (int i = 1; i <= 9; i++)
	{
		s_apple.Format(L"image/apple%d.png", i);
		s_sapple.Format(L"image/sapple%d.png", i);

		apple[i].Load(s_apple);
		sapple[i].Load(s_sapple);
	}

	for (int i = 0; i <= 9; i++)
	{
		w_num.Format(L"image/w%d.png", i);
		b_num.Format(L"image/b%d.png", i);

		w[i].Load(w_num);
		b[i].Load(b_num);
	}

	start_menu_on = false;
	game_menu_on = false;

	start_menu();
}

CChildView::~CChildView()
{
}

void CChildView::DrawRectangle(CPaintDC& dc, int x1, int y1, int x2, int y2)
{
	CPen pen;
	pen.CreatePen(PS_SOLID, 5, RGB(0, 0, 255));

	CPen* oldPen = dc.SelectObject(&pen);

	dc.MoveTo(x1, y1);
	dc.LineTo(x1, y2);
	dc.LineTo(x2, y2);
	dc.LineTo(x2, y1);
	dc.LineTo(x1, y1);

	dc.SelectObject(oldPen);
}

void CChildView::start_menu()
{
	start_menu_on = true;
	game_menu_on = false;
	timer_on = false;
	rect_draw = false;
}

void CChildView::game_menu()
{
	start_menu_on = false;
	game_menu_on = true;
	rect_draw = false;

	apple_sum = 0;
	score = 0;
	timer_num = 120;

	SetTimer(APPLE_TIMER, 1000, NULL);
	timer_on = true;

	int num = 0;
	for (int y = HEIGHT_S + HEIGHT_B; y < HEIGHT_E - APPLE_P; y += APPLE_P + HEIGHT_B)
	{
		for (int x = WIDTH_S + WIDTH_B; x < WIDTH_E - APPLE_P; x += APPLE_P + WIDTH_B)
		{
			apples[num] = new Apple(x, y, rand() % 9 + 1);
			num++;
		}
	}
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (start_menu_on)
		start.Draw(dc, 0, 0);
	else if (game_menu_on)
	{
		background.Draw(dc, 0, 0);

		for (int i = 0; i < APPLE_NUM; i++)
		{
			if (apples[i]->done)
				continue;
			else if (apples[i]->select)
				sapple[apples[i]->num].Draw(dc, apples[i]->x, apples[i]->y);
			else
				apple[apples[i]->num].Draw(dc, apples[i]->x, apples[i]->y);
		}

		if (rect_draw)
			DrawRectangle(dc, point_x_start, point_y_start, point_x_end, point_y_end);

		int temp_score = score;
		if (score >= 100)
		{
			int n100, n10, n1;

			n100 = temp_score / 100;
			temp_score -= n100 * 100;
			n10 = temp_score / 10;
			temp_score -= n10 * 10;
			n1 = temp_score;

			w[n100].Draw(dc, 1432, 91);
			w[n10].Draw(dc, 1482, 91);
			w[n1].Draw(dc, 1532, 91);
		}
		else if (score >= 10)
		{
			int n10, n1;

			n10 = temp_score / 10;
			temp_score -= n10 * 10;
			n1 = temp_score;

			w[n10].Draw(dc, 1458, 91);
			w[n1].Draw(dc, 1508, 91);
		}
		else
		{
			w[temp_score].Draw(dc, 1483, 91);
		}

		int temp_timer = timer_num;
		if (timer_num >= 100)
		{
			int n100, n10, n1;

			n100 = temp_timer / 100;
			temp_timer -= n100 * 100;
			n10 = temp_timer / 10;
			temp_timer -= n10 * 10;
			n1 = temp_timer;

			b[n100].Draw(dc, 1407, 274);
			b[n10].Draw(dc, 1473, 274);
			b[n1].Draw(dc, 1539, 274);
		}
		else if (timer_num >= 10)
		{
			int n10, n1;

			n10 = temp_timer / 10;
			temp_timer -= n10 * 10;
			n1 = temp_timer;

			b[n10].Draw(dc, 1440, 274);
			b[n1].Draw(dc, 1506, 274);
		}
		else
		{
			b[temp_timer].Draw(dc, 1473, 274);

			if (timer_num == 0)
			{
				timeOver.Draw(dc, WIDTH_S, HEIGHT_S);
			}
		}
	}

	

	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
}



int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	srand(time(NULL));
	SetTimer(GAME_TIMER, 100, NULL);

	return 0;
}


void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch (nIDEvent)
	{
	case GAME_TIMER:
		RedrawWindow();
		break;

	case APPLE_TIMER:
		if (timer_num > 0)
			timer_num--;
		if (timer_num == 0)
		{
			timer_on = false;
			KillTimer(APPLE_TIMER);
		}
	}

	CWnd::OnTimer(nIDEvent);
}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return true;
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	int x, y;
	x = point.x;
	y = point.y;

	if (start_menu_on)
	{
		if (646 < x && x < 1037 && 553 < y && y < 664)
			game_menu();
	}

	else if (game_menu_on)
	{
		if (timer_on)
		{
			point_x_start = point_x_end = x;
			point_y_start = point_y_end = y;
			rect_draw = true;
		}

		if (1399 < x && x < 1494 && 658 < y && y < 753)
			game_menu();
		else if (1518 < x && x < 1613 && 658 < y && y < 753)
			start_menu();
	}

	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	rect_draw = false;

	int sum = 0;
	for (int i = 0; i < APPLE_NUM; i++)
	{
		if (apples[i]->select && !apples[i]->done)
			sum += apples[i]->num;
	}

	if (sum == 10)
	{
		for (int i = 0; i < APPLE_NUM; i++)
		{
			if (apples[i]->select)
			{
				apples[i]->done = true;
				score++;
			}
			apples[i]->select = false;
		}
		return;
	}
	else
	{
		for (int i = 0; i < APPLE_NUM; i++)
		{
			apples[i]->select = false;
		}
	}


	CWnd::OnLButtonUp(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (rect_draw)
	{
		point_x_end = point.x;
		point_y_end = point.y;

		int x_start, y_start, x_end, y_end;
		x_start = point_x_start < point_x_end ? point_x_start : point_x_end;
		x_end = point_x_start > point_x_end ? point_x_start : point_x_end;
		y_start = point_y_start < point_y_end ? point_y_start : point_y_end;
		y_end = point_y_start > point_y_end ? point_y_start : point_y_end;

		int x, y;
		int select_false;

		for (int i = 0; i < APPLE_NUM; i++)
		{
			x = apples[i]->x;
			y = apples[i]->y;
			select_false = 0;

			if (x_start < x && x < x_end && y_start < y && y < y_end)
				apples[i]->select = true;
			else
				select_false++;

			if (x_start < x + APPLE_P && x + APPLE_P < x_end && y_start < y && y < y_end)
				apples[i]->select = true;
			else
				select_false++;

			if (x_start < x && x < x_end && y_start < y + APPLE_P && y + APPLE_P < y_end)
				apples[i]->select = true;
			else
				select_false++;

			if (x_start < x + APPLE_P && x + APPLE_P < x_end && y_start < y + APPLE_P && y + APPLE_P < y_end)
				apples[i]->select = true;
			else
				select_false++;

			if (x_start < x && x < x_end && y_start < y + APPLE_P / 2 && y + APPLE_P / 2 < y_end)
				apples[i]->select = true;
			else
				select_false++;

			if (x_start < x + APPLE_P / 2 && x + APPLE_P / 2 < x_end && y_start < y && y < y_end)
				apples[i]->select = true;
			else
				select_false++;

			if (x_start < x + APPLE_P/2 && x + APPLE_P/2 < x_end && y_start < y + APPLE_P && y + APPLE_P < y_end)
				apples[i]->select = true;
			else
				select_false++;

			if (x_start < x + APPLE_P && x + APPLE_P < x_end && y_start < y + APPLE_P/2 && y + APPLE_P/2 < y_end)
				apples[i]->select = true;
			else
				select_false++;

			if (select_false == 8)
				apples[i]->select = false;
		}
	}

	CWnd::OnMouseMove(nFlags, point);
}
