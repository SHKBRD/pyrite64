#include "script/userScript.h"
#include "scene/sceneManager.h"
#include "../p64/assetTable.h"
#include <libdragon.h>
#include <vi/swapChain.h>

namespace P64::Script::C7D3D67FA276A9FE
{
  P64_DATA(
    // Put your arguments and runtime values bound to an object here.
    // If you need them to show up in the editor, add a [[P64::Name("...")]] attribute.
    //
    // Types that can be set in the editor:
    // - uint8_t, int8_t, uint16_t, int16_t, uint32_t, int32_t
    // - float
    // - AssetRef<sprite_t>
    // - ObjectRef
    //
    // Other types can be used but are not exposed in the editor.

    [[P64::Name("Path Holder")]]
    ObjectRef pathHolder;
    [[P64::Name("Path Runner")]]
    ObjectRef pathRunner;

    const int8_t times=8;
    float magnitude = 100.0f;
    
    bool generatingPath=false;
    int8_t order[8];
    uint16_t pathPoints[8];
    float_t cz = 0.0;
    float_t cy = 0.0;
    float_t p = 0.0;
  );

  // Fisher-Yates algorithm
  int8_t* chooseOrder(int8_t* array) {
    for (int8_t i = 0; i < 8; ++i) {
        array[i] = i + 1;
    }
    for (int8_t i = 7; i > 0; --i) {
        int8_t j = static_cast<int8_t>(Math::rand01() * (i + 1));
        int8_t temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
    return array;
  }

  void resetPathPoints(Object& obj, Data *data) {
    // pathHolder won't reference an object when this runs during startup
    if (data->pathHolder != nullptr && data->pathHolder->hasChildren()) {
      data->pathHolder->iterChildren([](Object* child) {
         child->remove();
       });
    }
  }

  void spawnPoint(Object& obj, Data *data, int8_t idx) {
    float_t progress = static_cast<float_t>(data->order[idx])/static_cast<float_t>(data->times);
    float_t zOff = cosf(progress*2*FM_PI)*data->magnitude;
    float_t yOff = sinf(progress*2*FM_PI)*data->magnitude;
    fm_vec3_t off{0.0, yOff, zOff};
    data->cy = yOff;
    data->cz = zOff;
    data->p = progress;
    off += obj.pos;
    data->pathPoints[idx] = obj.getScene().addObject("point/Point.pf"_asset, off);
  }

  void makePathPoints(Object& obj, Data *data) {
    data->generatingPath = true;
    resetPathPoints(obj, data);
    chooseOrder(data->order);
    
    data->magnitude = 80.0f;
    for (int8_t i=0; i < data->times; ++i) {
      spawnPoint(obj, data, i);
    }
    return;
  }

  void updatePathPointModels(Object& obj, Data *data) {
    for (int8_t i=0; i < data->times; i++) {

    }
  }

  bool isPathReady(Object& obj, Data *data) {
    return data->pathHolder->hasChildren();
  }

  // The following functions are called by the engine at different points in the object's lifecycle.
  // If you don't need a specific function you can remove it.

  void init(Object& obj, Data *data)
  {
    // initialization, this is called once when the object spawns
    makePathPoints(obj, data);
  }

  void destroy(Object& obj, Data *data)
  {
    // clean-up, this is called when the object gets deleted
  }

  

  void update(Object& obj, Data *data, float deltaTime)
  {
    // this is called once every frame, put your main logic here
    if (data->generatingPath && isPathReady(obj, data)) {
      updatePathPointModels(obj, data);
    }
  }

  void draw(Object& obj, Data *data, float deltaTime)
  {
    // this is called once every frame, and for every active camera.
    // Put your drawing code here
    rdpq_text_printf(nullptr, 1, 10, 200, "P: %.2f %.2f",data->cz, data->cy);
    rdpq_text_printf(nullptr, 1, 10, 180, "Prog: %.5f",data->p);
    rdpq_text_printf(nullptr, 1, 10, 160, "Mag: %f",data->magnitude);
  }

  void onEvent(Object& obj, Data *data, const ObjectEvent &event)
  {
    // generic events an object can receive
    switch(event.type)
    {
      case EVENT_TYPE_ENABLE: // object got enabled
      break;
      case EVENT_TYPE_DISABLE: // object got disabled
      break;

      // you can check for your own custom types here too
    }
  }

  void onCollision(Object& obj, Data *data, const Coll::CollEvent& event)
  {
    // collision callbacks, only used if any collider is attached
  }
}
