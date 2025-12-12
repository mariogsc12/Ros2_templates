#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "rclcpp/rclcpp.hpp"
#include "simple_service/srv/add_two_ints.hpp"

class ServiceClient : public rclcpp::Node{
    private:
        void response_callback(rclcpp::Client<simple_service::srv::AddTwoInts>::SharedFuture future);
        rclcpp::Client<simple_service::srv::AddTwoInts>::SharedPtr client_;
    public: 
        ServiceClient(int a, int b);
};

#endif // CLIENT_HPP
