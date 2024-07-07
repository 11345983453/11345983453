#include "Window.h"
//ExMessage Window::m_msg;//要写到 cpp里面来 
Window::Window(int w, int h, int flag)
{
	m_handle = ::initgraph(w, h, flag);//初始化一个宽度为 w，高度为 h，标志为 flag 的图形窗口
	::setbkmode(TRANSPARENT);//设置背景模式为透明
}
void Window::setWindowTitle(const std::string& title)
{
	::SetWindowText(m_handle, title.c_str());//就是调用库的函数在类内内部，设置窗口的标题，m_handle 是窗口句柄
}

int Window::width()
{
	return ::getwidth();
}

int Window::height()
{
	return ::getheight();
}

void Window::clear()
{
	::cleardevice(); //这些都是把easyx库的写入类内  就是清屏，
}
//开始绘制
void Window::beginDraw()
{
	::BeginBatchDraw(); //画图等等相关的
}
//刷新
void Window::flushDraw()
{
	::FlushBatchDraw();
}
//结束绘制
void Window::endDraw()
{
	::EndBatchDraw();
}
//等待用户输入，返回输入字符
int Window::exec() {

	return getchar();
}
