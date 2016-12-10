#include "window.hpp"
#include <QStatusBar>
#include "filter.hpp"
#include "image.hpp"
#include <QHBoxLayout>
#include <QListWidget>
#include <QComboBox>
#include <QMessageBox>
#include <QFileDialog>
#include <QToolBar>
#include "view.hpp"

#include <QElapsedTimer>

Window::Window(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget* worksp = new QWidget;
    setCentralWidget(worksp);

    QHBoxLayout* lout = new QHBoxLayout(worksp);

    tView = new View;
    lout->addWidget(tView, 1);

    tList = new QListWidget;
    lout->addWidget(tList);
    //tList->setViewMode(QListWidget::IconMode);
    tList->setIconSize(QSize(100, 100));
    tList->setSelectionMode(QListWidget::SingleSelection);
    connect(tList, SIGNAL(currentRowChanged(int)),
            this, SLOT(setCurrent(int)));

    QToolBar* tbar = addToolBar("Tools");

    QAction* openAct = tbar->addAction(QIcon(":/open.png"), "Open image",
                                       this, SLOT(openImage()));

    QAction* saveAct = tbar->addAction(QIcon(":/save.png"), "Save result",
                                       this, SLOT(saveImage()));

    tbar->addSeparator();

    tScale = new QComboBox;
    tbar->addWidget(tScale);
    tScale->addItem("Fit view", 0);
    tScale->addItem("25%", 0.25);
    tScale->addItem("50%", 0.5);
    tScale->addItem("100%", 1);
    tScale->addItem("200%", 2);
    tScale->addItem("400%", 4);
    tScale->setCurrentIndex(0);
    connect(tScale, SIGNAL(currentIndexChanged(int)),
            this, SLOT(scaleImage(int)));

    tbar->addSeparator();

    QAction* doAct = tbar->addAction(QIcon(":/do.png"), "Process image",
                                     this, SLOT(processImage()));

    statusBar();
}

Window::~Window() {
    for (Image* i : tImgs)
        delete i;
}

void Window::openImage() {
    QString nameFilter = "Images (*.bmp *.png *.jpg *.jpeg)";
    QStringList fileNames = QFileDialog::getOpenFileNames(0, "Open image",
                                                    QString(), nameFilter);
    if (fileNames.isEmpty()) return;

    QStringList err;
    QListWidgetItem* it = 0;

    for (auto fileName : fileNames) {
        QPixmap src(fileName);
        if (src.isNull()) {
            err << fileName;
        }
        else {
            Image* img = new Image;
            tImgs << img;
            img->setImage(src);

            it = new QListWidgetItem(img->image(), QString(), tList);
            tList->addItem(it);
            it->setData(Qt::UserRole, QVariant::fromValue((void*)img));
        }
    }

    if (err.size() < fileNames.size()) {
        tList->setCurrentItem(it);
    }

    if (!err.isEmpty()) {
        QString msg("Cannot load some of the images:\n");
        msg += err.join("\n");
        QMessageBox::warning(0, "Error", msg);
    }
}

void Window::saveImage() {
    QString nameFilter = "Images (*.bmp *.png *.jpg *.jpeg)";
    QString fileName = QFileDialog::getSaveFileName(0, "Save result",
                                                    QString(), nameFilter);
    if (fileName.isEmpty()) return;

    if (!tView->currentImage().save(fileName)) {
        QString msg = QString("Cannot save image\n%1").arg(fileName);
        QMessageBox::critical(0, "Error", msg);
    }
}

void Window::processImage() {
    if (tList->count() == 0) return;

    struct Gauss {
        std::vector<float> mask;
        int radius;
        Gauss() {
            genGauss(1, mask, radius);
        }
    };
    static Gauss g;

    QElapsedTimer tm;
    tm.start();

    for (int i = 0, n = tList->count(); i < n; ++i) {
        void* vi = tList->item(i)->data(Qt::UserRole).value<void*>();
        Image* img = static_cast<Image*>(vi);
        int w = img->image().width();

        std::vector<float> procF;
        filterConv(img->imageF(), w, g.mask.data(), g.radius, procF);
        //filterSobel(img->imageF(), w, false, procF);

        img->setImage(procF, w);
    }

    qint64 t = tm.elapsed();
    statusBar()->showMessage(QString("%1 ms").arg(t));

    setCurrent(tList->currentRow());
}

void Window::scaleImage(int ix) {
    QVariant scaleVar = tScale->itemData(ix);
    if (!scaleVar.isValid()) return;
    double scale = scaleVar.toDouble();
    tView->setScale(scale);
}

void Window::setCurrent(int ix) {
    if (ix >= 0 && ix < tList->count()) {
        void* vi = tList->item(ix)->data(Qt::UserRole).value<void*>();
        Image* i = static_cast<Image*>(vi);
        setImage(i->image());
    }
}

void Window::resizeEvent(QResizeEvent *ev) {
    QMainWindow::resizeEvent(ev);
    if (tScale->currentIndex() == 0) {
        tView->setScale(0);
    }
}

void Window::setImage(const QPixmap &p) {
    tView->setImage(p);
    if (tScale->currentIndex() == 0) {
        tView->setScale(0);
    }
    else {
        tScale->setCurrentIndex(0);
    }
}
