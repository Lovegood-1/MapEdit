
/*
* 总体的窗体布局
*/

#ifndef MAPEDITTOOL_H
#define MAPEDITTOOL_H

#include "Macro.h"

#include <QWidget>
#include <QMenu>
#include <QAction>
#include <QMenuBar>

#include "MapDisplay.h"


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
    QMenuBar m_MenuBar;

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
};

#endif // !MAPEDITTOOL_H