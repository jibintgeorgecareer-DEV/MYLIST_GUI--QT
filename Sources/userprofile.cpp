#include "userprofile.h"
#include "ui_userprofile.h"

#include "authmanager.h"
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include <QFile>

UserProfile::UserProfile(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UserProfile)
{
    ui->setupUi(this);

    //----QSS style loading-----------------
    QFile file(":/styles/userprofile.qss");
    if(file.open(QFile::ReadOnly))
    {
        QString styles = QLatin1String(file.readAll());
        this->setStyleSheet(styles);
    }
    //------------------------------------------
}

UserProfile::~UserProfile()
{
    delete ui;
}

void UserProfile::loadProfile(int current_user_id)
{
    QSqlQuery query;

    query.prepare("SELECT * FROM  users WHERE id=:current_user_id;");
    query.bindValue(":current_user_id",current_user_id);
    query.exec();

    if(query.next())
    {
        ui->username->setText(query.value("username").toString());
        ui->useremail->setText(query.value("email").toString());

    }
}

void UserProfile::receiveAuth(AuthManager *obj)
{
    auth=obj; //Receive the auth object from mainwindow class , it sends a pointer
}

void UserProfile::on_pushButton_2_clicked()
{
    auth->logOut();
    qDebug()<<"ID user:"<<auth->get_current_user_id();
    close();
}


void UserProfile::on_btn_export_clicked()
{
    if(exporter.exportTxt(auth->get_current_user_id()))
    {
        QMessageBox::information(this,"EXPORT","Exported into txt file");
    }
    else
    {
        QMessageBox::information(this,"EXPORT","Export Failed");
    }
}

