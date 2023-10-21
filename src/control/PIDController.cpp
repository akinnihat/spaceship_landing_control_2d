#include "PIDController.h"

PIDController::PIDController(double Kp, double Ki, double Kd)
{
    m_Kp = Kp;
    m_Ki = Ki;
    m_Kd = Kd;
    m_Integral = 0;
    m_PreError = 0;
}

PIDController::~PIDController()
{

}

void PIDController::setPIDParameters(double Kp, double Ki, double Kd)
{
    m_Kp = Kp;
    m_Ki = Ki;
    m_Kd = Kd;
}

double PIDController::calculatePID(int error, double dt)
{
    double p_out = m_Kp * error;
    m_Integral += error * dt;
    double i_out = m_Ki * m_Integral;
    double d_out = m_Kd * ((error - m_PreError) / dt);

    m_PreError = error;
    return p_out + i_out + d_out;
}