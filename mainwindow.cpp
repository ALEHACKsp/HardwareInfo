#include "mainwindow.h"

const qint64 GB = 1024 * 1024 *1024;

MainWindow::MainWindow(QWidget *parent)
{
    this->setWindowTitle("硬件信息");
    this->setFixedSize(800,1024);
    QWidget *mainWidget = new QWidget(parent);
    mainWidget->setLayout(CreateMainLayout());
    this->setCentralWidget(mainWidget);
    getStorageInfo();
}

MainWindow::~MainWindow()
{
}

QVBoxLayout *MainWindow::CreateMainLayout()
{
    QVBoxLayout *main = new QVBoxLayout();

    QHBoxLayout *cpuLayout = new QHBoxLayout();
    QLabel *cpuType = Tools::CreateLabel("处理器型号:","cpu");
    QLineEdit *cpuDetail = Tools::CreateLineEdit(getCpuInfo(),"cpuDetail");
    cpuLayout->addWidget(cpuType);
    cpuLayout->addWidget(cpuDetail);

    QHBoxLayout *memoryLayout = new QHBoxLayout();
    QLabel *memoryType = Tools::CreateLabel("内存容量 : ","memory");
    QLineEdit *memoryDetail =Tools::CreateLineEdit(getMemoryInfo(),"memoryDetail");
    memoryLayout->addWidget(memoryType);
    memoryLayout->addWidget(memoryDetail);

    QHBoxLayout *storageLayout = new QHBoxLayout();
    QLabel *storageList = Tools::CreateLabel("磁盘列表 : ","storage");
    QTableView *storageTable = Tools::CreateTableView("storageTable");
    storageLayout->addWidget(storageList);
    storageLayout->addWidget(storageTable);

    main->addLayout(cpuLayout);
    main->addLayout(memoryLayout);
    main->addLayout(storageLayout);
    main->addStretch();
    return main;
}

QString MainWindow::getCpuInfo()
{
    QSettings *CPU = new QSettings("HKEY_LOCAL_MACHINE\\HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",QSettings::NativeFormat);
    QString m_cpu = CPU->value("ProcessorNameString").toString();
    delete CPU;
    return m_cpu;
}

QString MainWindow::getMemoryInfo()
{
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);
    GlobalMemoryStatusEx(&statex);
    double m_totalMem = statex.ullTotalPhys * 1.0/GB;
    double m_freeMem = statex.ullAvailPhys *1.0/GB;
    QString m_memory = QString("剩余可使用 %1 GB / 总共 %2 GB").arg(QString::asprintf("%.2f",m_freeMem)).arg(QString::asprintf("%.2f",m_totalMem));
    return m_memory;
}

void MainWindow::getStorageInfo()
{
    QTableView *table = findChild<QTableView *>("storageTable");
    QStandardItemModel *model = new QStandardItemModel(this);
    QItemSelectionModel *selection = new QItemSelectionModel(model);
    table->setModel(model);
    table->setSelectionModel(selection);

    QList<QStorageInfo> infoList = QStorageInfo::mountedVolumes();
    QString available;
    QString free;
    QString total;
    for(auto i = 0; i < infoList.size(); i++)
    {
        QStorageInfo info = infoList.at(i);
        available = QString::number(info.bytesAvailable()/GB,10)+"GB";
        free = QString::number(info.bytesFree()/GB,10)+"GB";
        total = QString::number(info.bytesTotal()/GB,10)+"GB";
        model->setItem(i,0,new QStandardItem(info.name()));
        model->setItem(i,1,new QStandardItem(available));
        model->setItem(i,2,new QStandardItem(free));
        model->setItem(i,3,new QStandardItem(total));
        model->setItem(i,4,new QStandardItem(QString(info.fileSystemType())));
        table->setRowHeight(i,145);
    }
    table->setColumnWidth(0,120);
    table->setColumnWidth(1,130);
    table->setColumnWidth(2,130);
    table->setColumnWidth(3,130);
    table->setColumnWidth(4,100);

}
