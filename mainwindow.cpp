#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>
#include <QLayout>
#include <QFileDialog>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QHBoxLayout *horizontalLayout = new QHBoxLayout;

    ui->widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    horizontalLayout->addWidget(ui->widget, 7);

    QVBoxLayout *verticalLayout = new QVBoxLayout;

    QHBoxLayout *horizontalLayout_1 = new QHBoxLayout;

    ui->pushButton_4->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    QSpacerItem *horizontalSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed);

    horizontalLayout_1->addSpacerItem(horizontalSpacer);
    horizontalLayout_1->addWidget(ui->pushButton_4, 2);

    ui->pushButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    ui->pushButton_2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    ui->pushButton_3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    ui->pushButton_5->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    ui->pushButton_6->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    ui->lineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    verticalLayout->addLayout(horizontalLayout_1);
    verticalLayout->addWidget(ui->pushButton);
    verticalLayout->addWidget(ui->pushButton_2);
    verticalLayout->addWidget(ui->pushButton_3);
    verticalLayout->addWidget(ui->pushButton_5);
    verticalLayout->addWidget(ui->pushButton_6);
    verticalLayout->addWidget(ui->lineEdit);

    QSpacerItem *verticalSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding);

    verticalLayout->addSpacerItem(verticalSpacer);

    horizontalLayout->addLayout(verticalLayout, 3);

    ui->centralwidget->setLayout(horizontalLayout);

    connect(ui->pushButton, SIGNAL(clicked()), ui->widget, SLOT(startPainting()));
    connect(ui->pushButton_2, SIGNAL(clicked()), ui->widget, SLOT(stopPainting()));
    connect(ui->pushButton_3, SIGNAL(clicked()), ui->widget, SLOT(randCells()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->pushButton_5, SIGNAL(clicked()), ui->widget, SLOT(clearAll()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(openFile()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),QDir::rootPath(), tr("*.txt"));

    if(fileName.size() != 0)
    {
        ui->lineEdit->setText(fileName);

        ui->widget->setFileName(fileName);
    }
}
