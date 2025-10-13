#include "scene/sceneManager.h"

namespace P64::Script::C3AF5D870988CBC0
{
  struct Data
  {
    [[P64::Name("Scene ID")]]
    uint32_t sceneId;

    [[P64::Name("Speed"), P64::Min("1")]]
    float speed = 1.0f;
  };

  void update(Object& obj, Data *data)
  {
    auto pressed = joypad_get_buttons_pressed(JOYPAD_PORT_1);
    if (pressed.b) {
      debugf("Arg: Scene-Id: %ld\n", data->sceneId);
      SceneManager::load(data->sceneId);
    }
  }
}
