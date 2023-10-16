/*
��������Ҫ����֮һ
���ܣ�
	1. ��ͼ����Ӧ��ꡢ���̡����ֵ��¼���
	2. ���� CSystemData �еĵ�ͱ�
��������Ҫ���� -> CSystemData
*/


#include "MapDisplay.h"

CMapDisplay::CMapDisplay(QWidget* parent): QOpenGLWidget(parent)
{
	m_pSystem		  = CSystemData::GetSystemData();
 	m_pGraph		  = CSystemData::GetSystemData()->GetGraph();

	m_dStartX		  = 0.0;
	m_dStartY		  = 0.0;
	m_dScale		  = 1.0;
	m_bEditMode		  = false;
	m_bLBtnPressed	  = false;
	m_bCtrlPressed	  = false;
	m_bAltPressed     = false;
	m_dEditAreaX1 = 0.0;
	m_dEditAreaX2 = 0.0;
	m_dEditAreaY1 = 0.0;
	m_dEditAreaY2 = 0.0;
 

	setMouseTracking(true);
	setFocusPolicy(Qt::FocusPolicy::WheelFocus);

}

CMapDisplay::~CMapDisplay()
{

}

 
void CMapDisplay::paintEvent(QPaintEvent* event)
{
	constexpr int DIAMETER = NODE_RADIUS * 2;
	// 1. Ϊ�˷�ֹ�����ǣ�����ϵͳ�滭��
#ifdef USE_OPENGL
	QOpenGLWidget::paintEvent(event);
#endif // USE_OPENGL

	double dImageWidth = m_pGraph->m_MapImage.width() * m_dScale;
	double dImageHeight = m_pGraph->m_MapImage.height() * m_dScale;
	double dConnectNode1PosX = 0.0;
	double dConnectNode2PosY = 0.0;

	QPainter painter(this);
	painter.drawImage(QRectF(m_dStartX, m_dStartY, dImageWidth, dImageHeight), m_pGraph->m_MapImage);

	QVector<CNode>::const_iterator cit = m_pGraph->m_NodeVec.constBegin();

	while (cit != m_pGraph->m_NodeVec.constEnd())
	{
		painter.setPen(Qt::PenStyle::NoPen);
		painter.setBrush(cit->m_NodeType == NodeType::Node_Road ? m_pSystem->GetRoadNodeBrush() : m_pSystem->GetBuildingNodeBrush());
		painter.drawEllipse(QRectF(
			m_dStartX + (cit->m_dNodePosX - NODE_RADIUS) * m_dScale,
			m_dStartY + (cit->m_dNodePosY - NODE_RADIUS) * m_dScale,
			DIAMETER * m_dScale,
			DIAMETER * m_dScale));

		// ���ڵ�ǰѡ�еĵ�
		if (cit->m_iNodeId == m_ConnectNode1.m_iNodeId)
		{
			dConnectNode1PosX = cit->m_dNodePosX;
			dConnectNode2PosY = cit->m_dNodePosY;
		}
		cit++;
	}

	painter.setPen(m_pSystem->GetEdgePen());
	QVector<CEdge>::const_iterator  cite = m_pGraph->m_EdgeVec.constBegin();
	while (cite != m_pGraph->m_EdgeVec.constEnd())
	{
		painter.drawLine(QLineF(
			QPoint(
				m_dStartX + cite->m_Node1.m_dNodePosX * m_dScale,
				m_dStartY + cite->m_Node1.m_dNodePosY * m_dScale),
			QPointF(
				m_dStartX + cite->m_Node2.m_dNodePosX * m_dScale,
				m_dStartY + cite->m_Node2 .m_dNodePosY * m_dScale)));
		cite++;
	}


	// ��ѡ����
	if (m_dEditAreaX1 != 0.0 &&
		m_dEditAreaX2 != 0.0 &&
		m_dEditAreaY1 != 0.0 &&
		m_dEditAreaY2 != 0.0)
	{
		painter.setPen(m_pSystem->GetEditAreaPen());
		painter.setBrush(Qt::BrushStyle::NoBrush);
		painter.drawRect(QRectF(
			QPoint(m_dStartX + m_dEditAreaX1 * m_dScale, m_dStartY + m_dEditAreaY1 * m_dScale),
			QPoint(m_dStartX + m_dEditAreaX2 * m_dScale, m_dStartY + m_dEditAreaY2 * m_dScale)
		)); // TODO-����任
	}


	// ��̬���߹���
	if (m_bEditMode && m_ConnectNode1.m_iNodeId != ERROR_NODE_ID)
	{
		painter.setPen(m_pSystem->GetConnectPen());
		painter.drawLine(QLineF(
			QPoint(
				m_dStartX + dConnectNode1PosX * m_dScale,
				m_dStartY + dConnectNode2PosY * m_dScale), 
			QPointF(m_EMovePoint)));
	}


 
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
	if (m_bEditMode)
	{


	}
	else
	{
		if (event->angleDelta().y() > 0)
		{
			double dMousePosX = (double)m_VMovePoint.x();
			double dMousePosY = (double)m_VMovePoint.y();
			double dScale = m_dScale;
			m_dScale = std::min(dScale * (1 + SCALE_SPEED) , (double)MAX_SCALE ) ;
			m_dStartX = dMousePosX - (dMousePosX - m_dStartX) / dScale * m_dScale;
			m_dStartY = dMousePosY - (dMousePosY - m_dStartY) / dScale * m_dScale;
			update();
		}
		else if (event->angleDelta().y() < 0)
		{
			double dMousePosX = (double)m_VMovePoint.x();
			double dMousePosY = (double)m_VMovePoint.y();
			double dScale = m_dScale;
			m_dScale = std::max(dScale * (1 - SCALE_SPEED), (double)1/MAX_SCALE);
			m_dStartX = dMousePosX - (dMousePosX - m_dStartX) / dScale * m_dScale;
			m_dStartY = dMousePosY - (dMousePosY - m_dStartY) / dScale * m_dScale;
			update();
		}


	}


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
		 
		m_EMovePoint = event->pos();
		if (m_bAltPressed && m_bLBtnPressed)
		{
			double dMousePosX = (m_EMovePoint.x() - m_dStartX) / m_dScale;
			double dMousePosY = (m_EMovePoint.y() - m_dStartY) / m_dScale;

			// ���ܣ���ѡ���ܵĵڶ�������������ƶ��仯
			m_dEditAreaX2 = dMousePosX;
			m_dEditAreaY2 = dMousePosY;
			update();
			
		}

		if(m_ConnectNode1.m_iNodeId != ERROR_NODE_ID)
			update();
	}
	else
	{
		// ��ȡ�ƶ����룬�޸Ļ�ͼ���������
		// �ƺ������Ż�
		//m_VClickPoint = m_VMovePoint;
		//m_VMovePoint = event->pos();
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
		m_EClickPoint = event->pos();
		if (event->button() == Qt::MouseButton::LeftButton)
		{
			m_bLBtnPressed = true;
			// dMousePosX - ͼƬ����
			double dMousePosX = (m_EClickPoint.x() - m_dStartX) / m_dScale;
			double dMousePosY = (m_EClickPoint.y() - m_dStartY) / m_dScale;
 

			if (m_bAltPressed)
			{
				m_dEditAreaX1 = dMousePosX;
				m_dEditAreaY1 = dMousePosY;
				m_dEditAreaX2 = m_dEditAreaX1;
				m_dEditAreaY2 = m_dEditAreaY1;  // ? ���Ϊʲôһ�£�Ӧ����press-���ϣ�move-����
				update();
			}
			else
			{
				emit Signal_NodeCreated(dMousePosX, dMousePosY);
			}


		}

		else if (event->button() == Qt::MouseButton::RightButton)
		{
			

			if (m_ConnectNode1.m_iNodeId == ERROR_NODE_ID && m_ConnectNode2.m_iNodeId == ERROR_NODE_ID)
			{
				fn_GetNodeId(
					((double)m_EClickPoint.x() - m_dStartX) / m_dScale, 
					((double)m_EClickPoint.y() - m_dStartY) / m_dScale, 
					m_ConnectNode1 );
			}
			else if (  !m_bCtrlPressed && m_ConnectNode1.m_iNodeId != ERROR_NODE_ID && m_ConnectNode2.m_iNodeId == ERROR_NODE_ID)
			{
				fn_GetNodeId(
					((double)m_EClickPoint.x() - m_dStartX) / m_dScale,
					((double)m_EClickPoint.y() - m_dStartY) / m_dScale,
					m_ConnectNode1 );
			}
			else if (m_bCtrlPressed && m_ConnectNode1.m_iNodeId != ERROR_NODE_ID && m_ConnectNode2.m_iNodeId == ERROR_NODE_ID)
			{
				// Ӧ�ô����µı���
				// 1 ���ѡ�еڶ����� 2 ȥ�ظ�
				fn_GetNodeId(
					((double)m_EClickPoint.x() - m_dStartX) / m_dScale,
					((double)m_EClickPoint.y() - m_dStartY) / m_dScale,
					m_ConnectNode2 );

				if (m_ConnectNode2.m_iNodeId != ERROR_NODE_ID)
				{
					bool bCreate = true;
					QVector<CEdge>::const_iterator cit = m_pGraph->m_EdgeVec.constBegin();
					while (cit != m_pGraph->m_EdgeVec.constEnd())
					{
						if (cit->m_Node1 == m_ConnectNode1 && cit->m_Node2 == m_ConnectNode2)
						{
							bCreate = false;
							break;
						}
						else if(cit->m_Node1 == m_ConnectNode2 && cit->m_Node2 == m_ConnectNode1)
						{
							bCreate = false;
							break;
						}
						cit++;
					}

					if (bCreate)
					{
						CEdge edge;
						edge.m_iEdgeId = m_pGraph->m_iMaxEdgeId++;
						edge.m_Node1 = m_ConnectNode1;
						edge.m_Node2 = m_ConnectNode2;
						m_pGraph->m_EdgeVec.push_back(edge);
					}
					else
					{
						QMessageBox msgBox;
						msgBox.setText(tr("Edge already existed"));
						msgBox.exec();
					}

					m_ConnectNode1 = CNode();
					m_ConnectNode2 = CNode();

				}

			}
		}
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
		if (event->button() == Qt::MouseButton::LeftButton)
		{
			m_bLBtnPressed = false;
		}
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
	if (m_bEditMode)
	{

	}
	else
	{
		// �����㷨
		if (event->button() == Qt::MouseButton::LeftButton)
		{
			m_dStartX = (width() - m_pGraph->m_MapImage.width()) / 2.0;
			m_dStartY = (height() - m_pGraph->m_MapImage.height()) / 2.0;
			m_dScale = 1.0;
			update();
		}
	}


#ifdef USE_OPENGL
	QOpenGLWidget::mouseDoubleClickEvent(event);
#else
	QWidget::mouseDoubleClickEvent(event);
#endif
}

void CMapDisplay::keyPressEvent(QKeyEvent* event)
{

	if (event->key() == Qt::Key::Key_Control)
	{
		m_bCtrlPressed = true;
	}
	else if (event->key() == Qt::Key::Key_Alt && !m_bLBtnPressed)
	{
		m_bAltPressed = true;
	}

#ifdef USE_OPENGL
	QOpenGLWidget::keyPressEvent(event);
#else
	QWidget::keyPressEvent(event);
#endif
}

void CMapDisplay::keyReleaseEvent(QKeyEvent* event)
{
	if (event->key() == Qt::Key::Key_Control)
	{
		m_bCtrlPressed = false;
	}
	else if (event->key() == Qt::Key::Key_Alt)
	{
		m_bAltPressed = false;
	}


#ifdef USE_OPENGL
	QOpenGLWidget::keyReleaseEvent(event);
#else
	QWidget::keyReleaseEvent(event);
#endif
}

int CMapDisplay::fn_GetNodeId(const double& dPosX, const double& dPosY, CNode& node)
{
	double dThreshold = m_pSystem->GetRadiusThreshold();
	double dCurMinThreshold = 99999;
	QVector<CNode>::const_iterator cit = m_pGraph->m_NodeVec.constBegin();
	while (cit != m_pGraph->m_NodeVec.constEnd())
	{
		double dTempThreshold = sqrt(pow(cit->m_dNodePosX - dPosX, 2.0) + pow(cit->m_dNodePosY - dPosY, 2.0));
	 
		if (dTempThreshold < dThreshold )
		{
			node = *cit;
			dThreshold = dTempThreshold;
			 
		}
		cit++;
	}
	return NORMAL_RETURN;
}
