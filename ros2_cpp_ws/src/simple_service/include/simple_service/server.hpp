#ifndef SERVER_HPP
#define SERVER_HPP

#include "rclcpp/rclcpp.hpp"
#include "simple_service/srv/add_two_ints.hpp"

class ServiceServer : public rclcpp::Node
{
    public:
        ServiceServer(const std::string &name);
    private:
        rclcpp::Service<simple_service::srv::AddTwoInts>::SharedPtr service_;

        void service_callback(const std::shared_ptr<simple_service::srv::AddTwoInts::Request> req,
                            const std::shared_ptr<simple_service::srv::AddTwoInts::Response> res);

};

#endif // SERVER_HPP