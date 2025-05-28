#include "parametermodel.h"

#include <QFile>
#include <QMessageBox>

#include "guiconstants.h"

ParameterModel::ParameterModel(QObject *parent)
    : QStandardItemModel{parent}
{
    setColumnCount(2);
    setHeaderData(0, Qt::Horizontal, "Parameter");
    setHeaderData(1, Qt::Horizontal, "Value");
}

void ParameterModel::load_from_file(const QString &parameter_file_name)
{
    QFile param_file(parameter_file_name);
    if (!param_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(nullptr, cmlgui::text::window::WINDOW_POPUP_ERROR_TITLE, cmlgui::text::message::ERROR_PARAMETER_FAILED);
        return;
    }

    QTextStream text_reader(&param_file);
    while (!text_reader.atEnd()) {
        QString line = text_reader.readLine().trimmed();
        if (line.isEmpty()) continue;

        // split the actual parameter data with the comment.
        QStringList parts = line.split("//", Qt::KeepEmptyParts);
        QString data_part = parts[0].trimmed();
        QString comment = (parts.size() > 1) ? parts[1].trimmed() : "";

        // split the parameter data into key-value pair
        QStringList key_value = data_part.split("=", Qt::SkipEmptyParts);
        if (key_value.size() < 2) continue;

        QString key = key_value[0].trimmed();
        QString value = key_value[1].trimmed();

        QList<QStandardItem *> row_items;
        QStandardItem *key_item = new QStandardItem(key);
        QStandardItem *value_item = new QStandardItem(value);

        if (!comment.isEmpty()) {
            key_item->setToolTip(comment);
            value_item->setToolTip(comment);
        }

        row_items << key_item << value_item;
        appendRow(row_items);

    }

    param_file.close();

}

void ParameterModel::save_to_file(const QString &parameter_file_name)
{
    QFile param_output_file(parameter_file_name);
    if (!param_output_file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }

    QTextStream out(&param_output_file);

    for (int row = 0; row < rowCount(); ++row) {
        QString key = item(row, 0)->text();
        QString value = item(row, 1)->text();
        QString comment = item(row, 0)->toolTip();  // Get the stored comment (tooltip)

        // Format: key = value // comment
        QString line = key + " = " + value;
        if (!comment.isEmpty()) {
            line += "  // " + comment;
        }
        out << line << "\n";
    }

    param_output_file.close();
}
