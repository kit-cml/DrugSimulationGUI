#ifndef PARAMETERMODEL_H
#define PARAMETERMODEL_H

#include <QStandardItemModel>
#include <QString>


class ParameterModel : public QStandardItemModel
{
public:
    explicit ParameterModel(QObject *parent = nullptr);
    void load_from_file(const QString &parameter_file_name);
    void save_to_file(const QString &parameter_file_name);
};

#endif // PARAMETERMODEL_H
