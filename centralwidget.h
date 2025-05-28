#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QComboBox>
#include <QEventLoop>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPlainTextEdit>
#include <QProcess>
#include <QPushButton>
#include <QRadioButton>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QWidget>

#include "parameterviewer.h"
#include "pdfviewer.h"

class CentralWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CentralWidget(QWidget *parent = nullptr);
private:
    // parts for parameter table view.
    // will be put at the middle.
    ParameterViewer     *viewer_inputdeck;
    QVBoxLayout         *layout_viewer;
    void setup_layout_viewer();
    void load_parameter();
    // parts for the selection between CPU and GPU simulation.
    QFormLayout         *layout_cpu_gpu_selection;
    QLabel              *label_cpu_gpu_mode;
    QHBoxLayout         *layout_radio;
    QHBoxLayout         *layout_processor;
    QRadioButton        *radio_cpu;
    QRadioButton        *radio_gpu;
    QLabel              *label_processor_size;
    QSpinBox            *spinbox_processor_size;
    void setup_cpu_gpu_selection();
    // parts for the button and logging.
    // will be put at the lower part.
    QTextEdit           *edit_logging;
    QPushButton         *button_execute;
    QPushButton         *button_report_generate;
    QPushButton         *button_save_logs;
    QHBoxLayout         *layout_button;
    QVBoxLayout         *layout_logging;
    PdfViewer           *viewer_report_preview;
    void append_text_color(const QString &text, const QString &color);
    void setup_layout_logging();
    // base layout that contains all of the layouts.
    QVBoxLayout         *layout_base;
    // additional components that is not a GUI components.
    QProcess            *process_console;
    QEventLoop              *event_console;
    void initialize_process();
    void execute_process(QString program_name, QStringList program_args);
    QString             simulation_directory;

private slots:
    void save_logs();
    void execute_simulation();
    void execute_report_generate();
    void handle_output_message();
    void handle_error_message();
    void handle_process_finished(int exit_code, QProcess::ExitStatus status);
};

#endif // CENTRALWIDGET_H
