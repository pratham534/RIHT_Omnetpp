package RIHT;

simple Sender {
    parameters:
        string ipv4Address; // IP address parameter
    gates:
        inout ethg[1];
}
