
/*
* 总体的窗体布局
*/

#ifndef MAPEDITTOOL_H
#define MAPEDITTOOL_H

#include "Macro.h"
#include "Systemdata.h"
#include "MapDisplay.h"

#include <QMenu>
#include <QLabel>
#include <QAction>
#include <QWidget>
#include <QMenuBar>


#include <QShortcut>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>

#include <QMessageBox>
#include <QFileDialog>




class CMapEditTool : public QWidget
{
    Q_OBJECT

public:
    CMapEditTool(QWidget *parent = nullptr);
    ~CMapEditTool();

    void resizeEvent(QResizeEvent* event) override;


private:
    /*
    窗体的成员其实就是一些控件
    ？systemdata是放在这里吗？
    */
    QMenuBar m_MenuBar; //QMenuBar 代表的是窗口最上方的一条菜单栏。

    QMenu* m_pFileMenu;
    QAction* m_pLoadFileAction;
    QAction* m_pSaveFileAction;
    QAction* m_pImportMapAction;


    QMenu* m_pOperateMenu;
    QAction* m_pViewModeAction;
    QAction* m_pEditModeAction;

    QMenu* m_pSelectionMenu;
    QAction* m_pSettingAction;

    CMapDisplay m_MapDisplay;


    QShortcut m_ModeSwitchShortcut;

    QLabel m_NodeInfoLabel;
    QLabel m_NodePosXLabel;     QLineEdit m_NodePosXEdit;
    QLabel m_NodePosYLabel;     QLineEdit m_NodePosYEdit;

    QLabel m_NodeTypeLabel;     QComboBox m_NodeTypeComboBox;
    QLabel m_NodeNameLabel;     QLineEdit m_NodeNameEdit;
    QPushButton m_SaveNodeBtn;

protected slots:
    int fn_Recv_LoadFileAction_Triggered();
    int fn_Recv_SaveDataAction_Triggered();
    int fn_Recv_ImportMapAction_Triggered();
    int fn_Recv_ViewModeAction_Triggered();
    int fn_Recv_EditModeAction_Triggered();
    int fn_Recv_SettingAction_Triggered();
    int fn_Recv_SaveNodeBtn_Clicked();
    int fn_Recv_ModeSwitchShortcut_Activated();

    int fn_Recv_MapDisplay_NodeCreated(const double& dPosX, const double& dPosY);

};

#endif // !MAPEDITTOOL_H