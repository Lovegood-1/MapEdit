#include "MapDisplay.h"

CMapDisplay::CMapDisplay(QWidget* parent): QOpenGLWidget(parent)
{
 	m_pGraph = CSystemData::GetSystemData()->GetGraph();
	m_dStartX = 0.0;
	m_dStartY = 0.0;
	m_bEditMode = false;
	m_bLBtnPressed = false;

}

CMapDisplay::~CMapDisplay()
{

}

/*
Qusetion :
1. 什么时候会触发这个事件？点的时候？
	- 初始化的时候
	- update
	- repaint()
*/
void CMapDisplay::paintEvent(QPaintEvent* event) 
{
	// 1. 为了防止被覆盖，先让系统绘画，
#ifdef USE_OPENGL
	QOpenGLWidget::paintEvent(event);
#endif // USE_OPENGL


	double dImageWidth = m_pGraph->m_MapImage.width();
	double dImageHeight = m_pGraph->m_MapImage.height();

	QPainter painter(this);
	painter.drawImage(QRectF(m_dStartX, m_dStartY, dImageWidth, dImageHeight), m_pGraph->m_MapImage);
 
 
#ifndef USE_OPENGL
	QWidget::paintEvet(event);
#endif 



}

void CMapDisplay::resizeEvent(QResizeEvent* event)
{
#ifdef USE_OPENGL
	QOpenGLWidget::resizeEvent(event);
#else
	QWidget::resizeEvent(event);
#endif
}

void CMapDisplay::wheelEvent(QWheelEvent* event)
{
#ifdef USE_OPENGL
	QOpenGLWidget::wheelEvent(event);
#else
	QWidget::wheelEvent(event);
#endif
}

void CMapDisplay::mouseMoveEvent(QMouseEvent* event)
{
	if (m_bEditMode)
	{

	}
	else
	{
		// 获取移动距离，修改绘图的起点坐标
		// 似乎可以优化

		if (m_bLBtnPressed)
		{
			m_VClickPoint = m_VMovePoint;
			m_VMovePoint = event ->pos();
			QPoint dis = m_VMovePoint - m_VClickPoint;
			m_dStartX += (double)dis.x();
			m_dStartY += (double)dis.y();

			update();
		}
	}



#ifdef USE_OPENGL
	QOpenGLWidget::mouseMoveEvent(event);
#else
	QWidget::mouseMoveEvent(event);
#endif
}

void CMapDisplay::mousePressEvent(QMouseEvent* event)
{
	if (m_bEditMode)
	{

	}
	else
	{
		m_VClickPoint = event ->pos();
		m_VMovePoint = m_VClickPoint;
		if (event->button() == Qt::MouseButton::LeftButton)
		{
			m_bLBtnPressed = true;
		}

	}




#ifdef USE_OPENGL
	QOpenGLWidget::mousePressEvent(event);
#else
	QWidget::mousePressEvent(event);
#endif
}

void CMapDisplay::mouseReleaseEvent(QMouseEvent* event)
{
	if (m_bEditMode)
	{
	}
	else
	{
		if (event->button() == Qt::MouseButton::LeftButton)
		{
			m_bLBtnPressed = false;
		}
	}



#ifdef USE_OPENGL
	QOpenGLWidget::mouseReleaseEvent(event);
#else
	QWidget::mouseReleaseEvent(event);
#endif
}

void CMapDisplay::mouseDoubleClickEvent(QMouseEvent* event)
{
#ifdef USE_OPENGL
	QOpenGLWidget::mouseDoubleClickEvent(event);
#else
	QWidget::mouseDoubleClickEvent(event);
#endif
}
