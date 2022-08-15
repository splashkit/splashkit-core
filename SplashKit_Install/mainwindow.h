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
    void downloadFileFromURL(const QString &url, const QString &filePath);
    QProcess *process;

private slots:
    void onDownloadFileComplete(QNetworkReply *reply);
    void readOutput();
    void progressbar( qint64 recieved,  qint64 total);

    void on_btn_install_clicked();
    void start_install_msys();
    void start_first_run();
    void install_git();
    void install_skm();
    void process_finished(int code, QProcess::ExitStatus status);
    void on_btn_sel_path_clicked();

    void on_btn_cancel_clicked();

private:
    Ui::MainWindow *ui;
    QString cProcess;
    bool completeProc;
};
#endif // MAINWINDOW_H
