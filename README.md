# Mylist

Mylist is a modern desktop To-Do List application built using **C++** and the **Qt Framework**.
The application helps users manage tasks efficiently with reminders, notifications, task exporting, and a clean QSS-styled user interface.

---

# Features

* User Authentication System
* Task Management (Create, Delete, Search)
* Task Details Dialog
* Reminder System
* Overdue Desktop Notifications
* Task Export to TXT File
* QSS Styled Modern UI
* Portable Desktop Deployment Support

---

# Technologies Used

* C++
* Qt
* SQLite
* QSS (Qt Style Sheets)
* CMake

---

# Screenshots

## Login Page

![Login](sceenshots/Login.png)

---

## Dashboard

![Dashboard](sreenshots/Dashboard.png)

---

## User Profile

![Profile](sreenshots/profile.png)

---

## Task Details

![Task Details](sreenshots/task_details.png)

---

# Project Structure

```text
MYLIST_APP/
│
├── Forms/
├── Headers/
├── Sources/
├── Styles/
├── icons/
│
├── resources.qrc
├── CMakeLists.txt
├── README.md
├── .gitignore
```
# Main Pillers 
* main.cpp              : Entry point of the application.
* mainwindow.cpp        : Contains main app logic and UI event handling.
* taskmanager           : Handles the all task-related operations (CRUD operations)
* authmanager           : Handles user authentication features (Registration , Login , current user)
* databasemanager       : Handles DB connection and set-up (SQLite)
* taskdetailsdialog.cpp : Manages task details dialog window (Detailed info)
* userprofile.cpp       : User info and exporting task into txt.


# Future Improvements

## Planned AI Integration

Future versions of Mylist aim to integrate AI-powered productivity features such as:

* Smart Task Prioritization
* AI Task Suggestions
* Deadline Prediction
* Productivity Analytics
* Natural Language Task Input
* AI Reminder Recommendations

---

# Author

Developed by Jibin George
