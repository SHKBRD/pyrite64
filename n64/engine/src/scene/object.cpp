/**
* @copyright 2025 - Max Bebök
* @license MIT
*/
#include "scene/object.h"

#include "scene/componentTable.h"
#include "scene/scene.h"
#include "scene/sceneManager.h"

P64::Object::~Object()
{
  auto compRefs = getCompRefs();
  for (uint32_t i=0; i<compCount; ++i) {
    const auto &compDef = COMP_TABLE[compRefs[i].type];
    char* dataPtr = (char*)this + compRefs[i].offset;
    compDef.initDel(*this, dataPtr, nullptr);
  }
}

void P64::Object::setEnabled(bool isEnabled)
{
  auto oldFlags = flags;
  if(isEnabled) {
    flags |= ObjectFlags::SELF_ACTIVE;
  } else {
    flags &= ~ObjectFlags::SELF_ACTIVE;
  }

  if(oldFlags == flags)return;

  auto compRefs = getCompRefs();
  for (uint32_t i=0; i<compCount; ++i) {
    const auto &compDef = COMP_TABLE[compRefs[i].type];
    if(compDef.onEvent)
    {
      char* dataPtr = (char*)this + compRefs[i].offset;
      compDef.onEvent(*this, dataPtr, {
        .senderId = 0,
        .type = isEnabled ? EVENT_TYPE_ENABLE : EVENT_TYPE_DISABLE,
        .value = 0
      });
    }
  }
}

void P64::Object::remove()
{
  if(flags & ObjectFlags::PENDING_REMOVE)return;
  flags |= ObjectFlags::PENDING_REMOVE;
  flags &= ~ObjectFlags::ACTIVE;
  SceneManager::getCurrent().removeObject(*this);
}
