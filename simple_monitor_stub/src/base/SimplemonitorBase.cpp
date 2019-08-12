/**
* simplemonitor API generated from simplemonitor.yang
*
* NOTE: This file is auto generated by polycube-codegen
* https://github.com/polycube-network/polycube-codegen
*/


/* Do not edit this file manually */


#include "SimplemonitorBase.h"

SimplemonitorBase::SimplemonitorBase(const std::string name) {
  logger()->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [Simplemonitor] [%n] [%l] %v");
}



SimplemonitorBase::~SimplemonitorBase() {}

void SimplemonitorBase::update(const SimplemonitorJsonObject &conf) {
  set_conf(conf.getBase());

  if (conf.ingressActionIsSet()) {
    setIngressAction(conf.getIngressAction());
  }
  if (conf.egressActionIsSet()) {
    setEgressAction(conf.getEgressAction());
  }
}

SimplemonitorJsonObject SimplemonitorBase::toJsonObject() {
  SimplemonitorJsonObject conf;
  conf.setBase(to_json());

  conf.setName(getName());
  conf.setIngressAction(getIngressAction());
  conf.setEgressAction(getEgressAction());

  return conf;
}


