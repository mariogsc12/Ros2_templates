#include "simple_subscriber/simple_subscriber.hpp"

SimpleSubscriber::SimpleSubscriber(const std::string &name) : Node(name){
    RCLCPP_INFO_STREAM(get_logger(), "Starting " << name.c_str());

    sub_ = create_subscription<std_msgs::msg::String>("hello_world_topic", 10, std::bind(&SimpleSubscriber::callback, this, std::placeholders::_1));
}

void SimpleSubscriber::callback(const std_msgs::msg::String &msg){
    RCLCPP_INFO_STREAM(get_logger(), "Received msg: " << msg.data.c_str());
}

int main(int argc, char* argv[]){
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SimpleSubscriber>("simple_subscriber_node");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}