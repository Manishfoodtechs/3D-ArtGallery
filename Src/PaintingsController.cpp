#include "PaintingsController.h"

PaintingsController::PaintingsController()
{
    INTERPOLATION_MIN   = 0 ;
    INTERPOLATION_MAX   = 100;

    interpolVarHangingAnimation  = new QPropertyAnimation(this, "interpolVarHanging");
    interpolVarFallingAnimation  = new QPropertyAnimation(this, "interpolVarFalling");

    QObject::connect(this, SIGNAL(interpolVarHangingChanged(float)), this, SLOT(updatePaintingHangAngle()));
    QObject::connect(this, SIGNAL(interpolVarFallingChanged(float)), this, SLOT(updatePaintingFallAngle()));

    interpolVarHangingAnimation->setKeyValueAt(0,INTERPOLATION_MIN);
    interpolVarHangingAnimation->setKeyValueAt(.5,INTERPOLATION_MAX);
    interpolVarHangingAnimation->setKeyValueAt(1,INTERPOLATION_MIN);
    //interpolationVariableAnimation->setLoopCount(-1);
    interpolVarHangingAnimation->setEasingCurve(QEasingCurve::OutElastic);
    interpolVarHangingAnimation->setDuration(5000);

    interpolVarFallingAnimation->setKeyValueAt(0,INTERPOLATION_MIN);
    interpolVarFallingAnimation->setKeyValueAt(1,INTERPOLATION_MAX);
    interpolVarFallingAnimation->setEasingCurve(QEasingCurve::OutBounce);
    interpolVarFallingAnimation->setDuration(2000);
}

void PaintingsController::startPaintingHangingMotion()
{
    interpolVarHangingAnimation->stop();
    interpolVarHangingAnimation->start();
}

void PaintingsController::startPaintingFallingMotion()
{
    interpolVarFallingAnimation->stop();
    interpolVarFallingAnimation->start();
}

void PaintingsController::updatePaintingHangAngle()
{
    Factory::paintingTransformList[4]->setRotationTo( ((130-90)*m_interpolVarHanging)/100 + 90  ,Factory::paintingTransformList[4]->getRotationY(), Factory::paintingTransformList[4]->getRotationZ() );
}

void PaintingsController::updatePaintingFallAngle()
{
    Factory::paintingTransformList[3]->setRotationTo( Factory::paintingTransformList[3]->getRotationX(), ((90)*m_interpolVarFalling)/100 + 0 , Factory::paintingTransformList[3]->getRotationZ() );
    Factory::paintingTransformList[3]->setTranslationTo( ((30-45)*m_interpolVarFalling)/100 + 45 ,((-23)*m_interpolVarFalling)/100, Factory::paintingTransformList[3]->getTranslationZ() );
}
