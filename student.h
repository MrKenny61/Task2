#ifndef STUDENT_H
#define STUDENT_H

#include <QAbstractTableModel>
#include <QVector>
#include <QString>
#include <QDataStream>

using namespace std;

class Student_model : public QAbstractTableModel
{
private:
    Q_OBJECT
public:
    struct student
    {
        QString name;
        uint course;
        uint group;
    };

    Student_model(QObject *parent = nullptr);

    QVector <student> vector;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

};

bool operator>>(QDataStream &input,Student_model::student &item);

bool operator<<(QDataStream &output, const Student_model::student &item);

#endif // STUDENT_H
