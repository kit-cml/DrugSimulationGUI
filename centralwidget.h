#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QComboBox>
#include <QWidget>
#include <QHBoxLayout>
#include <QPlainTextEdit>
#include <QProcess>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include "browsewidget.h"
#include "reportwidget.h"

class CentralWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CentralWidget(QWidget *parent = nullptr);
private:
    BrowseWidget        *browse_ic50;
    BrowseWidget        *browse_herg;
    QComboBox           *combo_cellmodel;
    QLabel              *label_cellmodel;
    QHBoxLayout         *layout_middle_cellmodel;
    QHBoxLayout         *layout_upper_button;
    QHBoxLayout         *layout_lower_report;
    QPlainTextEdit      *edit_inputdeck;
    QPlainTextEdit      *edit_logging;
    QProcess            *process_simulator;
    QPushButton         *button_execute;
    QPushButton         *button_generate_report;
    QString             simulation_directory;
    QVBoxLayout         *layout_base;
    QVBoxLayout         *layout_middle_filebrowser;
    QVBoxLayout         *layout_middle_input;
    ReportWidget        *report_generator;
    void create_parameter_file();
    void initialize_process();
    void populate_parameter();
    void setup_layout_upper();
    void setup_layout_middle();
    void setup_layout_lower();
private slots:
    void execute_generate_report();
    void execute_simulation();
    void execute_script();
    void handle_output_message();
    void handle_error_message();
    void handle_process_finished(int exit_code, QProcess::ExitStatus status);

};

#endif // CENTRALWIDGET_H
