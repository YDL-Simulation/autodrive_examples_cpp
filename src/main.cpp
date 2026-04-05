#ifdef _WIN32
#define NOMINMAX
#endif

#include "metacar/metacar.hpp"
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <numbers>

#ifdef _WIN32
#include <windows.h>
#endif

constexpr double PI = std::numbers::pi;

// 目标速度 (m/s)
constexpr double TARGET_SPEED = 15.0;

// PID 速度控制，返回 {油门, 刹车}
std::pair<double, double> calc_throttle_brake(double current_speed, double target_speed) {
  constexpr double K = 0.2;
  constexpr double B = 0.2;
  double acceleration = (target_speed - current_speed) * K + B;
  if (acceleration > 0) {
    return {std::min(acceleration, 1.0), 0.0};
  }
  return {0.0, std::min(-acceleration * 0.5, 1.0)};
}

// Stanley 循迹算法，返回转向值 [-1, 1]
double calc_steering(const metacar::Vector3 &pos, double yaw, double speed,
                     const std::vector<metacar::Vector3> &trajectory) {
  if (trajectory.empty()) {
    return 0.0;
  }
  constexpr double K = 0.5;
  metacar::Vector3 target_pos = trajectory.back();
  for (const auto &traj_pos : trajectory) {
    if ((traj_pos - pos).length() > K * speed) {
      target_pos = traj_pos;
      break;
    }
  }
  double theta = (target_pos - pos).yaw_rad();
  double steering_angle = std::remainder(theta - yaw, 2.0 * PI);
  double steering = -steering_angle / (PI / 4.0) * 2.0; // 实测乘2效果更好
  return std::clamp(steering, -1.0, 1.0);
}

int main() {
#ifdef _WIN32
  SetConsoleOutputCP(CP_UTF8);
#endif

  metacar::SceneAPI api;

  std::cout << "等待仿真器连接...\n";
  api.connect();
  std::cout << "已连接!\n";

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
    ctrl.gear = metacar::GearMode::DRIVE;

    auto [throttle, brake] = calc_throttle_brake(speed, TARGET_SPEED);
    ctrl.throttle = throttle;
    ctrl.brake = brake;

    ctrl.steering = calc_steering({pose.pos_x, pose.pos_y, pose.pos_z}, -pose.ori_z * PI / 180.0,
                                  speed, msg.trajectory);

    api.set_vehicle_control(ctrl);
  }

  std::cout << "仿真结束。\n";
  return 0;
}
