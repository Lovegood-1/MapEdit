/*
主窗口重要部件之一
功能：
	1. 绘图并相应鼠标、键盘、滚轮等事件。
	2. 管理 CSystemData 中的点和边
引出了重要对象 -> CSystemData
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
	// 1. 为了防止被覆盖，先让系统绘画，
#ifdef USE_OPENGL
	QOpenGLWidget::paintEvent(event);
#endif // USE_OPENGL

	double dImageWidth = m_pGraph->m_MapImage.width() * m_dScale;
	double dImageHeight = m_pGraph->m_MapImage.height() * m_dScale;
	double dConnectNode1PosX = 0.0;
	double dConnectNode2PosY = 0.0;

	// 1. 绘画背景
	QPainter painter(this);
	painter.drawImage(QRectF(m_dStartX, m_dStartY, dImageWidth, dImageHeight), m_pGraph->m_MapImage);

	// 2. 画边
	painter.setPen(m_pSystem->GetEdgePen());
	QVector<CEdge>::const_iterator  cite = m_pGraph->m_EdgeVec.constBegin();
	while (cite != m_pGraph->m_EdgeVec.constEnd())
	{
		painter.drawLine(QLineF(
			QPoint(
				fn_TransA2B(cite->m_Node1.m_dNodePosX, m_dStartX, m_dScale),
				fn_TransA2B(cite->m_Node1.m_dNodePosY, m_dStartY, m_dScale)), // 从地图系到窗口系的转换 dStartPoint + iPos_Map* dScale;
			QPoint(
				fn_TransA2B(cite->m_Node2.m_dNodePosX, m_dStartX, m_dScale),
				fn_TransA2B(cite->m_Node2.m_dNodePosY, m_dStartY, m_dScale))));
		cite++;
	}

	// 3. 画点:两种情况带id 或者不带id

	if (m_pSystem->GetShowNodeId())
	{
		QPen idPen = m_pSystem->GetNodeIdPen();
		QFont idFont = m_pSystem->GetNodeIdFont();
		int iHalfPixelSize = idFont.pixelSize() / 2;

		painter.setFont(idFont);
		QVector<CNode>::const_iterator cit = m_pGraph->m_NodeVec.constBegin();
		while (cit != m_pGraph->m_NodeVec.constEnd())
		{
			painter.setPen(Qt::PenStyle::NoPen);
			painter.setBrush(cit->m_NodeType == NodeType::Node_Road ? m_pSystem->GetRoadNodeBrush() : m_pSystem->GetBuildingNodeBrush());
			painter.drawEllipse(QRectF(
				m_dStartX + (cit->m_dNodePosX - NODE_RADIUS) * m_dScale, 
				m_dStartY + (cit->m_dNodePosY - NODE_RADIUS) * m_dScale,
				DIAMETER * m_dScale,
				DIAMETER * m_dScale));                                // 从地图系到窗口系的转换

			// 显示点的id
			painter.setPen(idPen);
			painter.drawText(
				QPointF(m_dStartX + (cit->m_dNodePosX + NODE_RADIUS) * m_dScale, m_dStartY + (cit->m_dNodePosY) * m_dScale - iHalfPixelSize), QString::number(cit->m_iNodeId) ) ;

			if (cit->m_iNodeId == m_ConnectNode1.m_iNodeId)
			{
				dConnectNode1PosX = cit->m_dNodePosX;
				dConnectNode2PosY = cit->m_dNodePosY;
			}
			cit++;
		}
	}
	else
	{
		painter.setPen(Qt::PenStyle::NoPen);
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

			// 对于当前选中的点
			if (cit->m_iNodeId == m_ConnectNode1.m_iNodeId)
			{
				dConnectNode1PosX = cit->m_dNodePosX;
				dConnectNode2PosY = cit->m_dNodePosY;
			}
			cit++;
		}
	}
	 

	// 框选功能
	if (m_dEditAreaX1 != 0.0 &&
		m_dEditAreaX2 != 0.0 &&
		m_dEditAreaY1 != 0.0 &&
		m_dEditAreaY2 != 0.0)
	{
		painter.setPen(m_pSystem->GetEditAreaPen());
		painter.setBrush(Qt::BrushStyle::NoBrush);
		painter.drawRect(QRectF(
			QPoint(m_dStartX + m_dEditAreaX1 * m_dScale, m_dStartY + m_dEditAreaY1 * m_dScale),   // 从地图系到窗口系的转换
			QPoint(m_dStartX + m_dEditAreaX2 * m_dScale, m_dStartY + m_dEditAreaY2 * m_dScale)
		)); // TODO-坐标变换
	}


	// 动态划线功能
	if (m_bEditMode && m_ConnectNode1.m_iNodeId != ERROR_NODE_ID)
	{
		painter.setPen(m_pSystem->GetConnectPen());
		painter.drawLine(QLineF(
			QPoint(
				fn_TransA2B(dConnectNode1PosX, m_dStartX, m_dScale),
				fn_TransA2B(dConnectNode2PosY, m_dStartY, m_dScale)),
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

			// 功能：框选功能的第二个点随着鼠标移动变化
			m_dEditAreaX2 = dMousePosX;
			m_dEditAreaY2 = dMousePosY;
			update();
			
		}

		if(m_ConnectNode1.m_iNodeId != ERROR_NODE_ID)
			update();
	}
	else
	{
		// 获取移动距离，修改绘图的起点坐标
		// 似乎可以优化
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
			// dMousePosX - 图片坐标
			double dMousePosX = (m_EClickPoint.x() - m_dStartX) / m_dScale;  // 从窗口系到地图系的转换
			double dMousePosY = (m_EClickPoint.y() - m_dStartY) / m_dScale;
 

			if (m_bAltPressed)
			{
				m_dEditAreaX1 = dMousePosX;
				m_dEditAreaY1 = dMousePosY;
				m_dEditAreaX2 = m_dEditAreaX1;
				m_dEditAreaY2 = m_dEditAreaY1;  // ? 这个为什么一致：应该是press-左上；move-右下
				update();
			}
			else
			{
				emit Signal_NodeCreated(dMousePosX, dMousePosY);
			}


		}

		else if (event->button() == Qt::MouseButton::RightButton)
		{
			if (m_bAltPressed &&
				m_dEditAreaX1!=0.0 &&
				m_dEditAreaY1!=0.0 &&
				m_dEditAreaX2!=0.0 &&
				m_dEditAreaY2!=0.0 )  
			{
				// 编辑模式 - 右击 ： 删除功能
				QMenu menu;
				const char *pDeleteNodes = "Delete Nodes";
				const char* pDeleteEdges = "Delete Edges";
				menu.addAction(tr(pDeleteNodes));
				menu.addAction(tr(pDeleteEdges));
				QAction* pRet = menu.exec(event->globalPos());
				if (pRet != nullptr && pRet->text() == tr(pDeleteNodes))
				{
					fn_DeleteNodes();
					update();
				}
				else if (pRet != nullptr && pRet->text() == tr(pDeleteEdges))
				{
					fn_DeleteEdges();
					update();
				}
			}
			else
			{
				// 编辑模式：边的创建功能
				// 
				// 因为边创建可能会走一半，所以会有边创建缓存(m_ConnectNode1,m_ConnectNode2)
	 
				//// 边的创建功能: 获取起始点
				if (m_ConnectNode1.m_iNodeId == ERROR_NODE_ID && m_ConnectNode2.m_iNodeId == ERROR_NODE_ID)
				{
					fn_GetNodeId(
						((double)m_EClickPoint.x() - m_dStartX) / m_dScale,             // 从窗口系到地图系的转换
						((double)m_EClickPoint.y() - m_dStartY) / m_dScale,
						m_ConnectNode1);
				}
				else if (!m_bCtrlPressed && m_ConnectNode1.m_iNodeId != ERROR_NODE_ID && m_ConnectNode2.m_iNodeId == ERROR_NODE_ID)
				{
					fn_GetNodeId(
						((double)m_EClickPoint.x() - m_dStartX) / m_dScale,            // 从窗口系到地图系的转换
						((double)m_EClickPoint.y() - m_dStartY) / m_dScale,
						m_ConnectNode1);

					if (m_ConnectNode1.m_iNodeId != ERROR_NODE_ID)
					{
						m_ConnectNode1 = CNode();
						m_ConnectNode2 = CNode();
					}
				}
				//  第二个点的选择与创建
				else if (m_bCtrlPressed && m_ConnectNode1.m_iNodeId != ERROR_NODE_ID && m_ConnectNode2.m_iNodeId == ERROR_NODE_ID)
				{
					
					fn_GetNodeId(
						((double)m_EClickPoint.x() - m_dStartX) / m_dScale,            // 从窗口系到地图系的转换
						((double)m_EClickPoint.y() - m_dStartY) / m_dScale,
						m_ConnectNode2);


					
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
							else if (cit->m_Node1 == m_ConnectNode2 && cit->m_Node2 == m_ConnectNode1)
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
						update();
					}
			 
				}
				update();
			
 

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
		// 居中算法
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

int CMapDisplay::fn_DeleteNodes()
{
	// 功能：框选的时候删除内部的节点，顺便删除点上的边
	double dx1 = m_dEditAreaX1 < m_dEditAreaX2 ? m_dEditAreaX1 : m_dEditAreaX2; // TODO: 这种重复的代码可以改
	double dx2 = m_dEditAreaX1 < m_dEditAreaX2 ? m_dEditAreaX2 : m_dEditAreaX1;
	double dy1 = m_dEditAreaY1 < m_dEditAreaY2 ? m_dEditAreaY1 : m_dEditAreaY2;
	double dy2 = m_dEditAreaY1 < m_dEditAreaY2 ? m_dEditAreaY2 : m_dEditAreaY1;

	// 先遍历边，如果两个顶点任意一个在区域内，则移除。
	QVector<CEdge>::iterator ite = m_pGraph->m_EdgeVec.begin();
	while (ite != m_pGraph->m_EdgeVec.end())
	{
		if ((ite->m_Node1.m_dNodePosX > dx1 && ite->m_Node1.m_dNodePosX < dx2 &&
			 ite->m_Node1.m_dNodePosY > dy1 && ite->m_Node1.m_dNodePosY < dy2 ) ||
			(ite->m_Node2.m_dNodePosX > dx1 && ite->m_Node2.m_dNodePosX < dx2 &&
			 ite->m_Node2.m_dNodePosY > dy1 && ite->m_Node2.m_dNodePosX < dy2 )) // 这种太变态了，可以考虑用个匿名函数

		{
			ite = m_pGraph->m_EdgeVec.erase(ite);
			continue;
		}
		ite++;
	}


	// 然后遍历边
	QVector<CNode>::iterator itn = m_pGraph->m_NodeVec.begin();
	while (itn != m_pGraph->m_NodeVec.end())
	{
		if ((itn->m_dNodePosX > dx1 && itn->m_dNodePosX < dx2 && itn->m_dNodePosY > dy1 && itn->m_dNodePosY < dy2)  ) // 这种太变态了，可以考虑用个匿名函数

		{
			itn = m_pGraph->m_NodeVec.erase(itn);
			continue;
		}
		itn++;
	}


	return NORMAL_RETURN;
}

int CMapDisplay::fn_DeleteEdges()
{
	double dx1 = m_dEditAreaX1 < m_dEditAreaX2 ? m_dEditAreaX1 : m_dEditAreaX2;
	double dx2 = m_dEditAreaX1 < m_dEditAreaX2 ? m_dEditAreaX2 : m_dEditAreaX1;
	double dy1 = m_dEditAreaY1 < m_dEditAreaY2 ? m_dEditAreaY1 : m_dEditAreaY2;
	double dy2 = m_dEditAreaY1 < m_dEditAreaY2 ? m_dEditAreaY2 : m_dEditAreaY1;

	QVector<CEdge>::iterator ite = m_pGraph->m_EdgeVec.begin();

	while (ite != m_pGraph->m_EdgeVec.end())
	{
		if (ite->m_Node1.m_dNodePosX > dx1 && ite->m_Node1.m_dNodePosX < dx2 &&
			ite->m_Node1.m_dNodePosY > dy1 && ite->m_Node1.m_dNodePosY < dy2 &&
			ite->m_Node2.m_dNodePosX > dx1 && ite->m_Node2.m_dNodePosX < dx2 &&
			ite->m_Node2.m_dNodePosY > dy1 && ite->m_Node2.m_dNodePosX < dy2) // 这种太变态了，可以考虑用个匿名函数

		{
			ite = m_pGraph->m_EdgeVec.erase(ite);
			continue;
		}
		ite++;
	}

	return NORMAL_RETURN;
}



template<typename T>
inline double CMapDisplay::fn_TransMap2Window(T iPos_Map, double dStartPoint, double dScale)
{
	/***************************************************************
	  *  @brief     函数作用：从地图坐标系转为窗口坐标系
	  *  @param     参数：dStartPoint-窗口坐标系下地图原点的值；dScale-窗口坐标系对地图坐标系的缩放尺寸
	  *  @note      备注
	  *  @Sample usage:     函数的使用方法
	 **************************************************************/

	return  dStartPoint + iPos_Map * dScale;
}

template<typename T>
inline double CMapDisplay::fn_TransA2B(T iPos_A, double dAStartPoint_B, double dScaleA_B)
{
	/***************************************************************
	  *  @brief     函数作用：从地图坐标系转为窗口坐标系
	  *  @param     参数：dStartPoint-窗口坐标系下地图原点的值；dScale-窗口坐标系对地图坐标系的缩放尺寸
	  *  @note      备注
	  *  @Sample usage:     函数的使用方法
	 **************************************************************/

	return  dAStartPoint_B + iPos_A * dScaleA_B;
}

