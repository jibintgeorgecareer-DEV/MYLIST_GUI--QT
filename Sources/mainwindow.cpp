#include "mainwindow.h"
#include "databasemanager.h"
#include "./ui_mainwindow.h" //Auto Generates UIC from mainwindow.ui

#include "taskdetailsdialog.h" //Task details dialog

#include "authmanager.h" //authentication
#include "taskmanager.h" //tasks managements
#include "userprofile.h" //User Profile

#include <QListWidgetItem> //To manage task of list

#include <QSqlQuery>    //Sql query execute
#include <QSqlError>    //Sql Error handling
#include <QSqlDatabase> //DB connection

#include <QDebug>       //Qt build in Debug handling
#include <QDate> //To get system date

#include <QFile> //Import QSS files

MainWindow::MainWindow(QWidget *parent) //Constructore defined
    : QMainWindow(parent)  //CAlling parent constructor  , Set QMainwindow top level
    , ui(new Ui::MainWindow) //ui = new Ui::MainWindow;
{
    ui->setupUi(this);   //Helper class fun managing widgets of ui_mainwindow.h (mainwindow.ui)
    this->setMinimumWidth(1300); //Ui window width

    //---------loading Qss files---------------------------------------------
    QFile file(":/styles/mainwindow.qss");
    if(file.open(QFile::ReadOnly))
    {
        QString styles = QLatin1String(file.readAll());
        this->setStyleSheet(styles);
    }
    //-------------------------------------------------------------------------


    ui->stackedWidget->setCurrentIndex(0); //To start app on login page

//------Set DataBase-----------------------------------------------------------
    DatabaseManager db; //From Database module (SQL-Qt connection)
    db.connectDatabase();
    db.createTables();
//------------------------------------------------------------------------------

    //-----------------Notification constructor-----------------------------------

    notification = new QSystemTrayIcon(this); // 'this' make the QSystemTrayIcon child of mainwindow
    notification->setIcon(QIcon(":/icons/logo.ico"));
    notification->show();
    //------------------------------------------------------------------------------
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_login_clicked() //Login User
{
    QString username = ui -> login_name -> text();
    QString password = ui -> login_password -> text();

    QSqlQuery query;

    if (auth.loginUser(username,password))
    {
        QString USER = auth.get_current_user_name();

        QMessageBox::about(this,"AUTHENTICATION","Login Sucessfull\nThis is my personal project");

        load_all_tasks(); //load task in dash
        taskCounter(); //load Task ststi in dash

        ui->dash_username->setText(auth.get_current_user_name());

        ui->stackedWidget->setCurrentIndex(2);//Go to Dash
        remainderAlert();//Remainder System awake
        overdueNotification();//Notification system awake.

    }
    else
    {
        QMessageBox::information(this,"Failed","NOT A USER");
    }

}

void MainWindow::on_btn_register_button_clicked() //Register User
{
    //auth declared in mainwindow.h

    QString username = ui->register_name->text();
    QString password = ui->register_password->text();
    QString email = ui->register_email->text();

    if(username.isEmpty() || password.isEmpty())
    {
        QMessageBox::warning(this,"REGISTER","field is EMPTY!");
        return;
    }

            if(auth.registerUser(username,password,email))
            {
            QMessageBox::information(this,"SUCCESS","YOU ARE REGISTERED");
            ui->stackedWidget->setCurrentIndex(0);
            }
            else
            {
            QMessageBox::information(this,"FAILED","Something Wrong!");
            }

}

void MainWindow::on_btn_goto_register_clicked() //From login to register
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_btn_goto_login_clicked() //From Register to login
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::load_all_tasks() //Fetch tasks from TaskManager fun
{
    ui->task_list->clear();

    QSqlQuery query = taskman.loadTask(auth.get_current_user_id());

    while(query.next())
    {
        QString task= query.value("task").toString();
        int task_id= query.value("id").toInt();

        QListWidgetItem *item = new QListWidgetItem(task);

        item->setData(Qt::UserRole,task_id); //UserRole is a custom hidden data for hide task_id

        ui->task_list->addItem(item);
    }
}


void MainWindow::on_btn_addtask_clicked() //ADD Task to DB
{
    QString task = ui->dash_task->text();
    QString description = ui->task_description->text();
    QString date_end =ui->task_end->text();
    QString priority = ui->task_priority->currentText();
    QString status = "Pending";
    QString date_stored = QDate::currentDate().toString("yyyy-MM-dd");

    if(task.isEmpty())
    {
        QMessageBox::warning(this,"FAILED","Enter Task");
        return;
    }
    if(priority == "SELECT PRIORITY")
    {
        priority="";
    }
    //taskman declared in .h to manage tasks

    bool okey=taskman.addTask(auth.get_current_user_id(),task,description,date_stored,date_end,priority,status);

    if(okey)
    {
        QMessageBox::information(this,"Succesfull","Task Added");
        load_all_tasks();
        taskCounter();

        ui->dash_task->clear();
        ui->task_description->clear();
    }
    else
    {
        QMessageBox::information(this,"Failed","Task Not Added!");
    }

}

void MainWindow::on_btn_deletetask_2_clicked()
{
    QListWidgetItem *item = ui->task_list->currentItem(); //Get selected task to delete
    if (item==nullptr)
    {
        QMessageBox::warning(this, "SELECT TASK", "Select task from list");
        return;
    }

    int task_id=item->data(Qt::UserRole).toInt();

    if(taskman.deleteTask(task_id))
    {
        load_all_tasks();
        taskCounter();
        QMessageBox::information(this,"DELETED","Task Deleted");
    }
    else
    {
        QMessageBox::warning(this,"FAILED","Something went wrong");
    }

}

void MainWindow::on_btn_searchtask_clicked()
{
    ui->task_list->clear();
    QString keyword = ui->dash_searchtask->text();

    if(keyword.isEmpty())
    {
        load_all_tasks();
        QMessageBox::warning(this,"EMPTY","Enter Something");
    }

    QSqlQuery  query = taskman.searchTask(auth.get_current_user_id(),keyword);
    bool found = false;

    while(query.next())
    {
        found = true;

        QString task = query.value("task").toString();
        int task_id  = query.value("id").toInt();

        QListWidgetItem *item = new QListWidgetItem(task);

        item->setData(Qt::UserRole,task_id);
        ui->task_list->addItem(item);
    }

    if(!found)
    {
        ui->task_list->addItem("No Tasks");
    }
}

void MainWindow::taskCounter()
{
    int total_tasks = taskman.totalTasks(auth.get_current_user_id());
    int com_tasks = taskman.completedTasks(auth.get_current_user_id());
    int pen_tasks = taskman.pendingTasks(auth.get_current_user_id());

    ui->total_tasks->setText(QString::number(total_tasks));
    ui->com_tasks->setText(QString::number(com_tasks));
    ui->pen_tasks->setText(QString::number(pen_tasks));
}
void MainWindow::on_btn_comtask_clicked()
{
    ui->task_list->clear();

    QSqlQuery query = taskman.taskByStatus(auth.get_current_user_id(),"Completed");
    bool found=false;

    while(query.next())
    {
        found = true;

        QString task = query.value("task").toString();
        int task_id  = query.value("id").toInt();

        QListWidgetItem *item = new QListWidgetItem(task);

        item->setData(Qt::UserRole,task_id);
        ui->task_list->addItem(item);
    }

    if(!found)
    {
        ui->task_list->addItem("No Tasks");
    }
}


void MainWindow::on_btn_pentasks_clicked()
{
    ui->task_list->clear();

    QSqlQuery query = taskman.taskByStatus(auth.get_current_user_id(),"Pending");
    bool found=false;

    while(query.next())
    {
        found = true;

        QString task = query.value("task").toString();
        int task_id  = query.value("id").toInt();

        QListWidgetItem *item = new QListWidgetItem(task);

        item->setData(Qt::UserRole,task_id);
        ui->task_list->addItem(item);
    }

    if(!found)
    {
        ui->task_list->addItem("No Tasks");
    }

}

void MainWindow::on_btn_alltasks_clicked()
{
    ui->task_list->clear();
    load_all_tasks();
}


void MainWindow::on_task_list_itemClicked(QListWidgetItem *item)
{
    QString selected_task=item->text();

    int task_id = item->data(Qt::UserRole).toInt();

    dialog.loadTaskDetails(task_id);
    dialog.exec();

    taskCounter(); //To update the task counter after update.
    load_all_tasks();
}


void MainWindow::on_btn_profile_clicked()
{
    UserProfile profile;
    profile.receiveAuth(&auth); //sharing actual auth to userprofile

    profile.loadProfile(auth.get_current_user_id());
    profile.exec();

    qDebug()<<"ID in mainwindow, profile btn:"<<auth.get_current_user_id();
    if(auth.get_current_user_id() == -1) //if logout clicked go to login
    {
        ui->stackedWidget->setCurrentIndex(0);
    }
}


void MainWindow::on_btn_searchpriority_clicked()
{
    ui->task_list->clear();

    QString keyword = ui->search_priority->currentText();
    QSqlQuery query = taskman.searchByPriority(auth.get_current_user_id(),keyword);
    bool found = false;

    while(query.next())
    {
        found = true;
        QString task = query.value("task").toString();
        int task_id = query.value("id").toInt();

        QListWidgetItem *item = new QListWidgetItem(task);

        item->setData(Qt::UserRole,task_id);
        ui->task_list->addItem(task);

    }

    if(!found)
    {
        ui->task_list->addItem("No Tasks");
    }
}

void MainWindow::remainderAlert()
{
    QStringList tasks_remainders = taskman.remainder(auth.get_current_user_id());

    if(tasks_remainders.isEmpty())
    {
        return;
    }

    QString all_tasks_remainders; //To append all tasks into one string

    for(QString &i : tasks_remainders)
    {
        qDebug()<<"Remainders:"<<i;
        all_tasks_remainders=all_tasks_remainders+" "+i+" "+"\n";
    }
    QMessageBox::warning(this,"REMAINDER","Taks due today!\n\n" + all_tasks_remainders);
}

void MainWindow::overdueNotification()
{
    QStringList overdue_tasks =taskman.overdueTask(auth.get_current_user_id());

    if(overdue_tasks.isEmpty())
    {
        return;
    }

    QString all_tasks;

    for(QString &i : overdue_tasks)
    {
        all_tasks += "- " + i + "\n";
    }

    notification->showMessage("OVERDUE TASKS",all_tasks,QSystemTrayIcon::Warning,3000);
}