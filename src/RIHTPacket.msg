// RIHTPacket.msg
//package RIHT;

//import inet.networklayer.ipv4.Ipv4Header;
//
//class RIHTPacket extends Ipv4Header {
//    int markingField; // 32-bit field used for marking (UIi)
//}

message RIHTPacket {
    int mark;
    int UI;
}