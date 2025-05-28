#ifndef PDFVIEWER_H
#define PDFVIEWER_H

#include <QDialog>
#include <QPdfDocument>
#include <QPdfView>
#include <QScrollArea>
#include <QString>
#include <QVBoxLayout>

class PdfViewer : public QDialog
{
    Q_OBJECT
public:
    PdfViewer(QWidget *parent = nullptr);
    void load_pdf(QString pdf_name);
private:
    QPdfDocument    *pdf_doc;
    QPdfView        *pdf_view;
    QScrollArea     *scroll_area;
    QVBoxLayout     *layout_base;
};

#endif // PDFVIEWER_H
