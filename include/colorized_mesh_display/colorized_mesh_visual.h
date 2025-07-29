#ifndef COLORIZED_MESH_VISUAL_H
#define COLORIZED_MESH_VISUAL_H

#include <OgrePrerequisites.h>

namespace pcl
{
struct PolygonMesh;
}

namespace colorized_mesh_display
{

class ColorizedMeshShape;

class ColorizedMeshVisual
{
public:
  ColorizedMeshVisual(Ogre::SceneManager *scene_manager, Ogre::SceneNode *parent_node = nullptr);

  virtual ~ColorizedMeshVisual();

  void visualizeMesh(const pcl::PolygonMesh& msg);

  void setFramePosition(const Ogre::Vector3& position);

  void setFrameOrientation(const Ogre::Quaternion& orientation);

private:

  Ogre::SceneManager* scene_manager_{ nullptr };

  Ogre::SceneNode* frame_node_{ nullptr };

  Ogre::ManualObject* manual_object_{ nullptr };

  Ogre::Entity* entity_{ nullptr };

  std::string material_name_;
};

} // namespace colorized_mesh_display

#endif // COLORIZED_MESH_VISUAL_H
