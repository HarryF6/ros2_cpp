#include "rclcpp/rclcpp.hpp"

class MyNode : public rclcpp::Node    // class declaration which inherits from rclcpp::Node
{
public:
  MyNode() : Node("DarthVader")
  {
    RCLCPP_INFO_STREAM(this->get_logger(), "I am your father.");   // just a printout
  }
};


int main(int argc, char *argv[]) {

    rclcpp::init(argc, argv);
    // tres maneras de inicializar nodos en ROS2
    auto node = rclcpp::Node::make_shared("ObiWan");

    RCLCPP_INFO(node->get_logger(),
            "Help me Obi-Wan Kenobi, you're my only hope");

    auto node2 = std::make_shared<MyNode>();
    //rclcpp::spin(node);

    auto node3 = std::make_shared<rclcpp::Node>("Yoda");
    RCLCPP_INFO(node3->get_logger(),
            "You must unlearn what you have learned");
    rclcpp::spin(node);
    return 0;
}