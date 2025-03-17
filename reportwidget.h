#ifndef REPORTWIDGET_H
#define REPORTWIDGET_H

#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QVBoxLayout>
#include <QWidget>

#include "browsewidget.h"
class ReportWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ReportWidget(QWidget *parent = nullptr);
    QString get_result_directory();
    QString get_latex_file();
    QString get_data_size();
private:
    BrowseWidget    *browse_result_dir;
    BrowseWidget    *browse_latex;
    QFormLayout     *layout_data_size_input;
    QHBoxLayout     *layout_base;
    QLineEdit       *edit_data_size;
    QLabel          *label_data_size_prompt;
    QVBoxLayout     *layout_input;
signals:

private slots:

};

#endif // REPORTWIDGET_H
