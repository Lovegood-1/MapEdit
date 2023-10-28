
/**
 * @brief     唯一入口文件
 * @details   主窗口（包括窗口上的菜单、按钮、MapDisplay主控件等）
 * @mainpage  main.cpp -> this file -> MapDisplay.cpp
 * @date 2023-10-24
 */

#ifndef MAPEDITTOOL_H
#define MAPEDITTOOL_H

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

#include "Macro.h"
#include "Systemdata.h"
#include "MapDisplay.h"
#include "SimpleButton.h"

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
    QAction* m_pShowNodeIdAction;
    QAction* m_pHideNodeIdAction;


    CMapDisplay m_MapDisplay;


    QShortcut m_ModeSwitchShortcut;

    QLabel m_NodeInfoLabel;
    QLabel m_NodePosXLabel;     QLineEdit m_NodePosXEdit;
    QLabel m_NodePosYLabel;     QLineEdit m_NodePosYEdit;

    QLabel m_NodeTypeLabel;     QComboBox m_NodeTypeComboBox;
    QLabel m_NodeNameLabel;     QLineEdit m_NodeNameEdit;
    QPushButton m_SaveNodeBtn;
    CSimpleButton m_TestBtn;

protected slots:
    int fn_Recv_LoadFileAction_Triggered();
    int fn_Recv_SaveDataAction_Triggered();
    int fn_Recv_ImportMapAction_Triggered();
    int fn_Recv_ViewModeAction_Triggered();
    int fn_Recv_EditModeAction_Triggered();
    int fn_Recv_ShowNodeIdAction_Triggered();
    int fn_Recv_HideNodeIdAction_Triggered();
    int fn_Recv_SettingAction_Triggered();
    int fn_Recv_SaveNodeBtn_Clicked();
    int fn_Recv_ModeSwitchShortcut_Activated();

    int fn_Recv_MapDisplay_NodeCreated(const double& dPosX, const double& dPosY);

private:
    int fn_LoadStyleSheet();


};

#endif // !MAPEDITTOOL_H