/**
* @copyright 2025 - Max Bebök
* @license MIT
*/
#include "project.h"
#include "../utils/fs.h"

#include "../utils/json.h"
#include "../utils/jsonBuilder.h"

using namespace simdjson;

std::string Project::ProjectConf::serialize() const {
  Utils::JSON::Builder builder{};
  builder.set("name", name);
  builder.set("romName", romName);
  builder.set("pathEmu", pathEmu);
  builder.set("pathN64Inst", pathN64Inst);
  return builder.toString();
}

void Project::Project::deserialize(const simdjson_result<dom::element> &doc) {
  conf.name = Utils::JSON::readString(doc, "name");
  conf.romName = Utils::JSON::readString(doc, "romName");
  conf.pathEmu = Utils::JSON::readString(doc, "pathEmu");
  conf.pathN64Inst = Utils::JSON::readString(doc, "pathN64Inst");
}

Project::Project::Project(const std::string &path)
  : path{path}, pathConfig{path + "/project.json"}
{
  deserialize(Utils::JSON::loadFile(pathConfig));
  assets.reload();
  scenes.reload();
}

void Project::Project::save() {
  Utils::FS::saveTextFile(pathConfig, conf.serialize());
  assets.save();
  scenes.save();
}
