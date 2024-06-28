#include "GUI.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>



GUI::GUI(Repository& r, Service& s) : repo{ r }, service{ s }
{
	this->list = new QListWidget{};
	this->showBestMatch = new QPushButton{ "Show best matching" };
	this->bestMatchDocument = new QLabel{};
	this->searchInput = new QLineEdit{};
	this->initialise();
	this->populateList();
	this->connectSignalsAndSlots();
}



void GUI::initialise()
{
	this->setFixedSize(800, 600);
	auto* layout = new QVBoxLayout{ this };
	layout->addWidget(this->list);
	auto* bestMatchLayout = new QHBoxLayout{};
	auto *searchLayout = new QGridLayout{};
	searchLayout->addWidget(this->searchInput, 0, 0);
	layout->addLayout(searchLayout);
	bestMatchLayout->addWidget(this->showBestMatch);
	bestMatchLayout->addWidget(this->bestMatchDocument);
	layout->addLayout(bestMatchLayout);
}



void GUI::populateList(){
		/*this->list->clear();
		std::vector<Document> docs = this->repo.getDocuments();
		for (auto& el : docs)
		{
			QString itemInList = QString::fromStdString(el.toString());
			QListWidgetItem* item = new QListWidgetItem{ itemInList };
			this->list->addItem(item);
		}		*/
	// the list should be sorted by Name
	std::vector<Document> docs = this->service.getDocuments();
	std::sort(docs.begin(), docs.end(), [](Document& d1, Document& d2) {return d1.getName() < d2.getName(); });
	for (auto& el : docs){
		QString itemInList = QString::fromStdString(el.toString());
		QListWidgetItem* item = new QListWidgetItem{ itemInList };
		this->list->addItem(item);
		}
	}


int GUI::getSelectedIndex() const
{
	return this->list->currentIndex().row();
}

void GUI::showBestMatchHandler()
{
	std::string name = this->searchInput->text().toStdString();
	Document bestMatch = this->service.getDocumentByName(name);
	this->bestMatchDocument->setText(QString::fromStdString(bestMatch.toString()));
}




void GUI::connectSignalsAndSlots()
{
	QObject::connect(this->showBestMatch, &QPushButton::clicked, this, &GUI::showBestMatchHandler);


	QObject::connect(this->searchInput, &QLineEdit::textChanged, [this]() {
		std::string text = this->searchInput->text().toStdString();
		std::vector<Document> docs = this->service.searchForTextInDocuments(text);
		this->list->clear();
		for (auto& el : docs) {
			QString itemInList = QString::fromStdString(el.toString());
			QListWidgetItem* item = new QListWidgetItem{ itemInList };
			this->list->addItem(item);
		}
	});
		
}
