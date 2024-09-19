    #include"computer.h"
    Computer::Computer() : id(-1), isInUse(false) {}

    Computer::Computer(int id) : id(id), isInUse(false), pricePerHour(0) {}

    Computer::~Computer() {};

    int Computer::getId() { return id; }

    bool Computer::getIsUse() { return isInUse; }

    float Computer::getCost() { return pricePerHour; }

    void Computer::startUsage() { isInUse = true; }

    void Computer::endUsage(){ isInUse = false;}