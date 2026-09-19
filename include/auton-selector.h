/* Helps prevent header files from being included multiple times*/
#pragma once

class autonSelector {

    private:
        static int autonNumber;
        static int totalAutons;

    public:
        autonSelector(int startingAuton, int numAutons);
        static int getSelectedAuton();
        void chooseAuton();
};





