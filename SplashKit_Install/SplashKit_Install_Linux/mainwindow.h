#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcessEnvironment>
#include <QDir>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QObject>
#include <QUrl>
#include <QProcess>
#include <QProgressBar>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QFile *m_file;
    bool m_isReady = true;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QProcess *process;

private slots:
    void readOutput();
    void progressbar_update();

    void on_btn_install_clicked();
    void install_curl_git();
    void install_skm();
    void make_splashkit();
    void install_vscode();
    void install_dotnet();
    void process_finished(int code, QProcess::ExitStatus status);

    void on_btn_cancel_clicked();

private:
    Ui::MainWindow *ui;
    QString cProcess;
    QString cStatus;
    bool completeProc;
    int cSteps;
};
#endif // MAINWINDOW_H
