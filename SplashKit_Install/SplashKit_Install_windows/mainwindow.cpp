#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    QString drive_letter = env.value("SystemDrive");

    ui->txt_path->setText(drive_letter + "\\");
    ui->pb_process->setVisible(false);
    ui->pb_process->setValue(0);
    ui->txt_process->setText("");
    QString intall_path = ui->txt_path->text();
    completeProc = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::downloadFileFromURL(const QString &url, const QString &filePath)
{
    if (!m_isReady)
            return;
        m_isReady = false;

        const QString fileName = filePath + url.right(url.size() - url.lastIndexOf("/"));
        m_file = new QFile();
        m_file->setFileName(fileName);
        m_file->open(QIODevice::WriteOnly);
        if (!m_file->isOpen()) {
            m_isReady = true;
            return; // TODO: permission check?
        }

        QNetworkAccessManager *manager = new QNetworkAccessManager;

        QNetworkRequest request;
        request.setUrl(QUrl(url));
        QNetworkReply *reply = manager->get(request);
        connect(reply , SIGNAL(downloadProgress(qint64,qint64)) , this , SLOT(progressbar(qint64,qint64)));
        connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(onDownloadFileComplete(QNetworkReply *)));

        manager->get(request);
        qDebug() << "Downloading..";
}

void MainWindow::onDownloadFileComplete(QNetworkReply *reply)
{
    if (!m_file->isWritable()) {
            m_isReady = true;
            return; // TODO: error check
        }

        m_file->write(reply->readAll());
        m_file->close(); // TODO: delete the file from the system later on
        m_isReady = true;


}
void MainWindow::readOutput(){

    QString output_val =  QString::fromUtf8(process->readAllStandardOutput()).trimmed();
    qDebug() << output_val;


    if(cProcess == "msys"){
        if(output_val.contains("%")){
            QStringList output_parts = output_val.split("%");
            int process_prog = output_parts[0].toInt();
            ui->pb_process->setVisible(true);
            ui->pb_process->setValue(process_prog);
            ui->txt_process->setText(output_parts[1]);

        }
        if(output_val.contains("Everything is Ok")){
            ui->pb_process->setVisible(false);
        }


    }



    if(cProcess == "dotnet"){
        output_val.replace("\b","");

        if(output_val.contains("Starting package install")){
            cStatus = "Starting package install";
        }
        ui->txt_process->setText(cStatus);
        if(output_val.contains("Successfully installed")){
            install_vscode();


        }
    }else{
        ui->txt_process->setText(output_val);
    }

    if(output_val.contains("Would you like to replace the existing file")){
        process->write("Y \n");
        process->waitForBytesWritten();
    }

    if(output_val.contains("Import PGP key 5F944B027F7FE2091985AA2EFA11531AA0AA7F57? [Y/n]")){
        process->write("Y \n");
        process->waitForBytesWritten();
    }
    if(output_val.contains("Do you agree to all the source agreements terms?")){
        process->write("Y \n");
        process->waitForBytesWritten();
    }

    if(output_val.contains("Proceed with installation? [Y/n]")){
        process->write("Y \n");
        process->waitForBytesWritten();
    }
    if(output_val.contains("You MUST restart shell to apply necessary actions")){
        install_git();
    }
    if(cProcess == "gcc" && output_val.contains("Optional dependencies for mingw-w64-x86_64-gdb")){
       install_dotnet();
    }

    if(output_val.contains("Optional dependencies for git")){
        install_skm();
    }
    if(output_val.contains("SplashKit Successfully installed")){
        install_gcc();
    }
    if(cProcess == "vscode"){
        ui->txt_process->setText(cStatus);
        if(output_val.contains("installed")){
            cStatus = "Installation completed successfully.";
            ui->btn_install->setText("Close");
            ui->btn_install->setEnabled(true);
            completeProc = true;
        }
    }


}

void MainWindow::progressbar( qint64 recieved,  qint64 total)
{

    long percentval = (100.00/total) * recieved;
    ui->pb_process->setValue(int(percentval));
    if(int(percentval) == 100){
        ui->pb_process->setVisible(false);
        ui->txt_process->setText("Downloading completed");
        start_install_msys();
    }
}

void MainWindow::on_btn_install_clicked()
{
    if(completeProc == true){
        QApplication::quit();
    }
    QString intall_path = ui->txt_path->text() + "\\msys64";
    QDir path(intall_path);
    if (path.exists()) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Confirm", "Msys2 is already installed. Do u want remove current installation?", QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            ui->txt_process->setText("Removing current installation. Please wait..");
            QCoreApplication::processEvents();
            path.removeRecursively();
        } else {
            return;
        }
    }
    ui->btn_install->setEnabled(false);
    ui->txt_path->setEnabled(false);
    ui->btn_sel_path->setEnabled(false);
    start_install_msys();

}

void MainWindow::start_install_msys()
{
    cProcess = "msys";
    QString intall_path = ui->txt_path->text();
    QString temp_path = QDir::tempPath();
    qDebug() << intall_path;
    cStatus = "Installing MSYS2";
    process = new QProcess(this);
    connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(readOutput()));
    connect(process, SIGNAL(finished(int, QProcess::ExitStatus )), this, SLOT(process_finished(int, QProcess::ExitStatus )));
    process->start("msys2-base-x86_64-latest.sfx.exe", QStringList() << "-y"  << "-o" + intall_path);


}

void MainWindow::start_first_run()
{

    cProcess = "first_run";
    QString intall_path = ui->txt_path->text() + "msys64\\usr\\bin";
    qDebug() << intall_path;
    ui->txt_process->setText("Setting up MSYS2. Please wait..");
    process = new QProcess(this);
    connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(readOutput()));
    connect(process, SIGNAL(finished(int, QProcess::ExitStatus )), this, SLOT(process_finished(int, QProcess::ExitStatus )));
    process->setWorkingDirectory(intall_path);
    process->start("cmd", QStringList() << "/c" << "bash" << "-lc" << "' '" );

}

void MainWindow::install_gcc()
{
    cProcess = "gcc";
    QString intall_path = ui->txt_path->text() + "msys64\\usr\\bin";
    qDebug() << intall_path;
    ui->txt_process->setText("Installing gcc");
    process = new QProcess(this);
    process->setWorkingDirectory(intall_path);
    connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(readOutput()));
    connect(process, SIGNAL(finished(int, QProcess::ExitStatus )), this, SLOT(process_finished(int, QProcess::ExitStatus )));
    process->setWorkingDirectory(intall_path);
    process->start( intall_path + "\\bash.exe", QStringList() <<  "-lc" << "yes | pacman --disable-download-timeout -S mingw-w64-{x86_64,i686}-gcc mingw-w64-{i686,x86_64}-gdb" );
}

void MainWindow::install_dotnet()
{
    cProcess = "dotnet";
    ui->txt_process->setText("Downloading Microsoft.DotNet.SDK.6");
    cStatus = "Installing Microsoft.DotNet.SDK.6";
    process = new QProcess(this);
    connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(readOutput()));
    connect(process, SIGNAL(finished(int, QProcess::ExitStatus )), this, SLOT(process_finished(int, QProcess::ExitStatus )));
    process->start("powershell", QStringList() << "/c" << "&" << "$env:LOCALAPPDATA\\Microsoft\\WindowsApps\\winget" << "install" << "Microsoft.DotNet.SDK.6"  );

}

void MainWindow::install_git()
{

    QString intall_path = ui->txt_path->text() + "msys64\\usr\\bin";
    qDebug() << intall_path;
    ui->txt_process->setText("Installing git");
    process = new QProcess(this);
    connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(readOutput()));
    connect(process, SIGNAL(finished(int, QProcess::ExitStatus )), this, SLOT(process_finished(int, QProcess::ExitStatus )));
    process->setWorkingDirectory(intall_path);
    process->start(intall_path + "\\bash.exe", QStringList() << "-lc" << "pacman -S git --noconfirm --disable-download-timeout" );

}

void MainWindow::install_skm()
{
    cProcess = "skm";
    QString intall_path = ui->txt_path->text() + "msys64\\usr\\bin";
    qDebug() << intall_path;
    ui->txt_process->setText("Starting to install SplashKit SDK");
    process = new QProcess(this);
    connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(readOutput()));
    connect(process, SIGNAL(finished(int, QProcess::ExitStatus )), this, SLOT(process_finished(int, QProcess::ExitStatus )));
    process->setWorkingDirectory(intall_path);
    process->start(intall_path + "\\bash.exe", QStringList() << "-lc" << "bash <(curl -s https://raw.githubusercontent.com/splashkit/skm/master/install-scripts/skm-install.sh) . " );
}

void MainWindow::install_vscode()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm", "Do you want to install Visual Studio Code?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        cProcess = "vscode";
        QString intall_path = ui->txt_path->text() + "msys64";
        qDebug() << intall_path;
        ui->txt_process->setText("Installing Microsoft.VisualStudioCode");
        cStatus = "Installing Microsoft.VisualStudioCode";
        process = new QProcess(this);
        connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(readOutput()));
        connect(process, SIGNAL(finished(int, QProcess::ExitStatus )), this, SLOT(process_finished(int, QProcess::ExitStatus )));
        process->start("powershell", QStringList() << "/c" << "&" << "$env:LOCALAPPDATA\\Microsoft\\WindowsApps\\winget" << "install" << "Microsoft.VisualStudioCode"  );
    } else {
        qDebug() << "no";
        ui->txt_process->setText("Installation completed successfully.");
        ui->btn_install->setText("Close");
        ui->btn_install->setEnabled(true);
        completeProc = true;
    }

}

void MainWindow::process_finished(int code, QProcess::ExitStatus status)
{
    if(cProcess == "msys" && code == 0){
        ui->txt_process->setText("MSYS2 Installation Completed");
        qDebug() << "starting first run";
        process->terminate();
        start_first_run();
    }

}


void MainWindow::on_btn_sel_path_clicked()
{
    QString intall_path = ui->txt_path->text();
    QDir directory = QFileDialog::getExistingDirectory(this,"Open Directory",intall_path);
    directory.setPath(intall_path);
    ui->txt_path->setText(directory.path());
}


void MainWindow::on_btn_cancel_clicked()
{
    QApplication::quit();
}

