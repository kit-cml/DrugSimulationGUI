#include "reportwidget.h"

#include "guiconstants.h"

ReportWidget::ReportWidget(QWidget *parent)
    : QWidget{parent}
{
    // set the base layout of the widget.
    layout_base = new QHBoxLayout();
    this->setLayout(layout_base);

    layout_input = new QVBoxLayout();
    browse_result_dir = new BrowseWidget(this, cmlgui::text::label::LABEL_PROMPT_SIMULATION_RESULT_REPORT(), cmlgui::text::label::DIALOG_TITLE_SIMULATION_RESULT(), false);
    browse_latex = new BrowseWidget(this, cmlgui::text::label::LABEL_PROMPT_LATEX_REPORT(), cmlgui::text::label::DIALOG_TITLE_LATEX(),true,cmlgui::text::label::FILE_FORMAT_LATEX());
    layout_data_size_input = new QFormLayout();
    label_data_size_prompt = new QLabel(cmlgui::text::label::LABEL_PROMPT_SIZE_REPORT());
    edit_data_size = new QLineEdit();
    layout_data_size_input->addRow(label_data_size_prompt, edit_data_size);
    layout_input->addWidget(browse_result_dir);
    layout_input->addLayout(layout_data_size_input);
    layout_input->addWidget(browse_latex);


    layout_base->addLayout(layout_input);
}

QString ReportWidget::get_result_directory()
{
    return browse_result_dir->get_file_path();
}

QString ReportWidget::get_latex_file()
{
    return browse_latex->get_file_path();
}

QString ReportWidget::get_data_size()
{
    return edit_data_size->text();
}
