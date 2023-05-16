#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


class DockingPaneManager;
class QLabel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QLabel *createLabel(QString string);
    DockingPaneManager *m_dockingPaneManager;
};

#endif // MAINWINDOW_H
