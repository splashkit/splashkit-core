#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    qDebug() << intall_path;
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
    ui->txt_process->setText(output_val);
    if(output_val.contains("Would you like to replace the existing file")){
        process->write("Y \n");
        process->waitForBytesWritten();
    }
    if(output_val.contains("Import PGP key 5F944B027F7FE2091985AA2EFA11531AA0AA7F57? [Y/n]")){
        process->write("Y \n");
        process->waitForBytesWritten();
    }
    if(output_val.contains("Proceed with installation? [Y/n]")){
        process->write("Y \n");
        process->waitForBytesWritten();
    }








}

void MainWindow::progressbar( qint64 recieved,  qint64 total)
{

    long percentval = (100.00/total) * recieved;
    ui->pb_process->setValue(int(percentval));
    if(int(percentval) == 100){
        ui->txt_process->setText("Downloading completed");
        start_install_msys();
    }
}

void MainWindow::on_btn_install_clicked()
{
    ui->btn_install->setEnabled(false);
    QString temp_path = QDir::tempPath();
    ui->btn_sel_path->setEnabled(false);
    ui->txt_path->setEnabled(false);
    ui->pb_process->setVisible(true);
    ui->txt_process->setText("Downloading msys2-base-x86_64-latest.sfx.exe ");
    downloadFileFromURL("https://github.com/msys2/msys2-installer/releases/download/nightly-x86_64/msys2-base-x86_64-latest.sfx.exe",temp_path);

}

void MainWindow::start_install_msys()
{
    cProcess = "msys";
    QString temp_path = QDir::tempPath();
    QString intall_path = ui->txt_path->text();
    ui->txt_process->setText("Preparing to install Msys2..");
    process = new QProcess(this);
    process->setWorkingDirectory(temp_path);
    process->setArguments(QStringList() << "-y");
    process->setArguments(QStringList() << "-o" + intall_path);
    process->setProgram("\\msys2-base-x86_64-latest.sfx.exe");
    process->start();
    connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(readOutput()));
    connect(process, SIGNAL(finished(int, QProcess::ExitStatus )), this, SLOT(process_finished(int, QProcess::ExitStatus )));
}

void MainWindow::start_first_run()
{

    cProcess = "first_run";
    QString intall_path = ui->txt_path->text() + "msys64\\usr\\bin";
    qDebug() << intall_path;
    ui->txt_process->setText("First run..");
    process = new QProcess(this);
    connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(readOutput()));
    connect(process, SIGNAL(finished(int, QProcess::ExitStatus )), this, SLOT(process_finished(int, QProcess::ExitStatus )));
    process->setWorkingDirectory(intall_path);
    process->execute("powershell", QStringList() << "/c" << "bash" << "-lc" << "' '" );
    process->waitForFinished();
    qDebug() << "now here";

}

void MainWindow::install_git()
{
    cProcess = "git";
    QString intall_path = ui->txt_path->text() + "msys64\\usr\\bin";
    qDebug() << intall_path;
    ui->txt_process->setText("Installing git");
    process = new QProcess(this);
    process->setWorkingDirectory(intall_path);
    process->start("cmd", QStringList() << "/c" << "pacman" << "-S" << "git" << "--noconfirm" << "--disable-download-timeout");
    qDebug() << process->state();

    connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(readOutput()));
    connect(process, SIGNAL(finished(int , QProcess::ExitStatus )), this, SLOT(process_finished(int , QProcess::ExitStatus )));
}

void MainWindow::install_skm()
{
    cProcess = "skm";
    QString intall_path = ui->txt_path->text() + "msys64";
    ui->txt_process->setText("Preparing to install SplashKit SDK..");
    process = new QProcess(this);
    connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(readOutput()));
    connect(process, SIGNAL(finished(int , QProcess::ExitStatus )), this, SLOT(process_finished(int , QProcess::ExitStatus )));
    process->setWorkingDirectory(intall_path);
    process->execute("powershell",QStringList() << intall_path + "\\msys2_shell.cmd -c 'bash <(curl -s https://raw.githubusercontent.com/splashkit/skm/master/install-scripts/skm-install.sh) .'" << "2>&1" );
    process->waitForFinished();
    ui->txt_process->setText("Installation Completed.");
}

void MainWindow::process_finished(int code, QProcess::ExitStatus status)
{
    if(cProcess == "msys" && code == 0){
        ui->txt_process->setText("MSYS2 Installation Completed");
        start_first_run();
    }
    if(cProcess == "first_run" && code == 0){
        ui->txt_process->setText("Setting up MSYS");
        install_git();
    }
    if(cProcess == "git" && code == 0){
        ui->txt_process->setText("Git installation completed");
        install_skm();
    }


}

void MainWindow::stateChangedslot(QProcess::ProcessState state)
{
   qDebug() << state;
}







