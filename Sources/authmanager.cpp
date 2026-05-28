#include "authmanager.h"
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>

AuthManager::AuthManager()
{
    current_user_id=-1; //-1 for if no user logged in
}

bool AuthManager::registerUser(QString username, QString password, QString email)
{
    QSqlQuery query;

    query.prepare(
        "INSERT INTO users(username,password,email)"
        "VALUES(:username,:password,:email)"
        );

    query.bindValue(":username",username);
    query.bindValue(":password",password);
    query.bindValue(":email",email);

    return query.exec();
}

bool AuthManager::loginUser(QString username, QString password)
{
    QSqlQuery query;

    query.prepare(
        "SELECT * FROM users "
        "WHERE username=:username "
        "AND password=:password"
        );

    query.bindValue(":username",username);
    query.bindValue(":password",password);

    query.exec();

    if(query.next())
    {
        current_user_id=query.value("id").toInt(); //Saving user ID from DB
        current_user_name=query.value("username").toString();//Save name from DB

        qDebug()<<"AuthManager:Login User->"<<query.value("username").toString();
        qDebug()<<"AuthManager:Login User ID->"<<query.value("id").toString();


        return true;
    }

    return false;
}

int AuthManager::get_current_user_id()
{
    return current_user_id;
}
QString AuthManager::get_current_user_name()
{
    return current_user_name;
}

void AuthManager::logOut()
{
    current_user_id=-1;
    current_user_name="";
}