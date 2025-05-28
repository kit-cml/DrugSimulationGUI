#include "parameterviewer.h"

#include <QHeaderView>

#include "guiconstants.h"

ParameterViewer::ParameterViewer()
{
    combo_cellname = new ComboBoxDelegate(cmlgui::text::combobox::MAP_CELL_MODEL,this);
    combo_celltype = new ComboBoxDelegate(cmlgui::text::combobox::MAP_CELLTYPE,this);
    combo_solver = new ComboBoxDelegate(cmlgui::text::combobox::MAP_SOLVER,this);
    model = new ParameterModel(this);
    setModel(model);
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void ParameterViewer::load_parameter(const QString &parameter_file_name)
{
    model->load_from_file(parameter_file_name);
    // Apply delegate to specific rows (hill_file and herg_file)
    for (int row = 0; row < model->rowCount(); ++row) {
        QString param_name = model->item(row, 0)->text();
        if (param_name == "cell_name") {
            setItemDelegateForRow(row, combo_cellname);
        }
        if (param_name == "celltype") {
            setItemDelegateForRow(row, combo_celltype);
        }
        if (param_name == "solver_type") {
            setItemDelegateForRow(row, combo_solver);
        }
    }
}

void ParameterViewer::save_parameter(const QString &parameter_file_name)
{
    model->save_to_file(parameter_file_name);
}


QString ParameterViewer::get_cell_name()
{
    QString cell_name;
    for (int row = 0; row < model->rowCount(); ++row) {
        QString param_name = model->item(row, 0)->text();
        if (param_name == "cell_name") {
            QModelIndex index = model->index(row, 1);
            cell_name = model->data(index, Qt::EditRole).toString();
        }
    }

    return cell_name;
}

QString ParameterViewer::get_drug_name()
{
    QString drug_name;
    for (int row = 0; row < model->rowCount(); ++row) {
        QString param_name = model->item(row, 0)->text();
        if (param_name == "drug_name") {
            QModelIndex index = model->index(row, 1);
            drug_name = model->data(index, Qt::EditRole).toString();
        }
    }

    return drug_name;
}

QString ParameterViewer::get_user_name()
{
    QString user_name;
    for (int row = 0; row < model->rowCount(); ++row) {
        QString param_name = model->item(row, 0)->text();
        if (param_name == "user_name") {
            QModelIndex index = model->index(row, 1);
            user_name = model->data(index, Qt::EditRole).toString();
        }
    }

    return user_name;
}

int ParameterViewer::get_sample_size()
{
    QString original_current_dir(QDir::currentPath());
    QDir::setCurrent(cmlgui::directory::DEFAULT_SIMULATION_ROOT);
    qDebug() << QDir::currentPath();

    QString file_name;
    for (int row = 0; row < model->rowCount(); ++row) {
        QString param_name = model->item(row, 0)->text();
        if (param_name == "hill_file") {
            QModelIndex index = model->index(row, 1);
            file_name = model->data(index, Qt::EditRole).toString();
        }
    }

    qDebug() << "FILE FROM TABLE: " << file_name;
    qDebug() << QDir::currentPath();
    QFile hill_file(file_name);
    if (!hill_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return -1;  // Return -1 if the file couldn't be opened
    }

    int line_count = 0;
       QTextStream in(&hill_file);
       in.readLine(); // skip the header
       while (!in.atEnd()) {
           in.readLine();  // Read a line
           line_count++;    // Increment the counter
       }

    hill_file.close();
    QDir::setCurrent(original_current_dir);
    qDebug() << QDir::currentPath();
    return line_count;
}
