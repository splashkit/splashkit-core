#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pb_process->setValue(0);
    ui->txt_process->setText("");
    completeProc = false;
    cSteps = 1;
    instStarted = false;
    skExist = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readOutput(){

    QString output_val =  QString::fromUtf8(process->readAllStandardOutput()).trimmed();
    qDebug() << output_val;
    ui->txt_process->setText(output_val);
    if(output_val.contains("password for data")){
        bool ok;
            QString text = QInputDialog::getText(this, tr("Password"),
                                                 tr("Password:"), QLineEdit::Password,
                                                 tr(""), &ok);
            if (ok && !text.isEmpty()){
                QString strdata = text + "\n";
                QByteArray data = QByteArray::fromStdString(strdata.toStdString());
                process->write(data);
                process->waitForBytesWritten();
            }
    }


    if(cProcess == "skm" && output_val.contains("bash")){
        shFile = output_val;
    }

    if(cProcess == "skm_handle" && output_val.contains("Looks like you already have splashkit") && output_val.length() < 300){
        skExist = true;
    }
    if(cProcess == "skm_handle" && output_val.contains("SplashKit Successfully installed!")){
        progressbar_update();
        install_dotnet();
    }
    if(cProcess == "install_vscode" && output_val.contains("code") && output_val.contains("is already installed")){
        progressbar_update();
        ui->txt_process->setText("Installation completed successfully.");
        ui->btn_install->setText("Close");
        ui->btn_install->setEnabled(true);
        completeProc = true;
    }
    if(cProcess == "install_vscode" && output_val.contains("Visual Studio Code") && output_val.contains("installed")){
        progressbar_update();
        ui->txt_process->setText("Installation completed successfully.");
        ui->btn_install->setText("Close");
        ui->btn_install->setEnabled(true);
        completeProc = true;
    }


}

void MainWindow::progressbar_update()
{
    long percentval = (100.00/5) * cSteps;
    ui->pb_process->setValue(int(percentval));
    ui->lbl_steps->setText("Installing " + QString::number(cSteps) + "/5");

}

void MainWindow::on_btn_install_clicked()
{
    if(instStarted == true){
          QApplication::quit();
          return;
     }
    instStarted = true;
    ui->lbl_steps->setText("Installing 1/5");
    ui->btn_install->setEnabled(false);
    ui->pb_process->setVisible(true);
    install_curl_git();

    process->waitForFinished();
}

void MainWindow::install_curl_git()
{
    cSteps = 1;
    cProcess = "git_crul";
    ui->txt_process->setText("Starting to install Git and CURL");
    process = new QProcess(this);
    process->setProcessChannelMode(QProcess::MergedChannels);
    connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(readOutput()));
    connect(process, SIGNAL(finished(int, QProcess::ExitStatus )), this, SLOT(process_finished(int, QProcess::ExitStatus )));
    process->start("sudo", QStringList() << "-S" << "apt-get" << "install" << "curl" << "git" << "-y" );
    process->waitForFinished();
}

void MainWindow::install_skm()
{
    cSteps = 2;
    cProcess = "skm";
    ui->txt_process->setText("Starting to install Splashkit SDK");
    process = new QProcess(this);
    process->setProcessChannelMode(QProcess::MergedChannels);
    connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(readOutput()));
    connect(process, SIGNAL(finished(int, QProcess::ExitStatus )), this, SLOT(process_finished(int, QProcess::ExitStatus )));
    process->start("curl", QStringList() << "-s" <<
           "https://raw.githubusercontent.com/splashkit/skm/master/install-scripts/skm-install.sh");
    process->waitForFinished();
    completeProc = true;

}

void MainWindow::handle_bash()
{
    skExist = false;
    cSteps = 2;
    cProcess = "skm_handle";
    ui->txt_process->setText("Starting to install Splashkit SDK");
    process = new QProcess(this);
    process->setProcessChannelMode(QProcess::MergedChannels);
    connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(readOutput()));
    connect(process, SIGNAL(finished(int, QProcess::ExitStatus )), this, SLOT(process_finished(int, QProcess::ExitStatus )));
    process->start("/bin/bash", QStringList() << "-c" << shFile);
    process->waitForFinished();
    completeProc = true;
}

void MainWindow::make_splashkit()
{
    cSteps = 3;
    cProcess = "make_splashkit";
    ui->txt_process->setText("Setting up SplashKit");
    process = new QProcess(this);
    process->setProcessChannelMode(QProcess::MergedChannels);
    connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(readOutput()));
    connect(process, SIGNAL(finished(int, QProcess::ExitStatus )), this, SLOT(process_finished(int, QProcess::ExitStatus )));
    process->start("skm", QStringList() << "linux" << "install" << "-y");
    process->waitForFinished();

}

void MainWindow::install_vscode()
{

    ui->txt_process->setText("Microsoft.DotNet.SDK.6 installed successfully!");
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm", "Do you want to install Visual Studio Code?", QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            cSteps = 5;
            completeProc = true;
            cProcess = "install_vscode";
            ui->txt_process->setText("Installing Visual Studio Code.");
            process = new QProcess(this);
            process->setProcessChannelMode(QProcess::MergedChannels);
            connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(readOutput()));
            connect(process, SIGNAL(finished(int, QProcess::ExitStatus )), this, SLOT(process_finished(int, QProcess::ExitStatus )));
            process->start("sudo", QStringList() << "-S" << "snap" << "install" << "code" << "--classic" );
            process->waitForFinished();
            qDebug() << "visual studio code";
        } else {
            cSteps = 5;
            cProcess = "install_vscode";
            qDebug() << "no";
            ui->txt_process->setText("Installation completed successfully.");
            ui->btn_install->setText("Close");
            ui->btn_install->setEnabled(true);
            completeProc = true;
        }
}

void MainWindow::install_dotnet()
{
    cSteps = 4;
    cProcess = "install_dotnet";
    ui->txt_process->setText("Installing Microsoft.DotNet.SDK.6");
    process = new QProcess(this);
    process->setProcessChannelMode(QProcess::MergedChannels);
    connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(readOutput()));
    connect(process, SIGNAL(finished(int, QProcess::ExitStatus )), this, SLOT(process_finished(int, QProcess::ExitStatus )));
    process->start("sudo", QStringList() << "-S" << "apt-get" << "install" << "dotnet6" << "-y" );
    completeProc = true;
    process->waitForFinished();
}

void MainWindow::remove_splashkit()
{
    cProcess = "skremove";
    ui->txt_process->setText("Removing SplashKit");
    process = new QProcess(this);
    process->setProcessChannelMode(QProcess::MergedChannels);
    connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(readOutput()));
    connect(process, SIGNAL(finished(int, QProcess::ExitStatus )), this, SLOT(process_finished(int, QProcess::ExitStatus )));
    QString cmd = "rm -rf /home/" + qgetenv("USER") + "/.splashkit";

    process->start("sudo", QStringList() << "-S" << "bash"  << "-c" << cmd  );
    completeProc = true;
    process->waitForFinished();
}


void MainWindow::process_finished(int code, QProcess::ExitStatus status)
{

    if(code == 0 && cProcess == "git_crul"){
        progressbar_update();
        install_skm();
    }

    if(code == 0 && cProcess == "install_dotnet" && completeProc == true){
        cProcess = "install_vscode";
        progressbar_update();
        install_vscode();
        completeProc = false;
    }
    if(code == 0 && cProcess == "skm" && completeProc == true){
        ui->txt_process->setText("Setting up SplashKit");
        handle_bash();
    }
    if(code == 0 && cProcess == "skremove" && completeProc == true){
        ui->txt_process->setText("Setting up SplashKit");
        handle_bash();
    }
    if(code == 0 && cProcess == "skm_handle" && completeProc == true){
        if(skExist){
            qDebug() << cProcess;
            QMessageBox::StandardButton reply;
                reply = QMessageBox::question(this, "Confirm", "SplashKit already installed. Do you want remove and intall?", QMessageBox::Yes|QMessageBox::No);
                if (reply == QMessageBox::Yes) {
                    skExist = false;
                    remove_splashkit();
                    return;
                } else {
                    QApplication::quit();
                }
        }else{
            ui->txt_process->setText("Setting up SplashKit");
            make_splashkit();
        }

    }



}


void MainWindow::on_btn_cancel_clicked()
{
    QApplication::quit();
}

