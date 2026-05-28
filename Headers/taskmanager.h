#ifndef TASKMANAGER_H
#define TASKMANAGER_H

//#include "authmanager.h"
#include <QString>
#include <QStringList>
#include <QSqlQuery> //DB

class TaskManager
{
public:
    TaskManager();
    bool addTask(int current_user_id, QString task, QString description, QString date_stored, QString date_end, QString priority, QString status);
    bool deleteTask(int task_id);
    QSqlQuery loadTask(int current_user_id);

    //Search System-----------------------------------------------------
    QSqlQuery searchTask(int current_user_id, QString keyword);
    QSqlQuery searchByPriority(int current_user_id, QString keyword);
    QSqlQuery taskByStatus(int current_user_id, QString status);
    //------------------------------------------------------------------


    //Task Counter---------------------------------------------
    int totalTasks(int current_user_id);
    int completedTasks(int current_user_id);
    int pendingTasks(int current_user_id);
    //---------------------------------------------------------

    QStringList remainder(int current_user_id); //Remainder System for today tasks
    QStringList overdueTask(int current_user_id); //Notification for overdue tasks

};

#endif // TASKMANAGER_H
