#ifndef IMAGEFOOTPRINTCALCULATOR_H
#define IMAGEFOOTPRINTCALCULATOR_H

#include <QtCore/QObject>
#include <QMatrix4x4>
#include <QVector3D>
#include <QtMath>
#include <QGeoCoordinate>
#include <qvariant.h>

class ImageFootprintCalculator : public QObject
{
    Q_OBJECT

public:
    explicit ImageFootprintCalculator (QObject *parent = nullptr);
    Q_INVOKABLE QVariantList calculateImageFootprint(const QGeoCoordinate &location,double altitude,
                                                     double pitch, double roll, double yaw,
                                                     double horizontalFov, double verticalFov);

    Q_INVOKABLE QVariantList calculateImageFootprint2(const QGeoCoordinate &location,double altitude,
                                                     double pitch, double roll, double yaw,
                                                     double horizontalFov, double verticalFov);
};

#endif
