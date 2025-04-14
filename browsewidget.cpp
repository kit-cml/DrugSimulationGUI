#include "browsewidget.h"

#include "guiconstants.h"

#include <QFileDialog>
#include <QString>

BrowseWidget::BrowseWidget(QWidget *parent, const QString string_prompt, const QString dialog_title, bool is_file, QString file_format)
    : QWidget{parent}, file_dialog_title(dialog_title), is_browse_file(is_file), file_format(file_format)
{
    // set the base layout of the widget.
    layout_base = new QFormLayout();
    this->setLayout(layout_base);

    button_browse = new QPushButton(cmlgui::text::button::BUTTON_BROWSE_TEXT);
    connect(button_browse, &QPushButton::clicked, this, &BrowseWidget::browse_file);
    edit_file_dir = new QLineEdit("");
    edit_file_dir->setReadOnly(true);
    label_prompt = new QLabel(string_prompt);

    layout_browse = new QHBoxLayout();
    layout_browse->addWidget(edit_file_dir);
    layout_browse->addWidget(button_browse);
    layout_base->addRow(label_prompt, layout_browse);
}

QString BrowseWidget::get_file_path()
{
    return edit_file_dir->text();
}

void BrowseWidget::browse_file()
{
    if(is_browse_file == true){
        QString file_path = QFileDialog::getOpenFileName(this->parentWidget(), file_dialog_title,
                                                         cmlgui::directory::DEFAULT_SIMULATION_ROOT, file_format) ;
        if (!file_path.isEmpty()) {
            edit_file_dir->setText(file_path);
        }
    }
    else{
        QString dir_path = QFileDialog::getExistingDirectory(this->parentWidget(), file_dialog_title,
                                                         cmlgui::directory::DEFAULT_SIMULATION_ROOT) ;
        if (!dir_path.isEmpty()) {
            edit_file_dir->setText(dir_path);
        }
    }
}
