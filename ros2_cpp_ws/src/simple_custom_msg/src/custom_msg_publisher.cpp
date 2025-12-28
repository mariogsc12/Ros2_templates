#include <simple_custom_msg/custom_msg_publisher.hpp>

SimpleCustomMsgPublisher::SimpleCustomMsgPublisher(const std::string &name) : Node(name), id(0){
    pub_ = create_publisher<simple_custom_msg::msg::CustomMsg>("custom_msg_topic", 10);
    timer_ = create_wall_timer(std::chrono::seconds(1), std::bind(&SimpleCustomMsgPublisher::timer_callback, this));
    RCLCPP_INFO_STREAM(get_logger(), "Publishing Custom Msg at 1 Hz");
}

void SimpleCustomMsgPublisher::timer_callback(){
    auto message = simple_custom_msg::msg::CustomMsg();
    message.id = ++id;
    message.text = "Hello ROS 2. This is a custom msg";
    pub_->publish(message);
}

int main(int argc, char* argv[]){
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SimpleCustomMsgPublisher>("custom_msg_publisher_node");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}