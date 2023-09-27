#ifndef ABSTRACTLOGVIEW_H
#define ABSTRACTLOGVIEW_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QDialog;
class QComboBox;
class QGroupBox;
class QGridLayout;
class QHBoxLayout;
class QFrame;
class QDialogButtonBox;
class QPushButton;
class QLineEdit;
class QDateEdit;
class QTableView;
class AbstractLogModel;
class QLabel;
class QRadioButton;
QT_END_NAMESPACE


class AbstractLogView : public QDialog
{
    Q_OBJECT
public:
    AbstractLogView(QWidget *parent = nullptr);
    virtual ~AbstractLogView() {};
    void open();

protected slots:
    virtual void save()=0;
    void cancel();
    void edit();
    virtual void bring()=0;
    void erase();
    void refresh();
    void filterOnEmployee();

protected:
    void createTableGroupBox();
    virtual void createInputGroupBox()=0;
    void createButtonBox();

    int editableId;
    int employeeId;
    bool editable;

    QGroupBox* tableGroupBox;
    AbstractLogModel* model;
    QTableView* tableView;
    QFrame* dateFrame;
    QHBoxLayout* dateLayout;
    QLabel* labelStartDate;
    QDateEdit* startDate;
    QRadioButton* radioButtonEmpl;

    QGroupBox* inputGroupBox;
    QLineEdit* content;
    QComboBox* employeeComboBox;

    QDialogButtonBox* buttonBox;
    QPushButton* saveButton;
    QPushButton* cancelButton;
    QPushButton* closeButton;
    QPushButton* deleteButton;

    QGridLayout* mainLayout;
    QGridLayout* tableLayout;
    QGridLayout* inputLayout;

    QString title;

    int width=800, height=600;

    };

#endif // ABSTRACTLOGVIEW_H

