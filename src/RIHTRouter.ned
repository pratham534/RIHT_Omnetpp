package RIHT;
// src/RIHTRouter.ned

simple RIHTRouter {
    parameters:
        int degree;
        int hashTableSize;
    gates:
        inout ethg[];
        
}
