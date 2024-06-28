#pragma once
#include <QWidget>
#include "Service.h"
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

class GUI : public QWidget
{
private:
	Repository& repo;
	Service& service;

	void initialise();

	QListWidget* list;
	QPushButton* showBestMatch;
	QLabel* bestMatchDocument;
	QLineEdit* searchInput;

public:
	GUI(Repository& r, Service& s);
	~GUI() {}

	void populateList();
	void connectSignalsAndSlots();
	int getSelectedIndex() const;
	void showBestMatchHandler();
	
};
