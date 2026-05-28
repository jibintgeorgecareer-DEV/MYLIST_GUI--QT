#include "taskdetailsdialog.h"
#include "ui_taskdetailsdialog.h"

#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>   // sql errors
#include <QDebug>
#include <QFile>

TaskDetailsDialog::TaskDetailsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TaskDetailsDialog)
{
    ui->setupUi(this);

    //------Qss Styles load--------------------------------------
    QFile file(":/styles/taskdetailsdialog.qss");
    if(file.open(QFile::ReadOnly))
    {
        QString styles = QLatin1String(file.readAll());
        this->setStyleSheet(styles);
    }
    //-------------------------------------------------------
}

TaskDetailsDialog::~TaskDetailsDialog()
{
    delete ui;
}

int TaskDetailsDialog::get_current_task_id()
{
    return current_task_id;
}

void TaskDetailsDialog::loadTaskDetails(int task_id)
{
    QSqlQuery query;

    query.prepare("SELECT * FROM tasks WHERE id=:task_id;");
    query.bindValue(":task_id",task_id);
    query.exec();

    if(query.next())
    {
        current_task_id=query.value("id").toInt();
        ui->dia_task->setText(query.value("task").toString());
        ui->dia_description->setText(query.value("description").toString());
        ui->dia_startdate->setText(query.value("date_stored").toString());
        ui->dia_enddate->setText(query.value("date_end").toString());
        ui->dia_priority->setText(query.value("priority").toString());
        ui->dia_status->setCurrentText(query.value("status").toString());
    }
}

void TaskDetailsDialog::on_dia_save_clicked()
{
    QSqlQuery query;

    QString task = ui->dia_task->text();
    QString description = ui->dia_description->text();
    QString startdate = ui->dia_startdate->text();
    QString enddate = ui->dia_enddate->text();
    QString priority = ui->dia_priority->text();
    QString status = ui->dia_status->currentText();

    query.prepare("UPDATE tasks SET status=:status,task=:task,description=:description,date_stored=:startdate,date_end=:enddate,priority=:priority WHERE id=:current_task_id;");
    query.bindValue(":status",status);
    query.bindValue(":current_task_id",current_task_id);
    query.bindValue(":task",task);
    query.bindValue(":description",description);
    query.bindValue(":startdate",startdate);
    query.bindValue(":enddate",enddate);
    query.bindValue(":priority",priority);

    if(query.exec())
    {
        QMessageBox::information(this,"Success","Status Updated");
    }
    close();
}


void TaskDetailsDialog::on_dia_deletetask_clicked()
{
    QSqlQuery query;

    query.prepare("DELETE FROM tasks WHERE id=:current_task_id;");
    query.bindValue(":current_task_id",current_task_id);

    if(query.exec())
    {
        QMessageBox::information(this,"Success","Task Deleted!");
    }
    close();
}

