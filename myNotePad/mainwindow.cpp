#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setWindowTitle("My Application");

    ui->setupUi(this);
    //谁发出信号->发出什么信号->谁来处理(MainWindow窗口)->怎么处理
    connect(ui -> newAction, &QAction::triggered, this, &MainWindow::newActionSlot);
    connect(ui -> openAction, &QAction::triggered, this, &MainWindow::openActionSlot);
    connect(ui -> saveAction, &QAction::triggered, this, &MainWindow::saveActionSlot);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newActionSlot() {
    ui -> textEdit -> clear();
    this -> setWindowTitle("新建文本文档.txt");
}

void MainWindow::openActionSlot() {
    //谁来处理->"打开"->获取当前路径(怎么处理)->"获取的文件后缀"(不写则为所有文件)
    QString fileName = QFileDialog::getOpenFileName(this, "打开", QCoreApplication::applicationFilePath(), "");
    if (fileName.isEmpty()) {
        QMessageBox::warning(this, "警告", "请选择一个文件");
    }else {
        //qDebug() << fileName;
        QFile file(fileName);
        //创建文件对象
        file.open(QIODevice::ReadOnly);
        QByteArray ba = file.readAll();
        ui -> textEdit ->setText(QString(ba));
        file.close();

    }
}

void MainWindow::saveActionSlot() {
    QString fileName = QFileDialog::getSaveFileName(this, "打开", QCoreApplication::applicationFilePath(), "");
    if (fileName.isEmpty()) {
        //QMessageBox::warning(this, "警告", "请选择一个文件");
    }else {
        //qDebug() << fileName;
        QFile file(fileName);
        //创建文件对象
        file.open(QIODevice::WriteOnly);
        //QString -> QByteArray
        QString str = ui -> textEdit -> toPlainText();
        QByteArray by1 = str.toLatin1();
        file.write(by1);
        file.close();

    }
}

void MainWindow::keyPressEvent(QKeyEvent *k) {
    if (k -> modifiers() == Qt::ControlModifier && k -> key() == Qt::Key_S) {
        saveActionSlot();
    }

}

void MainWindow::mousePressEvent(QMouseEvent *m) {
    QPoint pt = m -> pos();
    //获取光标位置
    qDebug() << pt;
    if (m -> button() == Qt::LeftButton) {
        qDebug() << "左键被按下";
    }else if (m -> button() == Qt::RightButton){
        qDebug() << "右键被按下";
    }

}
