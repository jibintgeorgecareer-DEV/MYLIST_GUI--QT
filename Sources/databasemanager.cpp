#include "databasemanager.h"

#include <QSqlDatabase> //Sql DB connection
#include <QSqlQuery>    //Sql query execute
#include <QSqlError>    //Sql Error handling

#include <QDebug>       //Qt build in Debug handling
#include <QFileInfo> //To find a file path

DatabaseManager::DatabaseManager()
{
    //constructor
}

bool DatabaseManager::connectDatabase()
{
    // -------------Set Up SQLite Connection---------------------------------------

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("Mylist.db"); //Mylist_APP\build\Desktop_Qt\Mylist.db"

    if(db.open())
    {
        qDebug() <<"Qt - SQL : Connection Successfull!";
        qDebug() << "SQL file path:"<< QFileInfo(db.databaseName()).absoluteFilePath();
        return true;
    }
    else
    {
        qDebug() <<"Qt - SQL : Connection Failed!";
        return false;
    }

    //-----------------End SQL Connection Setup-------------------------------------------
}

void DatabaseManager::createTables()
{
    QSqlQuery query; //object to write sql queries.

    query.exec(                             //user table
        "CREATE TABLE IF NOT EXISTS users("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "username TEXT UNIQUE,"
        "password TEXT"
        ")"
        );

    query.exec(                             //task table
        "CREATE TABLE IF NOT EXISTS tasks("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "user_id INTEGER,"
        "task TEXT,"
        "description TEXT,"
        "date_stored TEXT,"
        "date_end TEXT,"
        "priority TEXT,"
        "status TEXT"
        ")"
        );
}