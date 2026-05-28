#ifndef TASKDETAILSDIALOG_H
#define TASKDETAILSDIALOG_H

#include <QDialog>
#include <QMessageBox>


namespace Ui {
class TaskDetailsDialog;
}

class TaskDetailsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TaskDetailsDialog(QWidget *parent = nullptr);
    ~TaskDetailsDialog();

    void loadTaskDetails(int task_id);

private slots:
    void on_dia_save_clicked();
    int get_current_task_id();

    void on_dia_deletetask_clicked();

private:
    Ui::TaskDetailsDialog *ui;

    int current_task_id=-1; //Selected task
};

#endif // TASKDETAILSDIALOG_H
