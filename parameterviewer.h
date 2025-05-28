#ifndef PARAMETERVIEWER_H
#define PARAMETERVIEWER_H

#include <QTableView>

#include "comboboxdelegate.h"
#include "parametermodel.h"

class ParameterViewer : public QTableView
{
public:
    ParameterViewer();
    void load_parameter(const QString &parameter_file_name);
    void save_parameter(const QString &parameter_file_name);
    QString get_cell_name();
    QString get_drug_name();
    QString get_user_name();
    int get_sample_size();
private:
    ComboBoxDelegate *combo_cellname;
    ComboBoxDelegate *combo_celltype;
    ComboBoxDelegate *combo_solver;
    ParameterModel *model;
};

#endif // PARAMETERVIEWER_H
