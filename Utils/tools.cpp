#include "tools.h"

Tools::Tools()
{

}

QLabel *Tools::CreateLabel(QString text,QString objectname)
{
    QLabel *label = new QLabel();
    label->setText(text);
    label->setObjectName(objectname);
    return label;
}

QLineEdit *Tools::CreateLineEdit(QString text, QString objectname)
{
    QLineEdit *edit = new QLineEdit();
    edit->setText(text);
    edit->setObjectName(objectname);
    edit->setReadOnly(true);
    edit->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    return edit;
}

QTableView *Tools::CreateTableView(QString objectname)
{
    QTableView *table = new QTableView();
    table->setObjectName(objectname);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->verticalHeader()->setVisible(false);
    table->horizontalHeader()->setVisible(false);
    table->setShowGrid(false);
    return table;
}
