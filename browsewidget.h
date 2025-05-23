#ifndef BROWSEWIDGET_H
#define BROWSEWIDGET_H

#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QWidget>

#include "guiconstants.h"

class BrowseWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BrowseWidget(QWidget *parent = nullptr, const QString string_prompt = "Browse Prompt", const QString dialog_title = "Browse Title",
                          bool is_file = true, QString file_format = cmlgui::text::fileformat::FILE_FORMAT_ANY);
    QString get_file_path();
private:
    bool is_browse_file;
    QFormLayout *layout_base;
    QHBoxLayout *layout_browse;
    QLabel      *label_prompt;
    QLineEdit   *edit_file_dir;
    QPushButton *button_browse;
    QString     file_dialog_title;
    QString     file_format;
    signals:

private slots:
    void browse_file();
};

#endif // BROWSEWIDGET_H
