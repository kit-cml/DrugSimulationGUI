#ifndef FILEBROWSERDELEGATE_H
#define FILEBROWSERDELEGATE_H

#include <QFileDialog>
#include <QPushButton>
#include <QStyledItemDelegate>


// Custom delegate for file browser
class FileBrowserDelegate : public QStyledItemDelegate {
public:
    FileBrowserDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &) const override {
        QPushButton *button = new QPushButton("Browse", parent);
        connect(button, &QPushButton::clicked, [this, button, parent]() {
            QString filePath = QFileDialog::getOpenFileName(parent, "Select File");
            if (!filePath.isEmpty()) {
                emit fileSelected(filePath);
            }
        });

        return button;
    }

    void setEditorData(QWidget *editor, const QModelIndex &index) const override {
        QPushButton *button = qobject_cast<QPushButton *>(editor);
        if (button) {
            button->setProperty("filePath", index.data(Qt::EditRole).toString());
        }
    }

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override {
        QPushButton *button = qobject_cast<QPushButton *>(editor);
        if (button) {
            QString filePath = button->property("filePath").toString();
            model->setData(index, filePath, Qt::EditRole);
        }
    }

signals:
    void fileSelected(const QString &filePath) const{

    }
};
#endif // FILEBROWSERDELEGATE_H
