
/*
 * Copyright 2019 The Polycube Authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <bcc/helpers.h>

enum {
  SLOWPATH_REASON = 1,
};

enum {
  DROP,      // drop packet
  PASS,      // let packet go
  SLOWPATH,  // send packet to slowpath
  TWO_WAY
};

BPF_ARRAY(action_map, uint8_t, 1);

struct eth_hdr {
  __be64 dst : 48;
  __be64 src : 48;
  __be16 proto;
} __attribute__((packed));


static int handle_rx(struct CTXTYPE *ctx, struct pkt_metadata *md) {
  unsigned int zero = 0;
  uint8_t *action = action_map.lookup(&zero);
  // This check is needed by the verifier but will never happen because
  // the size of the array is 1.
  if (!action) {
    pcn_log(ctx, LOG_ERR, "Ingress: action not set -> DROP");
    return RX_DROP;
  }
  
  // what action should be performed in the packet?
  switch (*action) {
  case DROP:
    pcn_log(ctx, LOG_DEBUG, "Ingress: dropping packet");
    return RX_DROP;
  case PASS:
    pcn_log(ctx, LOG_DEBUG, "Ingress: passing packet");
    return RX_OK;
  case SLOWPATH:
    pcn_log(ctx, LOG_DEBUG, "Ingress: sending packet to slow path");
    return pcn_pkt_controller(ctx, md, SLOWPATH_REASON);
  case TWO_WAY:
    pcn_log(ctx, LOG_INFO, "Ingress: sending packet duplicate to slow path");
    pcn_pkt_controller(ctx, md, SLOWPATH_REASON);
    return RX_OK;
  default:
    pcn_log(ctx, LOG_DEBUG, "Ingress: bad action %d", *action);
    return RX_DROP;
  }

  return RX_OK;
}