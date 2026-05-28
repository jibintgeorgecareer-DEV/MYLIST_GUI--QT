#ifndef USERPROFILE_H
#define USERPROFILE_H

#include "authmanager.h"
#include "exportintofile.h"

#include <QDialog>

namespace Ui {
class UserProfile;
}

class UserProfile : public QDialog
{
    Q_OBJECT

public:
    explicit UserProfile(QWidget *parent = nullptr);
    ~UserProfile();

    void loadProfile(int current_user_id);

    void receiveAuth(AuthManager *obj);
private slots:
    void on_pushButton_2_clicked();

    void on_btn_export_clicked();

private:
    Ui::UserProfile *ui;
    AuthManager *auth;
    ExportIntoFile exporter;

};

#endif // USERPROFILE_H
