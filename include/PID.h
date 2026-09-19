/* Helps prevent header files from being included multiple times*/
#pragma once

class PID {

    private:
        double error = 0;
        double kP = 0;
        double kI = 0;
        double kD = 0;
        double integral = 0;
        double derivative = 0;
        double prevError = 0;
        double windupThreshold = 12;
        double total = 0;
        double tolerance = 0;
        double updateTime = 10;
    
    public:
        PID(double startError, double kp, double ki, double kd);
        PID(double startError, double kp, double ki, double kd, double Tolerance);
        PID(double startError, double kp, double ki, double kd, double Tolerance, double WindupTheshold, double UpdateTime);

        double calculateTotal(double currentError);

        double getUpdateTime();
};




