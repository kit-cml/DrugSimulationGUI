#ifndef GUICONSTANTS_H
#define GUICONSTANTS_H

#include <QDir>
#include <QMap>
#include <QString>
#include <QTranslator>

namespace cmlgui{

    namespace text{
        namespace label{
            inline const QString LABEL_PARAMETER_PROMPT_TEXT = "Assign the parameter file";
        }

        namespace button{
            inline const QString BUTTON_BROWSE_TEXT = "Browse...";
            inline const QString BUTTON_EXECUTE_TEXT = "Execute";
            inline const QString BUTTON_GENERATE_REPORT_TEXT = "Generate Report";
            inline const QString BUTTON_LOAD_PARAMETER_TEXT = "Load Parameter";
            inline const QString BUTTON_SAVE_LOGS_TEXT = "Save Logs";
        }

        namespace window{
            inline const QString WINDOW_MAIN_TITLE = "DrugSimulationGUI v.0.0.0";
            inline const QString WINDOW_BROWSE_HERG_TITLE = "Please select your hERG data file.";
            inline const QString WINDOW_BROWSE_IC50_TITLE = "Please select your IC50 data file.";
            inline const QString WINDOW_BROWSE_PARAMETER_TITLE = "Please select your parameter file.";
            inline const QString WINDOW_SAVE_LOGS_TITLE = "Save Logs As....";
            inline const QString WINDOW_PDF_VIEWER = "Report Preview";
            inline const QString WINDOW_POPUP_ERROR_TITLE = "Error";
            inline const QString WINDOW_POPUP_INFORMATION_TITLE = "Information";
            inline const QString WINDOW_POPUP_WARNING_TITLE = "Warning";
        }
        
        namespace combobox{
            inline const QMap<QString, QString> MAP_CELL_MODEL = {{"O'Hara-Rudy (Dutta) 2011", "ordstatic"},
                                                              {"O'Hara-Rudy IKr-dynamic 2017", "ord"},
                                                              {"Tomek et al. (ToR-ORd) 2019", "tomek"},
                                                              {"Tomek et al. with dynamic Chloride (ToR-ORd-dynCl) 2020","tomek_dyncl"}};
            inline const QMap<QString, QString> MAP_CELLTYPE = {{"Endo", "0"},
                                                              {"Epi", "1"},
                                                              {"Mid-myocardium", "2"}};
            inline const QMap<QString, QString> MAP_SOLVER = {{"Euler", "0"},
                                                              {"CVode", "1"}};
        }
        
        namespace fileformat{
            inline const QString FILE_FORMAT_ANY = "*";
            inline const QString FILE_FORMAT_IC50_HERG = "Comma-separated values files (*.csv)";
            inline const QString FILE_FORMAT_LATEX = "LaTEX files (*.tex)";
        }

        namespace message{
            inline const QString ERROR_SIMULATION_FAILED = "Simulation failed!";
            inline const QString ERROR_PARAMETER_FAILED = "The parameter file format is incorrect!";
            inline const QString ERROR_NO_PARAMETER = "The parameter file is empty. Make sure to load the parameter first!";
            inline const QString ERROR_CANNOT_SAVE_LOG = "This log cannot be saved! Contact the administrator!";
            inline const QString WARNNG_NO_IC50_HERG_FILE_PATH = "Make sure to provide the file path of both IC50 and hERG parameter data!!!";
            inline const QString WARNING_NO_PARAMETER_FILE = "Please provide parameter file!";
            inline const QString INFO_SIMULATION_FINISHED = "Simulation successfully finished!";
        }
        
    }

    namespace directory{
        // change this directory according to your console simulation located.
        inline const QString DEFAULT_SIMULATION_ROOT = "/home/iga/Documents/Code/Github/DrugSimulation/bin/simulation_dirs";
        inline const QString ORD_CVODE_DIRECTORY = "drugsim_ord_cvode";
        inline const QString ORDSTATIC_CVODE_DIRECTORY = "drugsim_ordstatic_cvode";
        inline const QString TOMEK_CVODE_DIRECTORY = "drugsim_tomek_cvode";
        inline const QString ORD_EULER_DIRECTORY = "drugsim_ord_euler";
        inline const QString ORDSTATIC_EULER_DIRECTORY = "drugsim_ordstatic_euler";
        inline const QString TOMEK_EULER_DIRECTORY = "drugsim_tomek_euler";
    }

    namespace file{
        inline const QString EXECUTABLE_SCRIPT_FILE  = "exec_bash_gui.sh";
        inline const QString EXECUTABLE_SCRIPT_DUMMY_FILE  = "exec_dummy.sh";
        inline const QString REPORT_GENERATOR_SCRIPT_FILE  = "generate_report.sh";
        inline const QString OUTPUT_PARAM_FILE  = "param.txt";
    }

    namespace program{
        inline const QString PROGRAM_BASH = "/bin/bash";
    }

    namespace size{
        inline constexpr int WINDOW_MAIN_HEIGHT =   1024;
        inline constexpr int WINDOW_MAIN_WIDTH  =   768;
        inline constexpr int WINDOW_PDF_HEIGHT =   740;
        inline constexpr int WINDOW_PDF_WIDTH  =   600;
    }
}
#endif // GUICONSTANTS_H
