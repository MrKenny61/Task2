#include "student.h"


Student_model::Student_model(QObject *parent) : QAbstractTableModel(parent) {}


QVariant Student_model::headerData(int section, Qt::Orientation orientation, int role) const
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

int Student_model::rowCount(const QModelIndex &parent) const
{
    return vector.length();
}

int Student_model::columnCount(const QModelIndex &parent) const
{
    return 3;
}

QVariant Student_model::data(const QModelIndex &index, int role) const
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

bool Student_model::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(QModelIndex(), row, row + count - 1);

    student s;
    s.name="";
    s.course=0;
    s.group=0;
    vector.insert(parent.row()+1,s);

    endInsertRows();
    return true;
}

bool Student_model::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(QModelIndex(), row, row + count - 1);
    vector.removeAt(parent.row());
    endRemoveRows();
    return true;
}

bool operator>>(QDataStream &input,Student_model::student &item)
{
    QString in1, in2, in3;

    input>>in1;
    input>>in2;
    input>>in3;
    item.name = in1;
    item.course = in2.toUInt();
    item.group = in3.toUInt();

    return true;
}

bool operator<<(QDataStream &output, const Student_model::student &item)
{
    output << item.name;
    QString out2= QString::number(item.course);
    QString out3 = QString::number(item.group);
    output<<out2;
    output<<out3;
    return true;
}
