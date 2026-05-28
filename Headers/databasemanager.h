#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase> //Sql DB connection

class DatabaseManager
{
public:
    DatabaseManager();
    bool connectDatabase();
    void createTables();

};

#endif
