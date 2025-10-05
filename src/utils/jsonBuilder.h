/**
* @copyright 2025 - Max Bebök
* @license MIT
*/
#pragma once
#include "simdjson.h"

namespace Utils::JSON
{
  class Builder
  {
    private:
      simdjson::builder::string_builder builder{};
      bool hasData = false;

    public:
      Builder() {
        builder.start_object();
      }

      template<typename T>
      void set(const std::string &key, T value) {
        if (hasData)builder.append_comma();
        builder.append_key_value(key, value);
        builder.append_raw("\n");
        hasData = true;
      }

      std::string toString() {
        builder.end_object();
        return {builder.c_str()};
      }
  };
}
