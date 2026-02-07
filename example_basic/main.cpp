#include <iostream>
#include <iomanip>
#include "metacar/metacar.hpp"

int main() {
    metacar::SceneAPI api;

    std::cout << "Waiting for simulator connection...\n";
    api.connect();
    std::cout << "Connected!\n";

    while (auto msg = api.step()) {
        const auto& pose = msg->pose_gnss;
        double speed = msg->main_vehicle.speed;

        std::cout << std::fixed << std::setprecision(2)
                  << "pos=(" << pose.pos_x << ", " << pose.pos_y << ", " << pose.pos_z << ")  "
                  << "speed=" << speed << " m/s\n";

        metacar::VehicleControl ctrl;
        ctrl.throttle = 0.1;
        ctrl.gear     = metacar::GearMode::DRIVE;
        api.set_vehicle_control(ctrl);
    }

    std::cout << "Simulation ended.\n";
    return 0;
}
