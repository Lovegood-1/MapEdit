#ifndef MAPDISPLAY_H
#define MAPDISPLAY_H

#include "Macro.h"
#include "Graph.h"
#include "SystemData.h"

#include <QPainter>
#include <QWheelEvent>
#include <QMouseEvent>

// ��̬ include
#ifdef USE_OPENGL
#include <QOpenGLWidget>
#else
#include <qwidget>
#endif

// ��̬���壡����
#ifdef USE_OPENGL
class CMapDisplay : public QOpenGLWidget
#else
class CMapDisplay : public Qwidget

#endif
{
public:
	CMapDisplay(QWidget* parent = nullptr);
	~CMapDisplay();


	// ���д��ڶ��л滭�����Ź��ܣ�������д����
	void paintEvent(QPaintEvent* event) override;
	void resizeEvent(QResizeEvent* event) override;
	void wheelEvent(QWheelEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void mouseDoubleClickEvent(QMouseEvent* event) override;



private:
	CGraph* m_pGraph;

	double m_dStartX;// ?your propose?
	double m_dStartY;

	bool m_bEditMode;
	bool m_bLBtnPressed;

	QPoint m_VClickPoint;
	QPoint m_VMovePoint;

};

#endif