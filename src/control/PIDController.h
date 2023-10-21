#ifndef PID_CONTROLLER_HEADER_FILE
#define PID_CONTROLLER_HEADER_FILE

class PIDController
{
private:
    double m_Kp;
    double m_Ki;
    double m_Kd;
    double m_Integral{0};
    int m_PreError{0};

public:
    PIDController(double Kp = 0.01, double Ki = 0.01, double Kd = 0.01);
    ~PIDController();
    void setPIDParameters(double Kp, double Ki, double Kd);
    double calculatePID(int error, double dt);
};

#endif