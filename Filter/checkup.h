#ifndef CHECKUP_H
#define CHECKUP_H


#include <QDialog>
#include <QSqlQuery>

QT_BEGIN_NAMESPACE
class QDialog;
class QComboBox;
class QGroupBox;
class QGridLayout;
class QHBoxLayout;
class QFrame;
class QDialogButtonBox;
class QPushButton;
class QLabel;
class QLineEdit;
class QDateTime;
class QDateEdit;
class QTableView;
class QSqlQueryModel;
QT_END_NAMESPACE

class Checkup : public QDialog
{
    Q_OBJECT

public:
    Checkup(QWidget *parent = nullptr);

private slots:

    void save();
    void cancel();
    void edit();
    void erase();
    void refresh();

private:
    void createTableGroupBox();
    void createInputGroupBox();
    void createButtonBox();

    int employeeId;
    int editableId;
    bool isEditable;

    QSqlQuery query;

    QGroupBox* tableGroupBox;
    QFrame* dateFrame;
    QHBoxLayout* dateLayout;
    QLabel* labelStartDate;
    QTableView* tableView;
    QSqlQueryModel* model;
    QDateEdit* startDate;

    QGroupBox* inputGroupBox;
    QSqlQueryModel* employeeModel;
    QComboBox* employeeComboBox;
    QLineEdit* content;

    QDialogButtonBox* buttonBox;
    QPushButton* saveButton;
    QPushButton* cancelButton;
    QPushButton* closeButton;
    QPushButton* deleteButton;

    QGridLayout* mainLayout;
    QGridLayout* tableLayout;
    QGridLayout* inputLayout;

};

#endif //CHECKUP_H
