#include "QtWidgetsApplicationExam.h"
#include <QtWidgets>

QtWidgetsApplicationExam::QtWidgetsApplicationExam(Service* service, Researcher* researcher, TableModel* model, QWidget* parent)
{

    this->service = service;
    this->researcher = researcher;

    setWindowTitle(QString::fromStdString(researcher->getName()));

    this->model = model;

    this->view = new QTableView;
    this->view->setModel(this->model);
    this->view->setSelectionBehavior(QAbstractItemView::SelectRows); // !!!!!!!!!!!!!!!!!!!!!!!!

    this->view->sortByColumn(4, Qt::DescendingOrder);

    this->addButton = new QPushButton("Add");

    this->titleEdit = new QLineEdit;
    this->descriptionEdit = new QLineEdit;
    this->durationEdit = new QLineEdit;

    QVBoxLayout* addLayout = new QVBoxLayout;
    addLayout->addWidget(new QLabel("Title"));
    addLayout->addWidget(this->titleEdit);
    addLayout->addWidget(new QLabel("Description"));
    addLayout->addWidget(this->descriptionEdit);
    addLayout->addWidget(new QLabel("Duration"));
    addLayout->addWidget(this->durationEdit);
    addLayout->addWidget(this->addButton);

    if (researcher->getPosition() == "senior")
    {
		this->acceptButton = new QPushButton("Accept");
		addLayout->addWidget(this->acceptButton);
        this->saveAllAcceptedButton = new QPushButton("Save all accepted");
        addLayout->addWidget(this->saveAllAcceptedButton);
	}

    QVBoxLayout* mainLayout = new QVBoxLayout;
    this->positionLabel = new QLabel(QString::fromStdString(researcher->getPosition()));
    mainLayout->addWidget(this->positionLabel);
    mainLayout->addWidget(this->view);
    mainLayout->addLayout(addLayout);
    setLayout(mainLayout);
    // connect add button
    QObject::connect(this->addButton, &QPushButton::clicked, this, &QtWidgetsApplicationExam::addIdea);
    
    if (researcher->getPosition() == "senior")
    {
        QObject::connect(this->view->selectionModel(), &QItemSelectionModel::selectionChanged, this, &QtWidgetsApplicationExam::selectionChangedHandler);
        QObject::connect(this->acceptButton, &QPushButton::clicked, this, &QtWidgetsApplicationExam::acceptIdea);
        QObject::connect(this->saveAllAcceptedButton, &QPushButton::clicked, [this]() {
			this->service->saveAllAccepted();
			this->view->viewport()->update();
		});
    }
    setMinimumWidth(580);
    // sort by duration
    this->model->sort(4, Qt::DescendingOrder);
    //this->model->sortData();
}

QtWidgetsApplicationExam::~QtWidgetsApplicationExam()
{}

void QtWidgetsApplicationExam::addIdea()
{
    std::string title = this->titleEdit->text().toStdString();
    std::string description = this->descriptionEdit->text().toStdString();
    int duration = this->durationEdit->text().toInt();
    std::string researcherName = this->researcher->getName();

    if (duration < 1 || duration > 3 || title.empty())
    {
		QMessageBox messageBox;
		messageBox.warning(0, "Error", "Invalid input.");
		messageBox.setFixedSize(500, 200);
        this->titleEdit->clear();
        this->descriptionEdit->clear();
        this->durationEdit->clear();
		return;
	}
    this->model->addIdea(title, description, "proposed", researcherName, duration);

    this->view->viewport()->update();
	
}

void QtWidgetsApplicationExam::acceptIdea()
{
    // get selected idea/row; if status is "accepted", disable button
    QModelIndexList selectedIndexes = this->view->selectionModel()->selectedRows();
    if (selectedIndexes.size() == 0)
    {
        this->acceptButton->setDisabled(true);
    }
    else
    {
		QModelIndex selectedIndex = selectedIndexes.at(0);
        if (selectedIndex.isValid())
        {
			int row = selectedIndex.row();
			Idea* i = this->model->getIdea(row);
            if (i->getStatus() == "accepted")
            {
				this->acceptButton->setDisabled(true);
			}
            else
            {
				this->acceptButton->setEnabled(true);
				this->model->acceptIdea(row);
				this->view->viewport()->update();
			}
		}
	}


}

void QtWidgetsApplicationExam::selectionChangedHandler() {
    // if status is "accepted", disable button
    QModelIndexList selectedIndexes = this->view->selectionModel()->selectedRows();
    if (selectedIndexes.size() == 0)
    {
		this->acceptButton->setDisabled(true);
	}
    else
    {
		QModelIndex selectedIndex = selectedIndexes.at(0);
        if (selectedIndex.isValid())
        {
			int row = selectedIndex.row();
			Idea* i = this->model->getIdea(row);
            if (i->getStatus() == "accepted")
            {
				this->acceptButton->setDisabled(true);
			}
            else
            {
				this->acceptButton->setEnabled(true);
			}
		}
	}
}
