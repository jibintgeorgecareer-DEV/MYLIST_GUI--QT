#include "exportintofile.h"

#include <QFile>
#include <QTextStream>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDate>
#include <QFileDialog>

ExportIntoFile::ExportIntoFile()
{

}

bool ExportIntoFile::exportTxt(int current_user_id)
{

    QString filename = QFileDialog::getSaveFileName(nullptr,"Save Tasks","Mylists.txt","Text Files (*.txt)");

        QFile file(filename);

        if(!file.open(QIODevice::WriteOnly| QIODevice::Text)) //create file , if file already
        {                                                    // already there rewrite it.
            qDebug()<<"File not opened";

            return false;
        }

        QTextStream write_to(&file);

        QSqlQuery query;

        query.prepare("SELECT task,description,date_stored,date_end,priority,status FROM tasks WHERE user_id=:current_user_id");
        query.bindValue(":current_user_id",current_user_id);
        query.exec();
        qDebug()<<"SQL ERROR:"<<query.lastError().text();
        qDebug()<<"user_id in export:"<<current_user_id;

        int i=1;
        while(query.next())
        {
            write_to << "No: "
                <<i
                <<"\n";
            write_to << "Task: "
                << query.value("task").toString()
                << "\n";
            qDebug()<<"Task in while loop:"<<query.value("task").toString();

            write_to << "Description: "
                << query.value("description").toString()
                << "\n";

            write_to << "Start Date: "
                << query.value("date_stored").toString()
                << "\n";

            write_to << "End Date: "
                << query.value("date_end").toString()
                << "\n";

            write_to << "Priority: "
                << query.value("priority").toString()
                << "\n";

            write_to << "Status: "
                << query.value("status").toString()
                << "\n";

            write_to << "-------------------\n";
            i++;
        }

        file.close();

        return true;
}