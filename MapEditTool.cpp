#include "MapEditTool.h"

CMapEditTool::CMapEditTool(QWidget *parent)
    : QWidget(parent), m_ModeSwitchShortcut(this)
{
    setAttribute(Qt::WidgetAttribute::WA_StyledBackground);
    setWindowTitle(tr("Map Edit Tool"));
    setWindowIcon(QIcon(QString(":/icon/Resource/icon/Tool.png")));
    setMinimumSize(QSize(600, 400));



    // creat 
    m_pLoadFileAction    = new QAction(tr("Load File"), this);
    m_pSaveFileAction    = new QAction(tr("Save Data"), this);
    m_pImportMapAction   = new QAction(tr("Import Map"), this);
    m_pViewModeAction    = new QAction(tr("View Mode"), this);
    m_pEditModeAction    = new QAction(tr("Edit Mode"), this);
    m_pShowNodeIdAction = new QAction(tr("Show Node Id"), this);
    m_pHideNodeIdAction = new QAction(tr("Hide Node Id"), this);
    m_pSettingAction     = new QAction(tr("Setting"), this);

    m_pViewModeAction->setCheckable(true);
    m_pViewModeAction->setChecked(true);
    m_pEditModeAction->setCheckable(true);
    m_pEditModeAction->setChecked(false);
    m_pShowNodeIdAction->setEnabled(false);



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

    m_pSelectionMenu->addAction(m_pHideNodeIdAction);
    m_pSelectionMenu->addAction(m_pShowNodeIdAction);
    m_pSelectionMenu->addSeparator();
    m_pSelectionMenu->addAction(m_pSettingAction);

    m_MenuBar.setParent(this);
    m_MenuBar.addMenu(m_pFileMenu);
    m_MenuBar.addMenu(m_pOperateMenu);
    m_MenuBar.addMenu(m_pSelectionMenu);

    m_MapDisplay.setParent(this);

    m_ModeSwitchShortcut.setKey(QKeySequence(Qt::Key::Key_Tab));


    // 二、窗口布局
    m_NodeInfoLabel.setParent(this);
    m_NodeInfoLabel.setText(tr("Node Info"));

    m_NodePosXLabel.setParent(this);
    m_NodePosXLabel.setText(tr("Pos X :"));

    m_NodePosXEdit.setParent(this);
    m_NodePosXEdit.setReadOnly(true);

    m_NodePosYLabel.setParent(this);
    m_NodePosYLabel.setText(tr("Pos Y :"));

    m_NodePosYEdit.setParent(this);
    m_NodePosYEdit.setReadOnly(true);

    m_NodeTypeLabel.setParent(this);
    m_NodeTypeLabel.setText(tr("Type :"));

    m_NodeTypeComboBox.setParent(this);
    m_NodeTypeComboBox.addItem(tr("Road"));
    m_NodeTypeComboBox.addItem(tr("Building"));
    m_NodeTypeComboBox.setCurrentIndex(0);

    m_NodeNameLabel.setParent(this);
    m_NodeNameLabel.setText(tr("Name :"));

 
    m_NodeNameEdit.setParent(this);
    m_NodeNameEdit.setPlaceholderText(tr("Name ..."));

    m_SaveNodeBtn.setParent(this);
    m_SaveNodeBtn.setText(tr("Save Node"));
    m_SaveNodeBtn.setShortcut(QKeySequence(QString("Ctrl+S")));
    m_SaveNodeBtn.setFocusPolicy(Qt::FocusPolicy::WheelFocus);

    connect(m_pLoadFileAction, &QAction::triggered, this, &CMapEditTool::fn_Recv_LoadFileAction_Triggered, Qt::ConnectionType::DirectConnection);
    connect(m_pSaveFileAction, &QAction::triggered, this, &CMapEditTool::fn_Recv_SaveDataAction_Triggered, Qt::ConnectionType::DirectConnection);
    connect(m_pImportMapAction, &QAction::triggered, this, &CMapEditTool::fn_Recv_ImportMapAction_Triggered, Qt::ConnectionType::DirectConnection);
    connect(m_pViewModeAction, &QAction::triggered, this, &CMapEditTool::fn_Recv_ViewModeAction_Triggered, Qt::ConnectionType::DirectConnection);
    connect(m_pEditModeAction, &QAction::triggered, this, &CMapEditTool::fn_Recv_EditModeAction_Triggered, Qt::ConnectionType::DirectConnection);
    connect(m_pSettingAction, &QAction::triggered, this, &CMapEditTool::fn_Recv_SettingAction_Triggered, Qt::ConnectionType::DirectConnection);
    connect(&m_SaveNodeBtn, &QPushButton::clicked, this, &CMapEditTool::fn_Recv_SaveNodeBtn_Clicked, Qt::ConnectionType::DirectConnection);
    connect(&m_ModeSwitchShortcut, &QShortcut::activated, this, &CMapEditTool::fn_Recv_ModeSwitchShortcut_Activated, Qt::ConnectionType::DirectConnection);
    connect(&m_MapDisplay, &CMapDisplay::Signal_NodeCreated, this, &CMapEditTool::fn_Recv_MapDisplay_NodeCreated, Qt::ConnectionType::DirectConnection);
    connect(m_pShowNodeIdAction, &QAction::triggered, this, &CMapEditTool::fn_Recv_ShowNodeIdAction_Triggered, Qt::ConnectionType::DirectConnection);
    connect(m_pHideNodeIdAction, &QAction::triggered, this, &CMapEditTool::fn_Recv_HideNodeIdAction_Triggered, Qt::ConnectionType::DirectConnection);

    fn_LoadStyleSheet();
}

CMapEditTool::~CMapEditTool()
{}

/*
设置大小变动时自己和自己内部部件的尺寸
*/
void CMapEditTool::resizeEvent(QResizeEvent * event)
{
    
    int heightOfmenu = 28;
    int iw = width(), ih = height();
    m_MenuBar.setGeometry       (0,                   0, iw, HIGH_MENU);
    m_MapDisplay.setGeometry    (0,                        HIGH_MENU, iw - WIDTH_MENU, ih- HIGH_MENU);
    m_NodeInfoLabel.setGeometry (iw - WIDTH_MENU + 5,      HIGH_MENU, 190, heightOfmenu+3);
    m_NodePosXLabel.setGeometry (iw - WIDTH_MENU + 5,      HIGH_MENU + 30,   85, heightOfmenu);
    m_NodePosXEdit.setGeometry  (iw - WIDTH_MENU + 5 + 90, HIGH_MENU + 30,   100,               heightOfmenu);
    m_NodePosYLabel.setGeometry (iw - WIDTH_MENU + 5,      HIGH_MENU + 30 + 30, 85             , heightOfmenu);
    m_NodePosYEdit.setGeometry  (iw - 105,                 85,                  100            , heightOfmenu);
    m_NodeTypeLabel.setGeometry (iw - WIDTH_MENU + 5,      115,                 85             , heightOfmenu);
    m_NodeTypeComboBox.setGeometry(iw - 105,               115,                 100            , heightOfmenu);
    m_NodeNameLabel.setGeometry (iw - WIDTH_MENU + 5,      145,                 85             , heightOfmenu);
    m_NodeNameEdit.setGeometry  (iw - 105,                 145,                 100            , heightOfmenu);
    m_SaveNodeBtn.setGeometry   (iw - WIDTH_MENU + 5,      175,                 190            , heightOfmenu);

    QWidget::resizeEvent(event);  
}

int CMapEditTool::fn_Recv_LoadFileAction_Triggered()
{
    QString qstrFilePath = QFileDialog::getOpenFileName(this, tr("Open .gh File"), QString("."), tr("Graph File(*.gh)"));
    if (qstrFilePath.isEmpty())
    {
        return NO_FILE_SELECTED;
    } 

    CSystemData::GetSystemData()->GetGraph()->LoadFile(qstrFilePath);
    return NORMAL_RETURN;
}

int CMapEditTool::fn_Recv_SaveDataAction_Triggered()
{
    QString qstrFilePath = QFileDialog::getSaveFileName(this, tr("Save .gh File"), QString("."), tr("Graph File(*.gh)"));
    if (qstrFilePath.isEmpty())
    {
        return NO_FILE_SELECTED;
    }

    CSystemData::GetSystemData()->GetGraph()->SaveData(qstrFilePath);
    return NORMAL_RETURN;
}

int CMapEditTool::fn_Recv_ImportMapAction_Triggered()
{
    QString qstrFilePath = QFileDialog::getOpenFileName(this, tr("Import Map File"),
        QString("."), tr(""));
    if (qstrFilePath.isEmpty())
    {
        return NO_FILE_SELECTED;
    }

    bool bRet = CSystemData::GetSystemData()->GetGraph()->m_MapImage.load(qstrFilePath);
    if ( bRet)
    {
        m_MapDisplay.update();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText(tr("Load File Fail"));
        msgBox.exec();
    }




    return NORMAL_RETURN;
}

int CMapEditTool::fn_Recv_ViewModeAction_Triggered()
{
    m_pViewModeAction->setChecked(true);
    m_pEditModeAction->setChecked(false);
    m_MapDisplay.SetEditMode(false);
    m_MapDisplay.update();

    return NORMAL_RETURN;
}

int CMapEditTool::fn_Recv_EditModeAction_Triggered()
{
    m_pViewModeAction->setChecked(false);
    m_pEditModeAction->setChecked(true);
    m_MapDisplay.SetEditMode(true);
    m_MapDisplay.update();
    return NORMAL_RETURN;
}

int CMapEditTool::fn_Recv_ShowNodeIdAction_Triggered()
{
    CSystemData::GetSystemData()->SetShowNodeId(true);
    m_pShowNodeIdAction->setEnabled(false);
    m_pHideNodeIdAction->setEnabled(true);
    m_MapDisplay.update();
    return NORMAL_RETURN;
}

int CMapEditTool::fn_Recv_HideNodeIdAction_Triggered()
{
    CSystemData::GetSystemData()->SetShowNodeId(false);
    m_pShowNodeIdAction->setEnabled(true);
    m_pHideNodeIdAction->setEnabled(false);
    m_MapDisplay.update();
    return NORMAL_RETURN;
}

int CMapEditTool::fn_Recv_SettingAction_Triggered()
{
    return NORMAL_RETURN;
}

int CMapEditTool::fn_Recv_SaveNodeBtn_Clicked()
{
    //1 检查输入是否合法
    QString qstrNodePosX = m_NodePosXEdit.text();
    QString qstrNodePosY = m_NodePosYEdit.text();
    QString qstrNodeName = m_NodeNameEdit.text();
    int iNodeType = m_NodeTypeComboBox.currentIndex();


    if (qstrNodePosX.isEmpty() || qstrNodePosY.isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setText(tr("Node Position Data Error"));
        msgBox.exec();
        return ERROR_POSITION;
    }

    if (iNodeType == 1 && qstrNodeName.isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setText(tr("Node Name Not Be Empty"));
        msgBox.exec();
        return EMPTY_NODE_NAME;
    }

    CGraph* pGraph = CSystemData::GetSystemData()->GetGraph();
    CNode node;
    node.setNodeId(pGraph->m_iMaxNodeId++);
    node.setNodePosX(qstrNodePosX.toDouble());
    node.setNodePosY(qstrNodePosY.toDouble());
    node.setNodeType(iNodeType == 0 ? NodeType::Node_Road : NodeType::Node_Building);
    node.setNodeName(qstrNodeName);

    pGraph->m_NodeVec.push_back(node); //应该是调用了拷贝构造函数？

    m_NodePosXEdit.clear();
    m_NodePosYEdit.clear();
    m_NodeNameEdit.clear();
    m_MapDisplay.update();
    return NORMAL_RETURN;
}

int CMapEditTool::fn_Recv_ModeSwitchShortcut_Activated()
{
    bool bEditMode = m_MapDisplay.GetEditMode();

    if (bEditMode)
    {
        m_pViewModeAction->setChecked(true);
        m_pEditModeAction -> setChecked(false);
        m_MapDisplay.SetEditMode(false);

    }
    else
    {
        m_pViewModeAction->setChecked(false);
        m_pEditModeAction->setChecked(true);
        m_MapDisplay.SetEditMode(true);
    }

    m_MapDisplay.update();
    return NORMAL_RETURN;
}

int CMapEditTool::fn_Recv_MapDisplay_NodeCreated(const double& dPosX, const double& dPosY)
{
    m_NodePosXEdit.setText(QString::number(dPosX));
    m_NodePosYEdit.setText(QString::number(dPosY));
    m_NodeNameEdit.setFocus();
    return NORMAL_RETURN;
}

int CMapEditTool::fn_LoadStyleSheet()
{
    QFile file(QString(":/qss/Resource/qss/MapEditTool.qss"));
    if (file.open(QIODevice::OpenModeFlag::ReadOnly))
    {
        setStyleSheet(QString(file.readAll()));
        file.close();
    }


    return 0;
}
