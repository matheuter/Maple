

#include "mainwindow.h"
#include "DockingPaneManager.h"
#include "DockingPaneBase.h"
#include <QLabel>
#include <QTextEdit>
#include <QUuid>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    showMaximized();

    m_dockingPaneManager = new DockingPaneManager;

    auto clientWidget = new QTextEdit;

    m_dockingPaneManager->setClientWidget(clientWidget);

    setCentralWidget(m_dockingPaneManager->widget());

    DockingPaneBase *dockingWindow_2 = m_dockingPaneManager->createPane(QUuid::createUuid().toString(), "Tool Window 2", createLabel("Hello World 2"), QSize(200, 200), DockingPaneManager::dockLeft, nullptr);
    DockingPaneBase *dockingWindow_3 = m_dockingPaneManager->createPane(QUuid::createUuid().toString(), "Tool Window 3", createLabel("Hello World 3"), QSize(100, 200), DockingPaneManager::dockRight, nullptr);
    m_dockingPaneManager->hidePane(dockingWindow_3);

}

MainWindow::~MainWindow()
{
    //delete ui;
}

QLabel *MainWindow::createLabel(QString string)
{
    auto label = new QLabel(string);

    label->setAlignment(Qt::AlignCenter);

    return(label);
}
