#ifndef SIMPLE_SUBSCRIBER_HPP
#define SIMPLE_SUBSCRIBER_HPP

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class SimpleSubscriber : public rclcpp::Node{
    private:
        rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_;
        void callback(const std_msgs::msg::String &msg);

    public:
        SimpleSubscriber(const std::string &name);
};

#endif  // SIMPLE_SUBSCRIBER_HPP
