#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QDir>
#include <QDataStream>
#include <QTextStream>
#include <QMessageBox>

#include <qdebug.h>


typedef struct buf{
    char i [256];
}BUF;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QDir d("/sdcard/lights");

    d.setPath(d.absoluteFilePath("/sdcard/lights"));
    ui->comboBox->addItems(d.entryList(QDir::Files));
    //ui->comboBox->showPopup();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
      QDir d("/sdcard");
      d.mkdir("lights");

      QFile f ("/sdcard/lights/" + ui->comboBox->currentText());
      BUF buf,cmp;

      qDebug("app starting...");

      f.open(QIODevice::ReadWrite);
      f.seek(0);

      QDataStream arr(&f);

      for (int i=0 ; i < 256 ; i++){
          buf.i[i] = i;
          cmp.i[i] = i;
      }

      arr.writeRawData((char*)&buf,sizeof(buf));
      arr.readRawData((char*)&buf,sizeof(buf));

      if ( memcmp(&cmp,&buf,sizeof(buf)) == 0 ){
          QMessageBox::information(0, "test", "<p>The files are equal meaning the test is <i>succes</i></p>");

          qDebug("equal");
      }

      qDebug("app ending...");

      f.close();

}

void MainWindow::on_comboBox_editTextChanged(const QString &arg1)
{
    //qDebug() << arg1;
}
