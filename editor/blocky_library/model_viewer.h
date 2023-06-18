#ifndef ZN_GODOT_MODEL_VIEWER_H
#define ZN_GODOT_MODEL_VIEWER_H

#include "../../util/godot/classes/control.h"
#include "../../util/macros.h"

ZN_GODOT_FORWARD_DECLARE(class Camera3D);
ZN_GODOT_FORWARD_DECLARE(class SubViewport);

namespace zylann {

class ZN_Axes3DControl;

// Basic SubViewport embedded in a Control for viewing 3D stuff.
// Implements camera controls orbitting around the origin.
// Godot has `MeshEditor` but it is specialized for Mesh resources without access to the hierarchy.
class ZN_ModelViewer : public Control {
	GDCLASS(ZN_ModelViewer, Control)
public:
	ZN_ModelViewer();

	void set_camera_distance(float d);

	// Stuff to view can be instanced under this node
	Node *get_viewer_root_node() const;

private:
#if defined(ZN_GODOT)
	void gui_input(const Ref<InputEvent> &p_event) override;
#elif defined(ZN_GODOT_EXTENSION)
	void _gui_input(const Ref<InputEvent> &p_event) override;
#endif
	void update_camera();

	// When compiling with GodotCpp, `_bind_methods` isn't optional.
	static void _bind_methods() {}

	Camera3D *_camera = nullptr;
	float _pitch = 0.f;
	float _yaw = 0.f;
	float _distance = 1.9f;
	ZN_Axes3DControl *_axes_3d_control = nullptr;
	SubViewport *_viewport;
};

} // namespace zylann

#endif // ZN_GODOT_MODEL_VIEWER_H