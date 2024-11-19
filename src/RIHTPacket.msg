// RIHTPacket.msg
//package RIHT;

message RIHTPacket {
    int mark;
    int UI;
    string srcAddress; // Source IP address
    string destAddress; // Destination IP address
}