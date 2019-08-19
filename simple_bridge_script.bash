# namespace ns1 -> veth1 10.0.0.1/24
# namespace ns2 -> veth2 10.0.0.2/24

clear
polycubectl simplemonitor sm1

for i in `seq 1 2`;
do
    sudo ip netns del ns${i} > /dev/null 2>&1 # remove ns if already existed
    sudo ip link del veth${i} > /dev/null 2>&1

    sudo ip netns add ns${i}
    sudo ip link add veth${i}_ type veth peer name veth${i}
    sudo ip link set veth${i}_ netns ns${i}
    sudo ip netns exec ns${i} ip link set dev veth${i}_ up
    sudo ip link set dev veth${i} up
    sudo ip netns exec ns${i} ifconfig veth${i}_ 10.0.0.${i}/24
done

polycubectl simplebridge add br1
polycubectl br1 ports add toveth1
polycubectl connect br1:toveth1 veth1
polycubectl br1 ports add toveth2 peer=veth2

polycubectl attach sm1 br1:toveth1


# ping ns2 from ns1
sudo ip netns exec ns1 ping 10.0.0.2 -c 1

# ping ns1 from ns2
sudo ip netns exec ns2 ping 10.0.0.1 -c 1
