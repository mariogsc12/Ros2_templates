#ifndef custom_msg_publisher_HPP
#define custom_msg_publisher_HPP

#include "rclcpp/rclcpp.hpp"

// IMPORTANT: ROS 2 message (.msg) and service (.srv) files are NOT included directly.
// They are used to generate C++ headers, which must be included instead.
// The generated headers are located under <package_name>/msg and use snake_case naming.
// Example:
#include "simple_custom_msg/msg/custom_msg.hpp"

class SimpleCustomMsgPublisher : public rclcpp::Node{
    private:
        void timer_callback();
        rclcpp::Publisher<simple_custom_msg::msg::CustomMsg>::SharedPtr pub_;
        rclcpp::TimerBase::SharedPtr timer_;
        int id;
        
    public: 
        SimpleCustomMsgPublisher(const std::string &name);
};

#endif // custom_msg_publisher_HPP
