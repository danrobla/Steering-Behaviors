#ifndef INITIALDIALOG_H
#define INITIALDIALOG_H

#include <QDialog>

namespace Ui {
class InitialDialog;
}

class InitialDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InitialDialog(QWidget *parent = 0);
    ~InitialDialog();

private slots:
    void toggleAgentMode();

private:
    Ui::InitialDialog *ui;
};

#endif // INITIALDIALOG_H
