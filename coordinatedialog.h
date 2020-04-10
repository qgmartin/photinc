#ifndef COORDINATEDIALOG_H
#define COORDINATEDIALOG_H

#include <QDialog>

#define VERSION 1.6

const double EARTH_ECUATORIAL_RADIUS = 6378100;
const double EARTH_POLAR_RADIUS = 6356800;
const double EARTH_MEAN_RADIUS = 6371000;
const double PI = 3.141592;
const double RADIAN = 0.01745329;
const QChar lambda(0x3BB);
const QChar theta(0x03B8);

class QRadioButton;
class QLineEdit;
class QLabel;
class QPushButton;
class QVBoxLayout;
class QHBoxLayout;
class QComboBox;
class QCheckBox;
class QDoubleSpinBox;
class QRegExp;
class QDoubleValidator;

class coordinateDialog : public QDialog
{
    Q_OBJECT
    
public:
    coordinateDialog(QWidget *parent = 0);
    ~coordinateDialog();

private slots:
    void whatCoordinate();
    void setDistance(QString satelite);
    void calculateInclination();
    void save();
    void writeData(QString &fileName);
    void clearCoordiantes();
    void aboutPhotInc();

private:
    double calculateEarthRadius(double latitude);

    QRadioButton *cartesianRadio;
    QRadioButton *polarRadio;
    QRadioButton *sphericalRadio;

    QCheckBox *latitudeLongitudeRepresentation;
    QCheckBox *nonSphericalEarth;

    QDoubleSpinBox *firstCoordinate;
    QDoubleSpinBox *secondCoordinate;
    QDoubleSpinBox *sateliteFirstCoordinate;
    QDoubleSpinBox *sateliteSecondCoordinate;

    QLineEdit *sateliteAltidude;
    QLineEdit *result;

    QLabel *identifyFirstCoordinate;
    QLabel *identifySecondCoordinate;
    QLabel *projectedFirstCoordinate;
    QLabel *projectedSecondCoordinate;
    QLabel *identifySatelite;
    QLabel *identifyAltitude;

    QPushButton *acceptButton;
    QPushButton *saveButton;
    QPushButton *cancelButton;
    QPushButton *aboutButton;

    QComboBox *sateliteBox;

    QHBoxLayout *coordinateTypeLayout;
    QHBoxLayout *coordinateInputLayout;
    QHBoxLayout *middleHorizontalBottomLayout;
    QHBoxLayout *buttonLayout;

    QVBoxLayout *dataRepresentationLayout;
    QVBoxLayout *latitudeLayout;
    QVBoxLayout *longitudeLayout;
    QVBoxLayout *sateliteInfoLayout;
    QVBoxLayout *sateliteSpecificationLayout;
    QVBoxLayout *mainLayout;

    QString distance;

    QDoubleValidator *distanceValidator;
    QString curFile;
    QLineEdit *comments;
};

#endif // COORDINATEDIALOG_H
