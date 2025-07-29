#include <rclcpp/rclcpp.hpp>
#include <pcl/io/vtk_lib_io.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl_msgs/msg/polygon_mesh.hpp>

template <typename T>
bool getParam(rclcpp::Node::SharedPtr node, const std::string& key, T& val)
{
    if (!node->get_parameter(key, val))
    {
        RCLCPP_ERROR(node->get_logger(), "Failed to get '%s' parameter", key.c_str());
        return false;
    }
    return true;
}

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("colorized_mesh_display_test_node");

    // Declare parameters
    node->declare_parameter<std::string>("mesh_file", "");
    node->declare_parameter<std::string>("base_frame", "world");

    std::string path;
    std::string base_frame;
    if (!getParam(node, "mesh_file", path) || !getParam(node, "base_frame", base_frame))
        return -1;

    // Load mesh
    pcl_msgs::msg::PolygonMesh msg;
    {
        pcl::PolygonMesh mesh;
        if (pcl::io::loadPolygonFile(path, mesh) < 0)
        {
            RCLCPP_ERROR(node->get_logger(), "Failed to load mesh file from '%s'", path.c_str());
            return -1;
        }

        RCLCPP_INFO(node->get_logger(), "Successfully loaded mesh file");

        pcl_conversions::fromPCL(mesh, msg);
        msg.header.frame_id = base_frame;
        msg.header.stamp = node->now();
    }

    // Publisher
    auto pub = node->create_publisher<pcl_msgs::msg::PolygonMesh>("colorized_mesh", 1);
    pub->publish(msg);
    RCLCPP_INFO(node->get_logger(), "Published colorized mesh");

    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
