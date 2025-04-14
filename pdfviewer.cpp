#include "pdfviewer.h"

#include "guiconstants.h"

PdfViewer::PdfViewer(QWidget *parent) : QDialog(parent)
{
    setWindowTitle(cmlgui::text::window::WINDOW_PDF_VIEWER);
    resize(cmlgui::size::WINDOW_PDF_WIDTH, cmlgui::size::WINDOW_PDF_HEIGHT);

    pdf_doc = new QPdfDocument(this);

    pdf_view = new QPdfView(this);
    pdf_view->setDocument(pdf_doc);
    pdf_view->setPageMode(QPdfView::PageMode::MultiPage);

    scroll_area = new QScrollArea();
    scroll_area->setWidgetResizable(true);
    scroll_area->setWidget(pdf_view);

    layout_base = new QVBoxLayout();
    layout_base->addWidget(scroll_area);
    setLayout(layout_base);
}

void PdfViewer::load_pdf(QString pdf_name)
{
    if(!pdf_name.isEmpty()){
        pdf_doc->load(pdf_name);
    }
}
