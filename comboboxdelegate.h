#ifndef COMBOBOXDELEGATE_H
#define COMBOBOXDELEGATE_H

#include <QMap>
#include <QString>
#include <QStyledItemDelegate>

class ComboBoxDelegate : public QStyledItemDelegate
{
public:
    explicit ComboBoxDelegate(const QMap<QString, QString> &items, QObject *parent = nullptr);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
private:
    QMap<QString, QString> combo_items; // Key (displayed) -> Value (stored)
    QMap<QString, QString> reverse_map; // Value (stored) -> Key (displayed)
};

#endif // COMBOBOXDELEGATE_H
