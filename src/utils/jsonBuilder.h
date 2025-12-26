/**
* @copyright 2025 - Max Bebök
* @license MIT
*/
#pragma once
#include "simdjson.h"
#include "glm/vec3.hpp"
#include "glm/gtc/quaternion.hpp"

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
      Builder& set(const std::string &key, T value) {
        if (hasData) {
          builder.append_comma();
          builder.append_raw("\n");
        }
        builder.append_key_value(key, value);
        hasData = true;
        return *this;
      }

      template<typename PROP>
      Builder& set(const Property<PROP> &prop) {
        set(prop.name, prop.value);
        return *this;
      }

      void set(const std::string &key, const glm::ivec2 &vec) {
        if (hasData)builder.append_comma();

        builder.escape_and_append_with_quotes(key);
        builder.append_colon();
        builder.start_array();
        builder.append(vec.x); builder.append_comma();
        builder.append(vec.y);
        builder.end_array();

        hasData = true;
      }

      void set(const std::string &key, const glm::vec3 &vec) {
        if (hasData)builder.append_comma();

        builder.escape_and_append_with_quotes(key);
        builder.append_colon();
        builder.start_array();
        builder.append(vec.x); builder.append_comma();
        builder.append(vec.y); builder.append_comma();
        builder.append(vec.z);
        builder.end_array();

        hasData = true;
      }


      Builder& set(const std::string &key, const glm::vec4 &vec) {
        if (hasData)builder.append_comma();

        builder.escape_and_append_with_quotes(key);
        builder.append_colon();
        builder.start_array();
        builder.append(vec.x); builder.append_comma();
        builder.append(vec.y); builder.append_comma();
        builder.append(vec.z); builder.append_comma();
        builder.append(vec.w);
        builder.end_array();

        hasData = true;
        return *this;
      }

      void set(const std::string &key, const glm::quat &vec) {
        if (hasData)builder.append_comma();

        builder.escape_and_append_with_quotes(key);
        builder.append_colon();
        builder.start_array();
        builder.append(vec.x); builder.append_comma();
        builder.append(vec.y); builder.append_comma();
        builder.append(vec.z); builder.append_comma();
        builder.append(vec.w);
        builder.end_array();

        hasData = true;
      }

      void set(const std::string &key, Builder &build) {
        if (hasData)builder.append_comma();
        builder.escape_and_append_with_quotes(key);
        builder.append_colon();
        builder.append_raw(build.toString());
        hasData = true;
      }

      template<typename T>
      Builder& setArray(const std::string &key, const std::vector<T> &parts, std::function<void(Builder&, const T&)> cb) {
        if (hasData)builder.append_comma();
        builder.escape_and_append_with_quotes(key);
        builder.append_colon();
        builder.start_array();

        bool needsComma = false;
        for (auto &part : parts) {
          if (needsComma) {
            builder.append_comma();
            builder.append_raw("\n");
          }
          Builder childBuilder{};
          cb(childBuilder, part);
          builder.append_raw(childBuilder.toString());
          needsComma = true;
        }
        builder.end_array();

        hasData = true;
        return *this;
      }

      void setRaw(const std::string &key, const std::vector<std::string> &parts) {
        if (hasData)builder.append_comma();
        builder.escape_and_append_with_quotes(key);
        builder.append_colon();
        builder.start_array();

        bool needsComma = false;
        for (auto &part : parts) {
          if (needsComma) {
            builder.append_comma();
            builder.append_raw("\n");
          }
          builder.append_raw(part);
          needsComma = true;
        }
        builder.end_array();

        hasData = true;
      }

      void setRaw(const std::string &key, const std::string &part) {
        if (hasData)builder.append_comma();
        builder.escape_and_append_with_quotes(key);
        builder.append_colon();
        builder.append_raw(part);
        builder.append_raw("\n");
        hasData = true;
      }

      void set(const std::string &key, std::vector<Builder> &build) {
        std::vector<std::string> parts{};
        for (auto &child : build) {
          parts.push_back(child.toString());
        }
        setRaw(key, parts);
      }

      std::string toString() {
        return std::string{builder.c_str()} + "}";
      }
  };
}
