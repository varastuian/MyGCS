#include "ImageFootprintCalculator.h"
#include <QMatrix4x4>
#include <QVector3D>
#include <QtMath>
ImageFootprintCalculator::ImageFootprintCalculator(QObject *parent): QObject(parent){}

QVariantList ImageFootprintCalculator::calculateImageFootprint(const QGeoCoordinate &location,double altitude, double pitch, double roll, double yaw, double horizontalFov, double verticalFov)
{

    if (altitude <= 2.0) {
        return {};
    }
    QList<QGeoCoordinate> footprint;

    // Field of View half-angles
    double hFovHalf = qDegreesToRadians(horizontalFov / 2.0);
    double vFovHalf = qDegreesToRadians(verticalFov / 2.0);

    // Rotation matrix for pitch, roll, yaw
    QMatrix4x4 rotation;
    rotation.rotate(pitch, 1, 0, 0); // Pitch
    rotation.rotate(roll , 0, 1, 0);  // Roll
    rotation.rotate(yaw  , 0, 0, 1);   // Yaw

    // Corners of the image in local camera space
    QVector3D corners[4] = {
        QVector3D(altitude * qTan(-hFovHalf), altitude * qTan(-vFovHalf), -altitude),
        QVector3D(altitude * qTan(hFovHalf), altitude * qTan(-vFovHalf), -altitude),
        QVector3D(altitude * qTan(hFovHalf), altitude * qTan(vFovHalf), -altitude),
        QVector3D(altitude * qTan(-hFovHalf), altitude * qTan(vFovHalf), -altitude),
    };

    // Transform corners to world space and project to ground
    for (int i = 0; i < 4; ++i) {
        QVector3D worldCorner = rotation.map(corners[i]);
        double groundX = worldCorner.x() / -worldCorner.z() * altitude;
        double groundY = worldCorner.y() / -worldCorner.z() * altitude;

        // Convert local ground X, Y to latitude and longitude
        double earthRadius = 6378137.0; // Earth radius in meters
        double dLat = groundY / earthRadius;
        double dLon = groundX / (earthRadius * qCos(qDegreesToRadians(location.latitude())));

        footprint.append(QGeoCoordinate(
            location.latitude() + qRadiansToDegrees(dLat),
            location.longitude() + qRadiansToDegrees(dLon)
            ));
    }

    QVariantList result;
    for (const QGeoCoordinate &coord : footprint) {
        result.append(QVariant::fromValue(coord));
    }
    result.append(QVariant::fromValue(result[0]));
    // qDebug() << result;
    return result;
}

QVariantList ImageFootprintCalculator::calculateImageFootprint2(const QGeoCoordinate &location,double altitude, double pitch, double roll, double yaw, double horizontalFov, double verticalFov)
{

    if (altitude <= 2.0) {
        return {};
    }
    QList<QGeoCoordinate> footprint;

    // Field of View half-angles
    double hFovHalf = qDegreesToRadians(horizontalFov / 2.0);
    double vFovHalf = qDegreesToRadians(verticalFov / 2.0);

    // Rotation matrix for pitch, roll, yaw
    QMatrix4x4 rotation;
    // rotation.rotate(pitch, 1, 0, 0); // Pitch
    // rotation.rotate(roll , 0, 1, 0);  // Roll
    // rotation.rotate(yaw  , 0, 0, 1);   // Yaw

    rotation.rotate(roll , 1, 0, 0);  // Roll
    rotation.rotate(pitch, 1, 0, 0); // Pitch
    rotation.rotate(yaw  , 0, 0, 1);   // Yaw
    // Corners of the image in local camera space
    QVector3D corners[4] = {
        // QVector3D(altitude * qTan(-hFovHalf), altitude * qTan(-vFovHalf), -altitude),
        // QVector3D(altitude * qTan(hFovHalf), altitude * qTan(-vFovHalf), -altitude),
        // QVector3D(altitude * qTan(hFovHalf), altitude * qTan(vFovHalf), -altitude),
        // QVector3D(altitude * qTan(-hFovHalf), altitude * qTan(vFovHalf), -altitude),

        QVector3D(altitude * qTan(-hFovHalf), altitude * qTan(vFovHalf), -altitude),
        QVector3D(altitude * qTan(hFovHalf), altitude * qTan(vFovHalf), -altitude),
        QVector3D(altitude * qTan(hFovHalf), altitude * qTan(-vFovHalf), -altitude),
        QVector3D(altitude * qTan(-hFovHalf), altitude * qTan(-vFovHalf), -altitude),
    };

    // Transform corners to world space and project to ground
    for (int i = 0; i < 4; ++i) {
        QVector3D worldCorner = rotation.map(corners[i]);
        double groundX = worldCorner.x() / -worldCorner.z() * altitude;
        double groundY = worldCorner.y() / -worldCorner.z() * altitude;

        // Convert local ground X, Y to latitude and longitude
        double earthRadius = 6378137.0; // Earth radius in meters
        double dLat = groundY / earthRadius;
        double dLon = groundX / (earthRadius * qCos(qDegreesToRadians(location.latitude())));

        footprint.append(QGeoCoordinate(
            location.latitude() + qRadiansToDegrees(dLat),
            location.longitude() + qRadiansToDegrees(dLon)
            ));
    }

    QVariantList result;
    for (const QGeoCoordinate &coord : footprint) {
        result.append(QVariant::fromValue(coord));
    }
    result.append(QVariant::fromValue(result[0]));
    // qDebug() << result;
    return result;
}
