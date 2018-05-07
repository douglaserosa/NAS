#include <iostream>
#include <string>
#include <fstream>

class Mobile {
private:
    int capacity;
    int charge_full_design;
    std::string charge_type;
    int charging_enabled;
    int current_now;
    int ext_pwr;
    std::string health;
    int present;
    std::string status;
    std::string technology;
    int temp;
    std::string type;
    std::string uevent;
    int voltage_max_design;
    int voltage_min_design;
    int voltage_now;
    std::string basePath = "/sys/class/power_supply/battery/";
public:
    int getCapacity();
    int getChargeFullDesign();
    std::string getChargeType();
    int getChargingEnabled();
    int getCurrentNow();
    int getExtPwr();
    std::string getHealth();
    int getPresent();
    std::string getStatus();
    std::string getTechnology();
    int getTemp();
    std::string getType();
    std::string getUevent();
    int getVoltageMaxDesign();
    int getVoltageMinDesign();
    int getVoltageNow();
};

int Mobile::getCapacity() {
    std::string line;
    std::ifstream myfile( basePath + "capacity");
    if (myfile.is_open())
    {
        getline (myfile,line);
        Mobile::capacity = std::stoi(line);
        myfile.close();
    }
    else
    {
        std::cout << "Unable to open " + basePath + "capacity\n";
        return 100;
    }
    return Mobile::capacity;
}

std::string Mobile::getChargeType() {
    std::string line;
    std::ifstream myfile( basePath + "charge_type");
    if (myfile.is_open())
    {
        getline (myfile,line);
        Mobile::charge_type = line;
        myfile.close();
    }
    else
    {
        std::cout << "Unable to open " + basePath + "charge_type\n";
        return "";
    }
    return Mobile::charge_type;
}

int Mobile::getChargeFullDesign() {
    std::string line;
    std::ifstream myfile( basePath + "charge_full_design");
    if (myfile.is_open())
    {
        getline (myfile,line);
        Mobile::charge_full_design = std::stoi(line);
        myfile.close();
    }
    else
    {
        std::cout << "Unable to open " + basePath + "charge_full_design\n";
        return 1000;
    }
    return Mobile::capacity;
}

int Mobile::getChargingEnabled() {
    std::string line;
    std::ifstream myfile( basePath + "charging_enabled");
    if (myfile.is_open())
    {
        getline (myfile,line);
        Mobile::charging_enabled = std::stoi(line);
        myfile.close();
    }
    else
    {
        std::cout << "Unable to open " + basePath + "charging_enabled\n";
        return 1;
    }
    return Mobile::charging_enabled;
}

int Mobile::getCurrentNow() {
    std::string line;
    std::ifstream myfile(basePath + "current_now");
    if (myfile.is_open())
    {
        getline (myfile,line);
        Mobile::current_now = std::stoi(line);
        myfile.close();
    }
    else
    {
        std::cout << "Unable to open " + basePath + "current_now\n";
        return 0;
    }
    return Mobile::current_now;
}

int Mobile::getExtPwr() {
    std::string line;
    std::ifstream myfile(basePath + "ext_pwr");
    if (myfile.is_open())
    {
        getline (myfile,line);
        Mobile::ext_pwr = std::stoi(line);
        myfile.close();
    }
    else
    {
        std::cout << "Unable to open " + basePath + "ext_pwr\n";
        return 0;
    }
    return Mobile::ext_pwr;
}

std::string Mobile::getHealth() {
    std::string line;
    std::ifstream myfile( basePath + "health");
    if (myfile.is_open())
    {
        getline (myfile,line);
        Mobile::health = line;
        myfile.close();
    }
    else
    {
        std::cout << "Unable to open " + basePath + "health\n";
        return "";
    }
    return Mobile::health;
}

int Mobile::getPresent() {
    std::string line;
    std::ifstream myfile(basePath + "present");
    if (myfile.is_open())
    {
        getline (myfile,line);
        Mobile::present = std::stoi(line);
        myfile.close();
    }
    else
    {
        std::cout << "Unable to open " + basePath + "present\n";
        return 0;
    }
    return Mobile::present;
}

std::string Mobile::getStatus() {
    std::string line;
    std::ifstream myfile( basePath + "status");
    if (myfile.is_open())
    {
        getline (myfile,line);
        Mobile::status = line;
        myfile.close();
    }
    else
    {
        std::cout << "Unable to open " + basePath + "status\n";
        return "";
    }
    return Mobile::status;
}

std::string Mobile::getTechnology() {
    std::string line;
    std::ifstream myfile( basePath + "technology");
    if (myfile.is_open())
    {
        getline (myfile,line);
        Mobile::technology = line;
        myfile.close();
    }
    else
    {
        std::cout << "Unable to open " + basePath + "technology\n";
        return "";
    }
    return Mobile::technology;
}

int Mobile::getTemp() {
    std::string line;
    std::ifstream myfile(basePath + "temp");
    if (myfile.is_open())
    {
        getline (myfile,line);
        Mobile::temp = std::stoi(line);
        myfile.close();
    }
    else
    {
        std::cout << "Unable to open " + basePath + "temp\n";
        return 0;
    }
    return Mobile::temp;
}

std::string Mobile::getType() {
    std::string line;
    std::ifstream myfile( basePath + "type");
    if (myfile.is_open())
    {
        getline (myfile,line);
        Mobile::type = line;
        myfile.close();
    }
    else
    {
        std::cout << "Unable to open " + basePath + "type\n";
        return "";
    }
    return Mobile::type;
}

std::string Mobile::getUevent() {
    std::string line;
    Mobile::uevent = "";
    std::ifstream myfile( basePath + "uevent");
    if (myfile.is_open())
    {
        while (getline (myfile,line)) {
            Mobile::uevent += line + "\n";
        }
        myfile.close();
    }
    else
    {
        std::cout << "Unable to open " + basePath + "uevent\n";
        return "";
    }
    return Mobile::uevent;
}

int Mobile::getVoltageMaxDesign() {
    std::string line;
    std::ifstream myfile(basePath + "voltage_max_design");
    if (myfile.is_open())
    {
        getline (myfile,line);
        Mobile::voltage_max_design = std::stoi(line);
        myfile.close();
    }
    else
    {
        std::cout << "Unable to open " + basePath + "voltage_max_design\n";
        return 0;
    }
    return Mobile::voltage_max_design;
}

int Mobile::getVoltageMinDesign() {
    std::string line;
    std::ifstream myfile(basePath + "voltage_min_design");
    if (myfile.is_open())
    {
        getline (myfile,line);
        Mobile::voltage_min_design = std::stoi(line);
        myfile.close();
    }
    else
    {
        std::cout << "Unable to open " + basePath + "voltage_min_design\n";
        return 0;
    }
    return Mobile::voltage_min_design;
}

int Mobile::getVoltageNow() {
    std::string line;
    std::ifstream myfile(basePath + "voltage_now");
    if (myfile.is_open())
    {
        getline (myfile,line);
        Mobile::voltage_now = std::stoi(line);
        myfile.close();
    }
    else
    {
        std::cout << "Unable to open " + basePath + "voltage_now\n";
        return 0;
    }
    return Mobile::voltage_now;
}