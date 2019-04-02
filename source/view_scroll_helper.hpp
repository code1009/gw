#pragma once



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class view_scroll_helper
{
private:
	float _contents_cx;
	float _contents_cy;
	float _view_xoffset;
	float _view_yoffset;
	float _window_cx;
	float _window_cy;

private:
	float _x;
	float _x_min;
	float _x_max;
	float _x_page;

	float _y;
	float _y_min;
	float _y_max;
	float _y_page;

private:
	HWND _hwnd;

	cx::bool_t _cf_xcenter;
	cx::bool_t _cf_ycenter;

public:
	view_scroll_helper();
	virtual ~view_scroll_helper();

private:
	int get_scroll_x      (void);
	int get_scroll_x_min  (void);
	int get_scroll_x_max  (void);
	int get_scroll_x_page (void);
	int get_scroll_y      (void);
	int get_scroll_y_min  (void);
	int get_scroll_y_max  (void);
	int get_scroll_y_page (void);

	void update_xscroll (void);
	void update_yscroll (void);

private:
	int x_to_xscroll (float v);
	int y_to_yscroll (float v);

	float xscroll_to_x (int v);
	float yscroll_to_y (int v);

private:
	void recalc_xscroll (void);
	void recalc_yscroll (void);

public:
	void initialize   (HWND hwnd, cx::bool_t cf_xcenter = true, cx::bool_t cf_ycenter = true);
	void set_contents (float cx, float cy, cx::bool_t update_scroll=false);
	void set_window   (int   cx, int   cy, cx::bool_t update_scroll=false);

	void on_xscroll(UINT code, int nPos);
	void on_yscroll(UINT code, int nPos);

	int get_view_xoffset (void);
	int get_view_yoffset (void);
};


