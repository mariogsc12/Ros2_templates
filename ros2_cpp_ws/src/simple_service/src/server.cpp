#include "simple_service/server.hpp"

ServiceServer::ServiceServer(const std::string &name) : Node(name) {
    RCLCPP_INFO_STREAM(get_logger(), "Starting " << name.c_str() << " node");
    service_ = create_service<simple_service::srv::AddTwoInts>("add_two_ints", std::bind(&ServiceServer::service_callback, this, std::placeholders::_1, std::placeholders::_2));;
}

void ServiceServer::service_callback(const std::shared_ptr<simple_service::srv::AddTwoInts::Request> req,
                            const std::shared_ptr<simple_service::srv::AddTwoInts::Response> res){
        RCLCPP_INFO_STREAM(rclcpp::get_logger("rclcpp"), "New Request Received a: " << req->a << " b: " << req->b);
        res->sum = req->a + req->b;
        RCLCPP_INFO_STREAM(rclcpp::get_logger("rclcpp"), "Returning sum: " << res->sum);
}

int main(int argc, char* argv[])
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<ServiceServer>("service_server");
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}