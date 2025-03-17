#ifndef GUICONSTANTS_H
#define GUICONSTANTS_H

#include <QDir>
#include <QMap>
#include <QString>
#include <QTranslator>

namespace cmlgui{
    // every QString under this namespace should be encased with tr() function
    // for multi-language support.
    // QString should be a function returned as QString with tr()
    // since tr() needs QObject as the parent.
    namespace text{
        namespace label{
            inline const QString BROWSE_TEXT() {
                return QObject::tr("Browse");
            }
            inline const QString EXECUTE_TEXT() {
                return QObject::tr("Execute");
            }
            inline const QString DIALOG_TITLE_HERG() {
                return QObject::tr("Please select your hERG parameter file.");
            }
            inline const QString DIALOG_TITLE_IC50() {
                return QObject::tr("Please select your IC50 file.");
            }
            inline const QString DIALOG_TITLE_SIMULATION_RESULT() {
                return QObject::tr("Please select your simulation result directory.");
            }
            inline const QString DIALOG_TITLE_LATEX() {
                return QObject::tr("Please select your LaTEX file.");
            }
            inline const QString LABEL_PROMPT_HERG() {
                return QObject::tr("hERG Parameter");
            }
            inline const QString LABEL_PROMPT_IC50() {
                return QObject::tr("IC50 Data");
            }
            inline const QString LABEL_PROMPT_SIMULATION_RESULT_REPORT() {
                return QObject::tr("Simulation Folder");
            }
            inline const QString LABEL_PROMPT_LATEX_REPORT() {
                return QObject::tr("LaTEX File");
            }
            inline const QString LABEL_PROMPT_SIZE_REPORT() {
                return QObject::tr("Sample Size");
            }
            inline const QString FILE_FORMAT_IC50_HERG() {
                return QObject::tr("Comma-separated values files (*.csv)");
            }
            inline const QString FILE_FORMAT_LATEX() {
                return QObject::tr("LaTEX files (*.tex)");
            }
            inline const QString WINDOW_MAIN_TITLE() {
                return QObject::tr("DrugSimulationGUI v.0.0.0");
            }
            inline const QString LABEL_PROMPT_CELLMODEL() {
                return QObject::tr("Cellmodel");
            }
            inline const QString LABEL_WARNING() {
                return QObject::tr("Warning");
            }
            inline const QString LABEL_ERROR() {
                return QObject::tr("Error");
            }
            inline const QString LABEL_INFORMATION() {
                return QObject::tr("Information");
            }
            inline const QMap<QString, QString> MAP_CELL_MODEL = {{"O'Hara-Rudy (Dutta) 2011", "ordstatic"},
                                                                  {"O'Hara-Rudy IKr-dynamic 2017", "ord"},
                                                                  {"Tomek et al. (ToR-ORd) 2019", "tomek"},
                                                                  {"Tomek et al. with dynamic Chloride (ToR-ORd-dynCl) 2020","tomek_dyncl"}};
        }

        namespace message{
            inline const QString ERROR_SIMULATION_FAILED() {
                return QObject::tr("Simulation failed!");
            }
            inline const QString WARNNG_NO_IC50_HERG_FILE_PATH() {
                return QObject::tr("Make sure to provide the file path of both IC50 and hERG parameter data!!!");
            }
            inline const QString INFO_SIMULATION_FINISHED() {
                return QObject::tr("Simulation successfully finished!");
            }
        }
    }

    namespace directory{
        // change this directory according to your console simulation located.
        inline const QString DEFAULT_SIMULATION_DIRECTORY = "/home/iga/Documents/Code/Github/DrugSimulation/bin/simulation_dirs";
        inline const QString ORD_DIRECTORY = "drugsim_ord_cvode";
        inline const QString ORDSTATIC_DIRECTORY = "drugsim_ordstatic_cvode";
        inline const QString TOMEK_DIRECTORY = "drugsim_tomek_cvode";
    }

    namespace file{
        inline const QString EXECUTABLE_SCRIPT_FILE  = "exec_bash_gui.sh";
        inline const QString REPORT_GENERATOR_SCRIPT_FILE  = "generate_report.sh";
        inline const QString INPUT_PARAM_FILE   = "param.txt";
        inline const QString OUTPUT_PARAM_FILE  = "param.txt";
    }

    namespace size{
        inline constexpr int WINDOW_MAIN_HEIGHT =   1024;
        inline constexpr int WINDOW_MAIN_WIDTH  =   768;
    }
}
#endif // GUICONSTANTS_H
