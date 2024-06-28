#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtWidgetsApplicationExam.h"
#include "Service.h"
#include "TableModel.h"
#include <QtWidgets>

class QtWidgetsApplicationExam : public QWidget
{
    Q_OBJECT

public:
    QtWidgetsApplicationExam(Service* service, Researcher* researcher, TableModel* model, QWidget* parent = nullptr);
    ~QtWidgetsApplicationExam();
    void addIdea();
    void acceptIdea();
    void selectionChangedHandler();

private:
    
    TableModel* model;
    QTableView* view;
    Service* service;
    Researcher* researcher;
    // fields for adding idea
    QLineEdit* titleEdit;
    QLineEdit* descriptionEdit;
    QLineEdit* durationEdit;
    QPushButton* addButton;
    QLabel* positionLabel;
    
    // accept button
    QPushButton* acceptButton;
    
    QPushButton* saveAllAcceptedButton;


};
