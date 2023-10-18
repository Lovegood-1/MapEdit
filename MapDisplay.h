#ifndef MAPDISPLAY_H
#define MAPDISPLAY_H

#include "Macro.h"
#include "Graph.h"
#include "SystemData.h"

#include <QMenu>
#include <QEvent>
#include <QAction>
#include <QPainter>
#include <QMessageBox>
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
	Q_OBJECT
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
	void keyPressEvent(QKeyEvent* event) override;
	void keyReleaseEvent(QKeyEvent* event) override;


	inline void		   SetEditMode(const bool& bEdieMode) { m_bEditMode = bEdieMode; }
	inline const bool& GetEditMode() const				  { return m_bEditMode; }

private:
 	int fn_GetNodeId(const double& dPosX, const double& dPosY, CNode& node);
	int fn_DeleteNodes();
	int fn_DeleteEdges();

signals:
	void Signal_NodeCreated(double dPosX, double dPosY);

private:
	CSystemData* m_pSystem;
	CGraph* m_pGraph;

	double m_dStartX;// ?your propose?
	double m_dStartY;
	double m_dScale;

	bool m_bEditMode;
	bool m_bLBtnPressed;
	bool m_bCtrlPressed;
	bool m_bAltPressed;

	QPoint m_VClickPoint;
	QPoint m_VMovePoint;

	QPoint m_EClickPoint;
	QPoint m_EMovePoint;

	// ����ʱ��Ķ�̬������
	CNode m_ConnectNode1;
	CNode m_ConnectNode2;

	// ��ѡ�༭�����ܵĲ���
	double m_dEditAreaX1;  // ���
	double m_dEditAreaY1;  // ���
	double m_dEditAreaX2;  // �ƶ�
	double m_dEditAreaY2;  // �ƶ�

};

#endif