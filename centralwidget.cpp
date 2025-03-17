#include "centralwidget.h"

#include "guiconstants.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QMessageBox>

CentralWidget::CentralWidget(QWidget *parent)
    : QWidget{parent}
{
    initialize_process();

    // set the base layout of the widget.
    layout_base = new QVBoxLayout();
    this->setLayout(layout_base);

    setup_layout_upper();
    setup_layout_middle();
    setup_layout_lower();

    layout_base->addLayout(layout_upper_button);
    layout_base->addLayout(layout_middle_cellmodel);
    layout_base->addLayout(layout_middle_filebrowser);
    layout_base->addLayout(layout_middle_input);
    layout_base->addLayout(layout_lower_report);
}

void CentralWidget::initialize_process()
{
    process_simulator = new QProcess(this);
    connect(process_simulator, &QProcess::readyReadStandardOutput, this, &CentralWidget::handle_output_message);
    connect(process_simulator, &QProcess::readyReadStandardError, this, &CentralWidget::handle_error_message);
    connect(process_simulator, &QProcess::finished, this, &CentralWidget::handle_process_finished);

}

void CentralWidget::handle_output_message()
{
    QByteArray output = process_simulator->readAllStandardOutput();
    edit_logging->appendPlainText(QString(output));
}

void CentralWidget::handle_error_message()
{
    QByteArray error = process_simulator->readAllStandardError();
    edit_logging->appendPlainText("ERROR: \n" + QString(error));
}

void CentralWidget::handle_process_finished(int exit_code, QProcess::ExitStatus status)
{
    if(status == QProcess::NormalExit){
        QMessageBox::information(nullptr, cmlgui::text::label::LABEL_INFORMATION(), cmlgui::text::message::INFO_SIMULATION_FINISHED());
    }
    else{
        QMessageBox::critical(nullptr, cmlgui::text::label::LABEL_ERROR(), cmlgui::text::message::ERROR_SIMULATION_FAILED());
    }
    button_execute->setEnabled(true);
}

void CentralWidget::execute_simulation()
{
    edit_logging->clear();
    button_execute->setEnabled(false);
    create_parameter_file();
    if( browse_herg->get_file_path().size() <= 0 || browse_ic50->get_file_path().size() <= 0 ){
        QMessageBox::warning(nullptr, cmlgui::text::label::LABEL_WARNING(), cmlgui::text::message::WARNNG_NO_IC50_HERG_FILE_PATH());
        button_execute->setEnabled(true);
        return;
    }
    execute_script();
}

void CentralWidget::execute_script()
{
    QString script_file(cmlgui::directory::DEFAULT_SIMULATION_DIRECTORY+"/"+simulation_directory+"/"+cmlgui::file::EXECUTABLE_SCRIPT_FILE);
    QString original_current_dir(QDir::currentPath());
    QDir::setCurrent(cmlgui::directory::DEFAULT_SIMULATION_DIRECTORY+"/"+simulation_directory);
    qDebug() << QDir::currentPath();
    process_simulator->start("/bin/bash", QStringList() << script_file);
    process_simulator->waitForFinished();
    QDir::setCurrent(original_current_dir);
    qDebug() << QDir::currentPath();
}

void CentralWidget::execute_generate_report()
{
    edit_logging->clear();
    if(combo_cellmodel->currentData().toString() == "ord"){
        simulation_directory = cmlgui::directory::ORD_DIRECTORY;
    }
    else if(combo_cellmodel->currentData().toString() == "ordstatic"){
        simulation_directory = cmlgui::directory::ORDSTATIC_DIRECTORY;
    }
    else if(combo_cellmodel->currentData().toString() == "tomek"){
        simulation_directory = cmlgui::directory::TOMEK_DIRECTORY;
    }
    QString script_file(cmlgui::directory::DEFAULT_SIMULATION_DIRECTORY+"/"+simulation_directory+"/"+cmlgui::file::REPORT_GENERATOR_SCRIPT_FILE);
    QString original_current_dir(QDir::currentPath());
    QDir::setCurrent(cmlgui::directory::DEFAULT_SIMULATION_DIRECTORY+"/"+simulation_directory);
    qDebug() << QDir::currentPath();
    QStringList script_args;
    script_args << script_file<< report_generator->get_result_directory().section('/', -2, -1, QString::SectionSkipEmpty)
                << report_generator->get_data_size()
                << QFileInfo(report_generator->get_latex_file()).fileName();
    qDebug() << script_args;
    process_simulator->start("/bin/bash", script_args);
    process_simulator->waitForFinished();
    QDir::setCurrent(original_current_dir);
    qDebug() << QDir::currentPath();
}

void CentralWidget::populate_parameter()
{
    // take pre-defined input parameter to the edit_inputdeck object.
    QFile file_inputdeck(cmlgui::directory::DEFAULT_SIMULATION_DIRECTORY+"/"+ cmlgui::directory::ORD_DIRECTORY+"/"+cmlgui::file::INPUT_PARAM_FILE);
    if (!file_inputdeck.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "Cannot open file: " + file_inputdeck.errorString());
        return;
    }
    QTextStream in(&file_inputdeck);
    QString content;
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (!line.startsWith("hill_file") && !line.startsWith("herg_file") && !line.startsWith("cell_name")) {
            content += line + "\n";
        }
    }
    file_inputdeck.close();

    edit_inputdeck->setPlainText(content);  // Load file content into QTextEdit
}

void CentralWidget::setup_layout_upper()
{
    layout_upper_button = new QHBoxLayout();
    button_execute = new QPushButton(cmlgui::text::label::EXECUTE_TEXT());
    connect(button_execute, &QPushButton::clicked, this, &CentralWidget::execute_simulation);
    layout_upper_button->addWidget(button_execute);
}

void CentralWidget::setup_layout_middle()
{

    layout_middle_cellmodel = new QHBoxLayout();
    label_cellmodel = new QLabel(cmlgui::text::label::LABEL_PROMPT_CELLMODEL());
    combo_cellmodel = new QComboBox();
    // Populate the combo box
    for (auto it = cmlgui::text::label::MAP_CELL_MODEL.begin(); it != cmlgui::text::label::MAP_CELL_MODEL.end(); ++it) {
        combo_cellmodel->addItem(it.key(), it.value());
    }
    layout_middle_cellmodel->addWidget(label_cellmodel);
    layout_middle_cellmodel->addWidget(combo_cellmodel);

    layout_middle_filebrowser = new QVBoxLayout();
    browse_ic50 = new BrowseWidget(this, cmlgui::text::label::LABEL_PROMPT_IC50(), cmlgui::text::label::DIALOG_TITLE_IC50());
    browse_herg = new BrowseWidget(this, cmlgui::text::label::LABEL_PROMPT_HERG(), cmlgui::text::label::DIALOG_TITLE_HERG());
    layout_middle_filebrowser->addWidget(browse_herg);
    layout_middle_filebrowser->addWidget(browse_ic50);

    layout_middle_input = new QVBoxLayout();
    edit_inputdeck = new QPlainTextEdit();
    populate_parameter();
    edit_logging = new QPlainTextEdit();
    edit_logging->setReadOnly(true);
    layout_middle_input->addWidget(edit_inputdeck);
    layout_middle_input->addWidget(edit_logging);
}

void CentralWidget::setup_layout_lower()
{
    layout_lower_report = new QHBoxLayout();
    report_generator = new ReportWidget();
    button_generate_report = new QPushButton("Generate");
    connect(button_generate_report, &QPushButton::clicked, this, &CentralWidget::execute_generate_report);

    layout_lower_report->addWidget(report_generator);
    layout_lower_report->addWidget(button_generate_report);
}

void CentralWidget::create_parameter_file()
{
    if(combo_cellmodel->currentData().toString() == "ord"){
        simulation_directory = cmlgui::directory::ORD_DIRECTORY;
    }
    else if(combo_cellmodel->currentData().toString() == "ordstatic"){
        simulation_directory = cmlgui::directory::ORDSTATIC_DIRECTORY;
    }
    else if(combo_cellmodel->currentData().toString() == "tomek"){
        simulation_directory = cmlgui::directory::TOMEK_DIRECTORY;
    }

    QString output_file(cmlgui::directory::DEFAULT_SIMULATION_DIRECTORY+"/"+simulation_directory+"/"+cmlgui::file::OUTPUT_PARAM_FILE);
    QFile file(output_file);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << edit_inputdeck->toPlainText();  // Preserves newlines
        out << "cell_name = " << combo_cellmodel->currentData().toString() << "\n";
        out << "hill_file = ./" << browse_ic50->get_file_path().section('/', -3, -1, QString::SectionSkipEmpty) << "\n";
        out << "herg_file = ./" << browse_herg->get_file_path().section('/', -3, -1, QString::SectionSkipEmpty) << "\n";
        file.close();
    }
}
