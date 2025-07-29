#include <colorized_mesh_display/colorized_mesh_display.h>
#include <colorized_mesh_display/colorized_mesh_visual.h>
#include <pcl_conversions/pcl_conversions.h>

#include <rviz_common/display.hpp>

namespace colorized_mesh_display
{

ColorizedMeshDisplay::ColorizedMeshDisplay() = default;

ColorizedMeshDisplay::~ColorizedMeshDisplay() = default;

void ColorizedMeshDisplay::onInitialize()
{
  MFDClass::onInitialize();
}

void ColorizedMeshDisplay::reset()
{
  MFDClass::reset();
  visual_.reset();
}

void ColorizedMeshDisplay::processMessage(std::shared_ptr<const pcl_msgs::msg::PolygonMesh> msg)
{
  // Get the transform
  Ogre::Quaternion orientation;
  Ogre::Vector3 position;

  if( !context_->getFrameManager()->getTransform(msg->header.frame_id,
                                                 msg->header.stamp,
                                                 position, orientation))
  {
    RCLCPP_ERROR(rviz_ros_node_.lock()->get_raw_node()->get_logger(), "Error transforming into frame '%s'", msg->header.frame_id.c_str());
    return;
  }

  pcl::PolygonMesh mesh;
  pcl_conversions::toPCL(*msg, mesh);

  visual_.reset(new ColorizedMeshVisual(scene_manager_));
  visual_->visualizeMesh(mesh);
  visual_->setFramePosition(position);
  visual_->setFrameOrientation(orientation);
}

} // namespace colorized_mesh_display

#include <pluginlib/class_list_macros.hpp>
PLUGINLIB_EXPORT_CLASS(colorized_mesh_display::ColorizedMeshDisplay, rviz_common::Display)
