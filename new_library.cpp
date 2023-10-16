#include "new_library.h"
#include "ui_new_library.h"

New_library::New_library(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::New_library)
{
    ui->setupUi(this);
}

New_library::~New_library()
{
    delete ui;
}

void New_library::on_save_button_clicked()
{
    input_text = ui->library_name_input->toPlainText();
    this->hide();
}

QString New_library::get_input_text() const
{
    return input_text;
}


void New_library::on_cancel_button_clicked()
{
    this->hide();
}

