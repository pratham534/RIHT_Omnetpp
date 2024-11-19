package RIHT;

simple Receiver {
    parameters:
        string ipv4Address;
        int attackThreshold;
    gates:
        inout ethg[1];
}
