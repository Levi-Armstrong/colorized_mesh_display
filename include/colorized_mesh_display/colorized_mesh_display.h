#ifndef COLORIZED_MESH_DISPLAY_H
#define COLORIZED_MESH_DISPLAY_H

#include <rviz_common/message_filter_display.hpp>
#include <pcl_msgs/msg/polygon_mesh.hpp>

namespace colorized_mesh_display
{

class ColorizedMeshVisual;

class ColorizedMeshDisplay : public rviz_common::MessageFilterDisplay<pcl_msgs::msg::PolygonMesh>
{
  Q_OBJECT

public:

  ColorizedMeshDisplay();

  virtual ~ColorizedMeshDisplay();

protected:

  void onInitialize() override;

  void reset() override;

private:

  void processMessage(std::shared_ptr<const pcl_msgs::msg::PolygonMesh> msg) override;

  std::shared_ptr<ColorizedMeshVisual> visual_;

};

} // namespace colorized_mesh_display

#endif // COLORIZED_MESH_DISPLAY_H
