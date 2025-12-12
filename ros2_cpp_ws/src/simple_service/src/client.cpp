#include "simple_service/client.hpp"

ServiceClient::ServiceClient(int a, int b) : Node("service_client") {
    RCLCPP_INFO_STREAM(get_logger(), "Starting service_client node");
    client_ = create_client<simple_service::srv::AddTwoInts>("add_two_ints");

    auto request = std::make_shared<simple_service::srv::AddTwoInts::Request>();
    request->a = a;
    request->b = b;

    while(!client_->wait_for_service(std::chrono::seconds(1))){
        if(!rclcpp::ok()){
            RCLCPP_ERROR(get_logger(), "Interrupted while waiting for the service. Exiting");
            return;
        }
        RCLCPP_INFO_STREAM(get_logger(), "service not available, wating...");
    }

    auto result = client_->async_send_request(request, std::bind(&ServiceClient::response_callback, this, std::placeholders::_1));
}

// SharedFuture enables asynchronous handling of the service response,
//      allowing the program to continue running while waiting for the result.
void ServiceClient::response_callback(rclcpp::Client<simple_service::srv::AddTwoInts>::SharedFuture future){
    if(future.valid()){
        RCLCPP_INFO_STREAM(get_logger(), "Service response " << future.get()->sum);
    }
    else{
        RCLCPP_ERROR_STREAM(get_logger(), "Service Failure");
    }
}

int main(int argc, char* argv[])
{
  rclcpp::init(argc, argv);

  if (argc != 3) {
    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Wrong number of arguments! Usage: service_client 1 2");
    return 1;
  }

  auto node = std::make_shared<ServiceClient>(atoi(argv[1]), atoi(argv[2]));
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}