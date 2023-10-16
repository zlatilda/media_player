#ifndef NEW_LIBRARY_H
#define NEW_LIBRARY_H

#include <QDialog>

namespace Ui {
class New_library;
}

class New_library : public QDialog
{
    Q_OBJECT

public:
    explicit New_library(QWidget *parent = nullptr);
    ~New_library();

    QString get_input_text() const;

private slots:
    void on_save_button_clicked();
    void on_cancel_button_clicked();

private:
    Ui::New_library *ui;
    QString input_text;
};

#endif // NEW_LIBRARY_H
