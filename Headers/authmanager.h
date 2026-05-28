#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H
#include <QString>

class AuthManager
{
public:
    AuthManager();

    bool registerUser(QString username,QString password,QString email);
    bool loginUser(QString username,QString password);
    int get_current_user_id();
    QString get_current_user_name();
    void logOut();



private:
    int current_user_id;
    QString current_user_name;
};

#endif // AUTHMANAGER_H
