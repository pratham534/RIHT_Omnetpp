package RIHT;

simple MyRoutingProtocol {
    parameters:
        @display("i=block/network2");
    gates:
        inout lowerLayerIn[];  // Incoming packets from lower layer
        inout lowerLayerOut[]; // Outgoing packets to lower layer
}
