#include "MapEditTool.h"

CMapEditTool::CMapEditTool(QWidget *parent)
    : QWidget(parent)
{
    // creat 
    m_pLoadFileAction    = new QAction(tr("Load File"), this);
    m_pSaveFileAction    = new QAction(tr("Save Data"), this);
    m_pImportMapAction   = new QAction(tr("Import Map"), this);
    m_pViewModeAction    = new QAction(tr("View Mode"), this);
    m_pEditModeAction    = new QAction(tr("Edit Mode"), this);
    m_pSettingAction     = new QAction(tr("Setting"), this);

    m_pFileMenu = new QMenu(tr("File"), this);
    m_pOperateMenu = new QMenu(tr("Operate Mode"), this);
    m_pSelectionMenu = new QMenu(tr("Selection"), this);

    // set relationship
    m_pFileMenu->addAction(m_pLoadFileAction);
    m_pFileMenu->addAction(m_pSaveFileAction);
    m_pFileMenu->addSeparator();
    m_pFileMenu->addAction(m_pImportMapAction);

    m_pOperateMenu->addAction(m_pViewModeAction);
    m_pOperateMenu->addAction(m_pEditModeAction);
    m_pSelectionMenu->addAction(m_pSettingAction);

    m_MenuBar.setParent(this);
    m_MenuBar.addMenu(m_pFileMenu);
    m_MenuBar.addMenu(m_pOperateMenu);
    m_MenuBar.addMenu(m_pSelectionMenu);

    m_MapDisplay.setParent(this);

}

CMapEditTool::~CMapEditTool()
{}

/*
设置大小变动时自己和自己内部部件的尺寸
*/
void CMapEditTool::resizeEvent(QResizeEvent * event)
{
    
    int iw = width(), ih = height();
    m_MenuBar.setGeometry   (0,      0, iw, HIGH_MENU);
    m_MapDisplay.setGeometry(0, HIGH_MENU, iw, ih - HIGH_MENU);

    QWidget::resizeEvent(event);  
}
