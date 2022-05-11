#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "tutorial_interfaces/msg/num.hpp"     // CHANGE
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses std::bind() to register a
* member function as a callback from the timer. */

class MinimalPublisher : public rclcpp::Node
{
  public:
    MinimalPublisher()
    : Node("publisher"), count_(0)
    {
      //publisher_ = this->create_publisher<std_msgs::msg::String>("topic_msg", 10);
      publisher_ = this->create_publisher<tutorial_interfaces::msg::Num>("topic_msg", 10);
      timer_ = this->create_wall_timer(500ms, std::bind(&MinimalPublisher::timer_callback, this)); // publicar mensajes cada 500ms
    }

  private:
    void timer_callback()
    {
      auto message = tutorial_interfaces::msg::Num();
      message.num = this->count_++;
      //message.data = "Hello, world! " + std::to_string(count_++);
      RCLCPP_INFO(this->get_logger(), "Publishing: '%i'", message.num);
      publisher_->publish(message);
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<tutorial_interfaces::msg::Num>::SharedPtr publisher_;
    //rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}