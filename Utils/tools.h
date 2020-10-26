#ifndef TOOLS_H
#define TOOLS_H

#include <QMainWindow>
#include <QDebug>
#include <QSettings>
#include <QLayout>
#include <QLineEdit>
#include <QLabel>
#include <QStorageInfo>
#include <QList>
#include <QTableView>
#include <QHeaderView>
#include <QStandardItem>
#include <QItemSelectionModel>
#include "windows.h"

class Tools
{
public:
    Tools();

    static QLabel *CreateLabel(QString text,QString objectname);
    static QLineEdit *CreateLineEdit(QString text,QString objectname);
    static QTableView *CreateTableView(QString objectname);
};

#endif // TOOLS_H
