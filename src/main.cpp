#include "metacar/metacar.hpp"
#include <iomanip>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

int main() {
#ifdef _WIN32
  SetConsoleOutputCP(CP_UTF8);
#endif

  metacar::SceneAPI api;

  std::cout << "等待仿真器连接...\n";
  api.connect();
  std::cout << "已连接!\n";

  // 获取静态数据
  const auto &static_data = api.get_scene_static_data();
  std::cout << "路线点数量: " << static_data.route.size() << "\n";

  while (auto result = api.step()) {
    auto &[msg, frames] = *result;
    const auto &pose = msg.pose_gnss;
    double speed = msg.main_vehicle.speed;

    std::cout << std::fixed << std::setprecision(2) << "位置=(" << pose.pos_x << ", " << pose.pos_y
              << ", " << pose.pos_z << ")  "
              << "速度=" << speed << " m/s\n";

    metacar::VehicleControl ctrl;
    ctrl.throttle = 0.1;
    ctrl.gear = metacar::GearMode::DRIVE;
    api.set_vehicle_control(ctrl);
  }

  std::cout << "仿真结束。\n";
  return 0;
}
