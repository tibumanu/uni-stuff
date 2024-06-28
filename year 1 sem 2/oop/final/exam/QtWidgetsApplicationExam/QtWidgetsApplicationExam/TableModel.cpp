#include "TableModel.h"
#include <QtWidgets>

int TableModel::rowCount(const QModelIndex& parent) const
{
	return this->service.getIdeas().size();
}

int TableModel::columnCount(const QModelIndex& parent) const
{
	return 5;
}

QVariant TableModel::data(const QModelIndex& index, int role) const
{

	Idea *i = this->service.getIdeas()[index.row()];
	if (role == Qt::DisplayRole)
	{
		switch (index.column())
		{
		case 0:
			return QString::fromStdString(i->getTitle());
			case 1:
				return QString::fromStdString(i->getDescription());
			case 2:
				return QString::fromStdString(i->getStatus());
			case 3:
				return QString::fromStdString(i->getCreator());
			case 4:
				return QString::number(i->getDuration());

		default:
			break;
		}
	}
	return QVariant();
}


void TableModel::populate()
{
	this->beginResetModel();
	for (auto i : this->service.getIdeas())
	{
		this->addIdea(i->getTitle(), i->getDescription(), i->getStatus(), i->getCreator(), i->getDuration());
	}
	this->endResetModel();
}

void TableModel::sortData()
{
	// sort by duration
	std::sort(this->service.getIdeas().begin(), this->service.getIdeas().end(), [](Idea* i1, Idea* i2) {
		return i1->getDuration() > i2->getDuration();
	});
}

Idea* TableModel::getIdea(int row)
{
	return this->service.getIdeas()[row];
}

Idea& TableModel::getIdeaRef(int row)
{
	return *this->service.getIdeas()[row];
}

void TableModel::acceptIdea(int row)
{
	beginResetModel();
	this->service.getIdeas()[row]->setStatus("accepted");
	endResetModel();

}


QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole)
	{
		if (orientation == Qt::Horizontal)
		{
			switch (section)
			{
			case 0:
				return "Title";
			case 1:
				return "Description";
			case 2:
				return "Status";
			case 3:
				return "Creator";
			case 4:
				return "Duration";

			default:
				break;

			}
		}
	}
	return QVariant();
}

void TableModel::addIdea(std::string title, std::string description, std::string status, std::string creator, int duration)
{

	// ROWS should be inserted, not columns
	beginInsertRows(QModelIndex(), this->service.getIdeas().size(), this->service.getIdeas().size());
	this->service.addIdea(title, description, status, creator, duration);
	endInsertRows();

}
