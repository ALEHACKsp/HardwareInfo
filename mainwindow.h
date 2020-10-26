#if defined(_MSC_VER) && (_MSC_VER >= 1600)
#pragma execution_character_set("utf-8")
#endif


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Utils/tools.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QVBoxLayout *CreateMainLayout();
    QString getCpuInfo();
    QString getMemoryInfo();
    void getStorageInfo();
};
#endif // MAINWINDOW_H
