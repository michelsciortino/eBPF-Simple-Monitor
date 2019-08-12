/**
* simplemonitor API generated from simplemonitor.yang
*
* NOTE: This file is auto generated by polycube-codegen
* https://github.com/polycube-network/polycube-codegen
*/


/* Do not edit this file manually */

/*
* SimplemonitorBase.h
*
*
*/

#pragma once

#include "../serializer/SimplemonitorJsonObject.h"


#include "polycube/services/transparent_cube.h"



#include "polycube/services/utils.h"
#include "polycube/services/fifo_map.hpp"

#include <spdlog/spdlog.h>

using namespace polycube::service::model;


class SimplemonitorBase: public virtual polycube::service::TransparentCube {
 public:
  SimplemonitorBase(const std::string name);
  
  virtual ~SimplemonitorBase();
  virtual void update(const SimplemonitorJsonObject &conf);
  virtual SimplemonitorJsonObject toJsonObject();

  /// <summary>
  /// Action performed on ingress packets
  /// </summary>
  virtual SimplemonitorIngressActionEnum getIngressAction() = 0;
  virtual void setIngressAction(const SimplemonitorIngressActionEnum &value) = 0;

  /// <summary>
  /// Action performed on egress packets
  /// </summary>
  virtual SimplemonitorEgressActionEnum getEgressAction() = 0;
  virtual void setEgressAction(const SimplemonitorEgressActionEnum &value) = 0;
};
