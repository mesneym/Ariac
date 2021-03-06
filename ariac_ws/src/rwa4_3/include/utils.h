#ifndef UTILS_H
#define UTILS_H

#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Point.h>
#include <unordered_map>
#include <string>

#include <ros/ros.h>

#include <nist_gear/VacuumGripperState.h>

#include <tf2_ros/buffer.h>
#include <tf2_ros/transform_listener.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>

typedef struct Shipment shipment; // forward declarations
typedef struct Order order;
typedef struct Product product;

const double PI = 3.141592; // TODO correct!

// Logical cameras
const int MAX_NUMBER_OF_CAMERAS = 17;



const int MAX_PICKING_ATTEMPTS = 3; // for pickup
const double ABOVE_TARGET = 0.2; // above target z pos when picking/placing part
const double PICK_TIMEOUT = 4.0;
const double RETRIEVE_TIMEOUT = 2.0;

const double BELT_SPEED = 0.2; // m/s

const double GRIPPER_HEIGHT = 0.01;
const double EPSILON = 0.008; // for the gripper to firmly touch

const double BIN_HEIGHT = 0.724;
const double TRAY_HEIGHT = 0.755;
const double RAIL_HEIGHT = 0.95;

const double PLANNING_TIME = 20; // for move_group
const int MAX_EXCHANGE_ATTEMPTS = 6; // Pulley flip

extern std::string action_state_name[];
extern std::unordered_map<std::string, double> model_height;

enum PartStates {FREE, BOOKED, UNREACHABLE, ON_TRAY, GRIPPED, GOING_HOME,
  REMOVE_FROM_TRAY, LOST};



typedef struct PresetLocation {
    std::vector<double> gantry;
    std::vector<double> left_arm;
    std::vector<double> right_arm;
} start, bin3, agv2, agv1, agv1_faultyG, agv2_faultyG, bin13, bin16, shelf5_1, shelf5_2, shelf5_3, shelf5_4, shelf5_5,shelf11_1, shelf11_2, shelf11_3,
shelf8_1, shelf8_2, shelf8_3, agv2_go_to_flipped_pulley, agv1_go_to_flipped_pulley,agv2_flipped, agv2_flipped1,agv1_flipped, agv1_flipped1, agv1_drop,
agv2_drop, movingPart, movingPart1, agv1_gasket_part_green;

typedef struct Part {
  std::string type; // model type
  geometry_msgs::Pose pose; // model pose (in frame)
  geometry_msgs::Pose save_pose;
  std::string frame; // model frame (e.g., "logical_camera_1_frame")
  ros::Time time_stamp;
  std::string id;
  PartStates state; // model state (enum PartStates)
  bool faulty;
} part;

typedef struct Position {
    std::vector<double> gantry;
    std::vector<double> left;
    std::vector<double> right;
} position;

typedef struct Shipment {
    std::string shipment_type;
    std::string agv_id;
    std::vector<Product> products;
    order* parent_order;
} shipment;

typedef struct Product {
    std::string type;
    geometry_msgs::Pose pose;
    part p; // NEW here!
    // std::string frame_of_origin;
    geometry_msgs::Pose actual_pose;
    std::string actual_pose_frame;
    std::string agv_id;
    std::string tray;
    std::string arm_name;
    std::string cache_id;
    shipment* parent_shipment{};
    bool high_priority{};
    int correction_attempts{};
    int service_attempts{};

    Product(); // contructor
} product;

typedef struct Order {
    std::string order_id;
    std::vector<Shipment> shipments;
} order;

typedef struct Stats {
  double total_time = 0.0;
  double fail_time = 0.0;
  int calls = 0;
  int fails = 0;
} stats;


#endif
