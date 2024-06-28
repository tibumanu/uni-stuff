#pragma once
#include <qabstractitemmodel.h>
#include "Service.h"
#include <string>

class TableModel : public QAbstractTableModel
{
private:
	Service& service;

public:
	TableModel(Service& service) : service{ service } {
		//populate();
	}
	int rowCount(const QModelIndex& parent = QModelIndex()) const;
	int columnCount(const QModelIndex& parent = QModelIndex()) const;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
	void populate();
	void sortData();
	// get idea at row
	Idea* getIdea(int row);
	Idea& getIdeaRef(int row);
	void acceptIdea(int row);
	// get item at row

	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
	void addIdea(std::string title, std::string description, std::string status, std::string creator, int duration);
};
