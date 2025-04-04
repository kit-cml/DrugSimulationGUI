#include "centralwidget.h"

#include "guiconstants.h"

#include <functional>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QOverload>

CentralWidget::CentralWidget(QWidget *parent)
    : QWidget{parent}
{
    initialize_process();

    // set the base layout of the widget.
    layout_base = new QVBoxLayout();
    this->setLayout(layout_base);

    setup_layout_viewer();
    setup_layout_logging();
    layout_base->addLayout(layout_viewer);
    layout_base->addLayout(layout_logging);
}

void CentralWidget::setup_layout_viewer()
{
    layout_viewer = new QVBoxLayout();
    viewer_inputdeck = new ParameterViewer();
    load_parameter();
    layout_viewer->addWidget(viewer_inputdeck);
}

void CentralWidget::load_parameter()
{
    // set the default cell model as ord.
    simulation_directory = cmlgui::directory::ORD_CVODE_DIRECTORY;
    QString param_file_name = cmlgui::directory::DEFAULT_SIMULATION_ROOT+"/"+simulation_directory+"/"+cmlgui::file::OUTPUT_PARAM_FILE;
    viewer_inputdeck->load_parameter(param_file_name);
}

void CentralWidget::append_text_color(const QString &text, const QString &color)
{
    edit_logging->append(QString("<span style='color:%1;'>%2</span>").arg(color, text.toHtmlEscaped().replace("\n", "<br>")));
}

void CentralWidget::setup_layout_logging()
{
    layout_button = new QHBoxLayout();
    layout_logging = new QVBoxLayout();
    button_execute = new QPushButton(cmlgui::text::button::BUTTON_EXECUTE_TEXT);
    connect(button_execute, &QPushButton::clicked, this, &CentralWidget::execute_simulation);
    button_report_generate = new QPushButton(cmlgui::text::button::BUTTON_GENERATE_REPORT_TEXT);
    connect(button_report_generate, &QPushButton::clicked, this, &CentralWidget::execute_report_generate);
    button_save_logs = new QPushButton(cmlgui::text::button::BUTTON_SAVE_LOGS_TEXT);
    connect(button_save_logs, &QPushButton::clicked, this, &CentralWidget::save_logs);

    //button_report_generate->setEnabled(false);
    button_save_logs->setEnabled(false);

    layout_button->addWidget(button_execute);
    layout_button->addWidget(button_report_generate);

    edit_logging = new QTextEdit();
    edit_logging->setReadOnly(true);

    viewer_report_preview = new PdfViewer();

    layout_logging = new QVBoxLayout();
    layout_logging->addLayout(layout_button);
    layout_logging->addWidget(edit_logging);
    layout_logging->addWidget(button_save_logs);

}

void CentralWidget::initialize_process()
{
    process_console = new QProcess();
    event_console = new QEventLoop();
    connect(process_console,
            QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            event_console, &QEventLoop::quit);
    connect(process_console, &QProcess::readyReadStandardOutput, this, &CentralWidget::handle_output_message);
    connect(process_console, &QProcess::readyReadStandardError, this, &CentralWidget::handle_error_message);
    connect(process_console, &QProcess::finished, this, &CentralWidget::handle_process_finished);


}


void CentralWidget::save_logs()
{
    QString file_path = QFileDialog::getSaveFileName(this->parentWidget(), cmlgui::text::window::WINDOW_SAVE_LOGS_TITLE,
                                                     cmlgui::directory::DEFAULT_SIMULATION_ROOT, cmlgui::text::fileformat::FILE_FORMAT_ANY);
    if (file_path.isEmpty()) {
        return; // User canceled the dialog
    }

    QFile logfile(file_path);
    if (logfile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&logfile);
        out << edit_logging->toPlainText(); // Save as plain text (no HTML)
        logfile.close();
    } else {
        QMessageBox::critical(nullptr, cmlgui::text::window::WINDOW_POPUP_ERROR_TITLE, cmlgui::text::message::ERROR_CANNOT_SAVE_LOG);
    }
}

void CentralWidget::execute_simulation()
{
    // prepare some GUI components when simulation started.
    edit_logging->clear();
    button_execute->setEnabled(false);
    button_report_generate->setEnabled(false);
    button_save_logs->setEnabled(false);

    simulation_directory = viewer_inputdeck->get_simulation_directory();

    // save the input into the parameter file.
    QString param_file_name = cmlgui::directory::DEFAULT_SIMULATION_ROOT+"/"+simulation_directory+"/"+cmlgui::file::OUTPUT_PARAM_FILE;
    viewer_inputdeck->save_parameter(param_file_name);
    edit_logging->append("Save the parameter file at " + param_file_name);
    // execute the simulation script.

    QString script_file(cmlgui::directory::DEFAULT_SIMULATION_ROOT+"/"+simulation_directory+"/"+cmlgui::file::EXECUTABLE_SCRIPT_FILE);
    //QString script_file(cmlgui::directory::DEFAULT_SIMULATION_ROOT+"/"+simulation_directory+"/"+cmlgui::file::EXECUTABLE_SCRIPT_DUMMY_FILE);
    QStringList program_args;
    program_args << script_file;
    execute_process(cmlgui::program::PROGRAM_BASH,program_args);
}

void CentralWidget::execute_process(QString program_name, QStringList program_args)
{
    QString original_current_dir(QDir::currentPath());
    QDir::setCurrent(cmlgui::directory::DEFAULT_SIMULATION_ROOT+"/"+simulation_directory);
    qDebug() << QDir::currentPath();
    process_console->start(program_name, program_args);
    // to make sure the process after this executed after the QProcess finished the task.
    event_console->exec();
    QDir::setCurrent(original_current_dir);
    qDebug() << QDir::currentPath();
}

void CentralWidget::execute_report_generate()
{
    button_execute->setEnabled(false);
    button_report_generate->setEnabled(false);
    button_save_logs->setEnabled(false);

    simulation_directory = viewer_inputdeck->get_simulation_directory();

    QString cell_name = viewer_inputdeck->get_cell_name();
    QString drug_name = viewer_inputdeck->get_drug_name();
    QString user_name = viewer_inputdeck->get_user_name();
    int sample_size = viewer_inputdeck->get_sample_size();
    // the format of the result_directory always ends with '/' character.
    // Otherwise, the report generating script will got some problems.
    // Need something to do to revise it. (TODO)
    QString result_directory = "result/"+drug_name+"/";
    QString report_latex_file = "report_drug_" + drug_name + "_" + cell_name + "_" + user_name + ".tex";
    QString report_pdf_file = "report_drug_" + drug_name + "_" + cell_name + "_" + user_name + ".pdf";

    QString script_file(cmlgui::directory::DEFAULT_SIMULATION_ROOT+"/"+simulation_directory+"/"+cmlgui::file::REPORT_GENERATOR_SCRIPT_FILE);
    QStringList program_args;
    program_args << script_file << result_directory << QString::number(sample_size) << user_name  << report_latex_file;
    qDebug() << program_args;
    execute_process(cmlgui::program::PROGRAM_BASH,program_args);

    viewer_report_preview->load_pdf(cmlgui::directory::DEFAULT_SIMULATION_ROOT+"/"+simulation_directory+"/"+report_pdf_file);
    viewer_report_preview->exec();

}

void CentralWidget::handle_output_message()
{
    QByteArray output = process_console->readAllStandardOutput();
    append_text_color(QString(output));
}

void CentralWidget::handle_error_message()
{
    QByteArray error = process_console->readAllStandardError();
    append_text_color("ERROR: \n" + QString(error), "red");
}

void CentralWidget::handle_process_finished(int exit_code, QProcess::ExitStatus status)
{
    if(status == QProcess::NormalExit && exit_code == 0){
        QMessageBox::information(nullptr, cmlgui::text::window::WINDOW_POPUP_INFORMATION_TITLE, cmlgui::text::message::INFO_SIMULATION_FINISHED);
    }
    else{
        QMessageBox::critical(nullptr, cmlgui::text::window::WINDOW_POPUP_ERROR_TITLE, cmlgui::text::message::ERROR_SIMULATION_FAILED);
    }
    button_execute->setEnabled(true);
    button_report_generate->setEnabled(true);
    button_save_logs->setEnabled(true);
}
