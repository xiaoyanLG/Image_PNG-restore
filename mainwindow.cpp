#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked() // 选择源文件路径
{
    ui->lineEdit->setText(QFileDialog::getExistingDirectory(this));
}

void MainWindow::on_pushButton_3_clicked() // 选择保存路径
{
    ui->lineEdit_2->setText(QFileDialog::getExistingDirectory(this));
}

void MainWindow::on_pushButton_clicked() // 修复
{
    QDir dir(ui->lineEdit->text());
    QFileInfoList list = dir.entryInfoList(QStringList() << "*.png");
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        QImage image(fileInfo.filePath());
        if (image.isNull())
        {
            continue;
        }

        if (ui->lineEdit_2->text().isEmpty())
        {
            image.save(fileInfo.filePath());
        }
        else
        {
            image.save(ui->lineEdit_2->text() + QDir::separator() + fileInfo.fileName());
        }

        ui->statusBar->showMessage(fileInfo.filePath());
    }

    QMessageBox::information(this, QStringLiteral("完成"), QStringLiteral("全部修复完成"));
}
