#include "comboboxdelegate.h"

#include <QComboBox>

ComboBoxDelegate::ComboBoxDelegate(const QMap<QString, QString> &items, QObject *parent)
    : QStyledItemDelegate(parent), combo_items(items)
{
    // Reverse map: value -> key for lookup
    for (auto it = combo_items.begin(); it != combo_items.end(); ++it) {
        reverse_map[it.value()] = it.key();
    }
}

QWidget *ComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &) const
{
    QComboBox *editor = new QComboBox(parent);
    editor->addItems(combo_items.keys()); // Display keys in combo box
    return editor;
}

void ComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QComboBox *combo_editor = static_cast<QComboBox *>(editor);
    QString stored_value = index.data().toString(); // Get stored value from the model

    if (reverse_map.contains(stored_value)) {
        int item_index = combo_editor->findText(reverse_map[stored_value]);
        if (item_index != -1) {
            combo_editor->setCurrentIndex(item_index);
        }
    }
}

void ComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *combo_editor = static_cast<QComboBox *>(editor);
    QString selected_key = combo_editor->currentText(); // Get displayed key
    QString stored_value = combo_items[selected_key]; // Get actual stored value

    model->setData(index, stored_value, Qt::EditRole); // Store value, not key
}

void ComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const
{
    editor->setGeometry(option.rect);
}
