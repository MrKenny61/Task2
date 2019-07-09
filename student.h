#ifndef STUDENT_H
#define STUDENT_H

#endif // STUDENT_H

#include <QAbstractTableModel>
#include <QVector>

using namespace std;

typedef unsigned int uint;

class Student_model : public QAbstractTableModel
{
private:
    Q_OBJECT
public:
    struct student
    {
        char name[30];
        uint course;
        uint group;
    };

    Student_model(QObject *parent = nullptr);

    QVector <student> vector;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const
    {
        if (role==Qt::DisplayRole){
            if (orientation==Qt::Horizontal){

            switch (section) {
             case 0:return QString("Name");
             case 1:return QString("Course");
             case 2:return QString("Group")  ;

            default:
                break;
            }
        }
        }
        return QVariant();
    }

    int rowCount(const QModelIndex &parent = QModelIndex()) const
    {
        return vector.length();
    }

    int columnCount(const QModelIndex &parent = QModelIndex()) const
    {
        return 3;
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const
    {
        if (role==Qt::DisplayRole){
            switch (index.column()) {
             case 0:return vector.at(index.row()).name;
             case 1:return vector.at(index.row()).course;
             case 2:return vector.at(index.row()).group;

            default:
                break;
            }
        }
        return QVariant();
    }
};
