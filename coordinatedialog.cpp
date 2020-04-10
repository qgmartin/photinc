#include <QtGui>

#include "coordinatedialog.h"
#include <iostream>
#include <math.h>

coordinateDialog::coordinateDialog(QWidget *parent)
    : QDialog(parent)
{
    //Creating GUI
    cartesianRadio = new QRadioButton(tr("&Cartesian"));
    polarRadio = new QRadioButton(tr("&Polar"));
    sphericalRadio = new QRadioButton(tr("&Spherical"));

    cartesianRadio->setCheckable(true);
    polarRadio->setCheckable(true);
    sphericalRadio->setCheckable(true);

    cartesianRadio->setChecked(false);
    polarRadio->setChecked(false);
    sphericalRadio->setChecked(true);

    coordinateTypeLayout = new QHBoxLayout();
    coordinateTypeLayout->addWidget(cartesianRadio);
    coordinateTypeLayout->addWidget(polarRadio);
    coordinateTypeLayout->addWidget(sphericalRadio);

    latitudeLongitudeRepresentation = new QCheckBox(tr("Use latitude - longitude notation"));
    latitudeLongitudeRepresentation->setDisabled(true);
    nonSphericalEarth = new QCheckBox(tr("Consider Earth as perfect sphere"));
    nonSphericalEarth->setChecked(true);
    nonSphericalEarth->setDisabled(true);

    dataRepresentationLayout = new QVBoxLayout();
    dataRepresentationLayout->addWidget(latitudeLongitudeRepresentation);
    dataRepresentationLayout->addWidget(nonSphericalEarth);

    firstCoordinate = new QDoubleSpinBox();
    firstCoordinate->setDecimals(4);
    secondCoordinate = new QDoubleSpinBox();
    secondCoordinate->setDecimals(4);
    sateliteFirstCoordinate = new QDoubleSpinBox();
    sateliteFirstCoordinate->setDecimals(4);
    sateliteSecondCoordinate = new QDoubleSpinBox();
    sateliteSecondCoordinate->setDecimals(4);

    identifyFirstCoordinate = new QLabel(tr("Point Latitude:"));
    identifySecondCoordinate = new QLabel(tr("Point Longitude:"));
    projectedFirstCoordinate = new QLabel(tr("Satelite Latitude:"));
    projectedSecondCoordinate = new QLabel(tr("Satelite Longitude:"));

    latitudeLayout = new QVBoxLayout();
    latitudeLayout->addWidget(identifyFirstCoordinate);
    latitudeLayout->addWidget(firstCoordinate);
    latitudeLayout->addWidget(projectedFirstCoordinate);
    latitudeLayout->addWidget(sateliteFirstCoordinate);

    longitudeLayout = new QVBoxLayout();
    longitudeLayout->addWidget(identifySecondCoordinate);
    longitudeLayout->addWidget(secondCoordinate);
    longitudeLayout->addWidget(projectedSecondCoordinate);
    longitudeLayout->addWidget(sateliteSecondCoordinate);

    coordinateInputLayout = new QHBoxLayout();
    coordinateInputLayout->addLayout(latitudeLayout);
    coordinateInputLayout->addLayout(longitudeLayout);

    identifySatelite = new QLabel(tr("Satelite:"));
    sateliteBox = new QComboBox();
    sateliteBox->addItem(tr("ISS"));
    sateliteBox->addItem(tr("Other..."));

    identifyAltitude = new QLabel(tr("Altitude (in m):"));
    sateliteAltidude = new QLineEdit();
    distance = tr("395000");
    sateliteAltidude->setText(distance);
    sateliteAltidude->setEnabled(false);
    distanceValidator = new QDoubleValidator(0, 100000000000, 2);
    sateliteAltidude->setValidator(distanceValidator);

    acceptButton = new QPushButton(tr("Calculate"));
    acceptButton->autoDefault();
    result = new QLineEdit();
    result->setReadOnly(true);

    sateliteInfoLayout = new QVBoxLayout();
    sateliteInfoLayout->addWidget(identifySatelite);
    sateliteInfoLayout->addWidget(identifyAltitude);
    sateliteInfoLayout->addWidget(acceptButton);

    sateliteSpecificationLayout = new QVBoxLayout();
    sateliteSpecificationLayout->addWidget(sateliteBox);
    sateliteSpecificationLayout->addWidget(sateliteAltidude);
    sateliteSpecificationLayout->addWidget(result);

    middleHorizontalBottomLayout = new QHBoxLayout();
    middleHorizontalBottomLayout->addLayout(sateliteInfoLayout);
    middleHorizontalBottomLayout->addLayout(sateliteSpecificationLayout);

    cancelButton = new QPushButton(tr("Cancel"));
    saveButton = new QPushButton(tr("Save"));
    aboutButton = new QPushButton(tr("About..."));

    buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(aboutButton);
    buttonLayout->addWidget(cancelButton);

    comments = new QLineEdit();
    comments->setPlaceholderText(tr("Observations..."));

    mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(coordinateTypeLayout);
    mainLayout->addLayout(dataRepresentationLayout);
    mainLayout->addLayout(coordinateInputLayout);
    mainLayout->addLayout(middleHorizontalBottomLayout);
    mainLayout->addWidget(comments);
    mainLayout->addLayout(buttonLayout);

    setTabOrder(firstCoordinate, secondCoordinate);
    setTabOrder(secondCoordinate, sateliteFirstCoordinate);
    setTabOrder(sateliteFirstCoordinate, sateliteSecondCoordinate);

    connect(cartesianRadio, SIGNAL(toggled(bool)), this, SLOT(whatCoordinate()));
    connect(polarRadio, SIGNAL(toggled(bool)), this, SLOT(whatCoordinate()));
    connect(sphericalRadio, SIGNAL(toggled(bool)), this, SLOT(whatCoordinate()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(sateliteBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(setDistance(QString)));
    connect(acceptButton, SIGNAL(clicked()), this, SLOT(calculateInclination()));
    connect(sateliteAltidude, SIGNAL(textChanged(QString)), this, SLOT(setDistance(QString)));
    connect(saveButton, SIGNAL(clicked()), this, SLOT(save()));
    connect(aboutButton, SIGNAL(clicked()), this, SLOT(aboutPhotInc()));

    curFile = tr("data.txt");

    whatCoordinate();
    setFixedSize(sizeHint());
    setWindowTitle(tr("PhotInc"));
    setWindowIcon(QIcon(":/images/earth.png"));
}

coordinateDialog::~coordinateDialog()
{

}

void coordinateDialog::whatCoordinate()
{
    if (cartesianRadio->isChecked())
    {
        firstCoordinate->setRange(-10000, 10000);
        secondCoordinate->setRange(-10000, 10000);
        sateliteFirstCoordinate->setRange(-10000, 10000);
        sateliteSecondCoordinate->setRange(-10000, 10000);
        identifyFirstCoordinate->setText(tr("Point x (in m):"));
        identifySecondCoordinate->setText(tr("Point y (in m):"));
        projectedFirstCoordinate->setText(tr("Satelite x (in m):"));
        projectedSecondCoordinate->setText(tr("Satelite y (in m):"));
        latitudeLongitudeRepresentation->setDisabled(true);
    }
    else if (polarRadio->isChecked())
    {
        firstCoordinate->setRange(0, 10000);
        secondCoordinate->setRange(-179.9999, 180);
        sateliteFirstCoordinate->setRange(0, 10000);
        sateliteSecondCoordinate->setRange(-179.9999, 180);
        identifyFirstCoordinate->setText(tr("Point r (in m):"));
        identifySecondCoordinate->setText(tr("Point %1:").arg(theta));
        projectedFirstCoordinate->setText(tr("Satelite r (in m):"));
        projectedSecondCoordinate->setText(tr("Satelite %1:").arg(theta));
        latitudeLongitudeRepresentation->setDisabled(true);
    }
    else if (sphericalRadio->isChecked())
    {
        firstCoordinate->setRange(-90, 90);
        secondCoordinate->setRange(-179.9999, 180);
        sateliteFirstCoordinate->setRange(-90, 90);
        sateliteSecondCoordinate->setRange(-179.9999, 180);
        identifyFirstCoordinate->setText(tr("Point Latitude:"));
        identifySecondCoordinate->setText(tr("Point Longitude:"));
        projectedFirstCoordinate->setText(tr("Satelite Latitude:"));
        projectedSecondCoordinate->setText(tr("Satelite Longitude:"));
        latitudeLongitudeRepresentation->setDisabled(true);
    }
    clearCoordiantes();
}

void coordinateDialog::clearCoordiantes()
{
    firstCoordinate->clear();
    secondCoordinate->clear();
    sateliteFirstCoordinate->clear();
    sateliteSecondCoordinate->clear();
    result->clear();
}

void coordinateDialog::setDistance(QString satelite)
{
    bool ok = false;
    if (satelite == "ISS")
    {
        sateliteAltidude->clear();
        distance = tr("395000");
        sateliteAltidude->setText(distance);
        sateliteAltidude->setEnabled(false);
    }
    else
    {
        ok = true;
        sateliteAltidude->setEnabled(true);
        distance = sateliteAltidude->text();
    }
    sateliteBox->setEditable(ok);
}

double coordinateDialog::calculateEarthRadius(double latitude)
{
    //When Earth is nos a sphere we suppose a linear variation on radius as a function of latitude
    return 2 * (EARTH_POLAR_RADIUS - EARTH_ECUATORIAL_RADIUS) / PI * abs(latitude) + EARTH_ECUATORIAL_RADIUS;
}

void coordinateDialog::calculateInclination()
{
    double inclinationInRad = 0;
    double inclinationInDeg = 0;
    double maxInclination = asin(EARTH_MEAN_RADIUS / (EARTH_MEAN_RADIUS + distance.toDouble()));
    double maxInclinationArc = PI - PI / 2 - maxInclination;

    if (cartesianRadio->isChecked())
    {
        double straightDistance = sqrt(pow((sateliteFirstCoordinate->text().toDouble() - firstCoordinate->text().toDouble()), 2) +
                               pow((sateliteSecondCoordinate->text().toDouble() - secondCoordinate->text().toDouble()), 2));
        inclinationInRad = atan(straightDistance / sateliteAltidude->text().toDouble());
        inclinationInDeg = inclinationInRad / RADIAN;
    }
    else if (polarRadio->isChecked())
    {
        double angleDifferenceInDeg = sateliteSecondCoordinate->text().toDouble() - secondCoordinate->text().toDouble();
        double straightDistance = sqrt(pow(sateliteFirstCoordinate->text().toDouble(), 2) + pow(firstCoordinate->text().toDouble(), 2) -
                                       2 * sateliteFirstCoordinate->text().toDouble() * firstCoordinate->text().toDouble() * cos(angleDifferenceInDeg * RADIAN));
        inclinationInRad = atan(straightDistance / sateliteAltidude->text().toDouble());
        inclinationInDeg = inclinationInRad / RADIAN;
    }
    else if (sphericalRadio->isChecked())
    {
        double haversinLatitude = pow(sin((sateliteFirstCoordinate->text().toDouble() - firstCoordinate->text().toDouble()) * RADIAN / 2), 2);
        double haversinLongitude = pow(sin((sateliteSecondCoordinate->text().toDouble() - secondCoordinate->text().toDouble()) * RADIAN / 2), 2);
        double haversinProduct = cos(sateliteFirstCoordinate->text().toDouble() * RADIAN) * cos(firstCoordinate->text().toDouble() * RADIAN);
        double haversinRoot = sqrt(haversinLatitude + haversinProduct * haversinLongitude);
        double distanceArcAngle = 2 * asin(haversinRoot);

        if (maxInclinationArc <= distanceArcAngle)
        {
            result->setText(tr("Not visible"));
            result->setStyleSheet("color : red");
            return;
        }
        else
        {
            double antiProjectionRadiusOverArc = sin(distanceArcAngle);
            double complementProjectionRadiusOverArc = 1 - cos(distanceArcAngle);
            double straightDistance = sqrt(pow(antiProjectionRadiusOverArc, 2) + pow(complementProjectionRadiusOverArc, 2)) * EARTH_MEAN_RADIUS;

            double neededAngle = (PI - distanceArcAngle) / 2;
            double lastSide = sqrt(pow(straightDistance, 2) + pow(distance.toDouble(), 2) -
                                2 * straightDistance * distance.toDouble() * cos(neededAngle));
            inclinationInRad = asin(straightDistance * sin(neededAngle) / lastSide);
            inclinationInDeg = inclinationInRad / RADIAN;
        }
    }

    if (inclinationInRad >= 2 * maxInclination)
    {
        result->setText(tr("Out of range"));
        result->setStyleSheet("color : green");
    }
    else
    {
        result->setText(QString::number(inclinationInDeg));
        result->setStyleSheet("color : black");
    }
}

void coordinateDialog::save()
{
    bool ok = true;
    QString fileName = QInputDialog::getText(this, tr("PhotInc - Saving"), tr("Introduce name for file:"),
                                             QLineEdit::Normal, curFile, &ok);
    if (!fileName.isEmpty() && ok == true)
    {
        if (!fileName.contains(".txt"))
        {
            fileName.append(".txt");
            curFile = fileName;
        }
        writeData(curFile);
    }
}

void coordinateDialog::writeData(QString &fileName)
{
    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly | QFile::Append))
    {
        QMessageBox::warning(this, tr("PhotInc"), tr("Cannot write file %1:\n%2.")
                             .arg(file.fileName()).arg(file.errorString()));
    }
    else
    {
        QApplication::setOverrideCursor(Qt::WaitCursor);
        QTextStream out(&file);
        if (file.size() == 0)
        {
            out << tr("PhotInc v%1 data file.\n").arg(VERSION);
        }
        out << "\n" << QDate::currentDate().toString() << " at "
            << QTime::currentTime().toString() << "; Observations: " <<
               comments->text() << "\n";
        out << identifyFirstCoordinate->text() << " " << firstCoordinate->text() << ", ";
        out << identifySecondCoordinate->text() << " " << secondCoordinate->text() << "\n";
        out << projectedFirstCoordinate->text() << " " << sateliteFirstCoordinate->text() << ", ";
        out << projectedSecondCoordinate->text() << " " << sateliteSecondCoordinate->text() << "\n";
        out << tr("Inclination: ") << result->text() << ", for " << sateliteBox->currentText()
            << " at " << sateliteAltidude->text() << "m.\n";
        QApplication::restoreOverrideCursor();
    }
}

void coordinateDialog::aboutPhotInc()
{
    QMessageBox::about(this, tr("PhotInc"), tr("<h2>PhotInc %1, Guillermo Martin</h2>"
                                               "Splashscreen image\n courtesy of the Image Science & Analysis Laboratory "
                                               "NASA Johnson Space Center: http://eol.jsc.nasa.gov, ISS030-E-10008.").arg(VERSION));
}
