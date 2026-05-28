#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "authmanager.h" //authentication
#include "taskmanager.h" //tasks managements
#include "taskdetailsdialog.h"

#include <QMainWindow>
#include <QMessageBox>
#include <QListWidgetItem> //Access item in List
#include <QSystemTrayIcon> // Set desktop notifications

QT_BEGIN_NAMESPACE
namespace Ui {    //When compile .ui , Qt UIC creates Ui::MainWindow
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:  //Qt Meta-Object System can invoke private functions only inside mainwindow.cpp

    void on_btn_login_clicked();  //login button
    void on_btn_register_button_clicked();  //register button

    void on_btn_goto_register_clicked();
    void on_btn_goto_login_clicked();

    void on_btn_addtask_clicked();
    void load_all_tasks();

    void on_btn_deletetask_2_clicked();

    void on_btn_searchtask_clicked();

    void taskCounter();//Display task statitics

    void on_btn_comtask_clicked();

    void on_btn_pentasks_clicked();

    void on_btn_alltasks_clicked();

    void on_task_list_itemClicked(QListWidgetItem *item);

    void on_btn_profile_clicked();

    void on_btn_searchpriority_clicked();

    void remainderAlert();

    void overdueNotification();

private:
    Ui::MainWindow *ui;
    int current_user_id;
    AuthManager auth;
    TaskManager taskman;
    TaskDetailsDialog dialog;

    QSystemTrayIcon *notification; //Desktop notification system obj
};
#endif // MAINWINDOW_H
