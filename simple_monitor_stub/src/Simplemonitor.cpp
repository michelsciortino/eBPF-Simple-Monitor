/**
* simplemonitor API generated from simplemonitor.yang
*/

#include "Simplemonitor.h"

#include "Simplemonitor_dp_egress.h"
#include "Simplemonitor_dp_ingress.h"

using namespace polycube::service::model;
using namespace polycube::service;
using namespace polycube::service::utils;

Simplemonitor::Simplemonitor(const std::string name, const SimplemonitorJsonObject &conf)
    : TransparentCube(conf.getBase(), {simplemonitor_code_ingress}, {simplemonitor_code_egress}),
      SimplemonitorBase(name)
{
  logger()->info("Creating Simplemonitor instance");
  setIngressAction(conf.getIngressAction());
  setEgressAction(conf.getEgressAction());
}

Simplemonitor::~Simplemonitor()
{
  logger()->info("Destroying Simplemonitor instance");
}

void Simplemonitor::attach()
{
  logger()->info("Monitor attaching to peer..");
  try
  {
    std::string parent_peer = get_parent_parameter("peer");
    logger()->info("parent peer is: {}", parent_peer);
  }
  catch (const std::exception &e)
  {
    logger()->warn("Error getting parent parameter: {}", e.what());
  }
}

void Simplemonitor::packet_in(polycube::service::Sense sense,
                              polycube::service::PacketInMetadata &md,
                              const std::vector<uint8_t> &packet)
{
  logger()->info("CONTROL: Packet received");
  switch (sense)
  {
  case polycube::service::Sense::INGRESS:
    logger()->info("CONTROL: packet in event from ingress program");
    break;
  case polycube::service::Sense::EGRESS:
    logger()->info("CONTROL: packet in event from egress program");
    break;
  }

  uint64_t src_mac = 0;
  uint64_t dst_mac = 0;


  logger()->info("packet lenght:{0}", packet.size());
  for (uint i = 0; i < 6; i++)
    src_mac = (src_mac << 8) + packet[i];
  for(uint i=6; i< 12; i++)
    dst_mac = (dst_mac << 8) + packet[i];

  logger()->info("CONTROL: src mac: {0}", utils::nbo_uint_to_mac_string(src_mac));
  logger()->info("CONTROL: dst mac: {0}", utils::nbo_uint_to_mac_string(dst_mac));
  //logger()->info("packet lenght:{0}",packet.size());
}

SimplemonitorIngressActionEnum Simplemonitor::getIngressAction()
{
  logger()->info("getting Ingress Action");
  auto t = get_array_table<uint8_t>("action_map", 0, ProgramType::INGRESS);
  uint8_t value = t.get(0x0);
  return static_cast<SimplemonitorIngressActionEnum>(value);
}

void Simplemonitor::setIngressAction(const SimplemonitorIngressActionEnum &value)
{
  logger()->info("setting Ingress Action to {0}", ingressActionToString(value));
  uint8_t action = static_cast<uint8_t>(value);
  auto t = get_array_table<uint8_t>("action_map", 0, ProgramType::INGRESS);
  t.set(0x0, action);
}

SimplemonitorEgressActionEnum Simplemonitor::getEgressAction()
{
  logger()->info("getting Egress Action");
  auto t = get_array_table<uint8_t>("action_map", 0, ProgramType::EGRESS);
  uint8_t value = t.get(0x0);
  return static_cast<SimplemonitorEgressActionEnum>(value);
}

void Simplemonitor::setEgressAction(const SimplemonitorEgressActionEnum &value)
{
  logger()->info("setting Egress Action to {0}", egressActionToString(value));
  uint8_t action = static_cast<uint8_t>(value);
  auto t = get_array_table<uint8_t>("action_map", 0, ProgramType::EGRESS);
  t.set(0x0, action);
}