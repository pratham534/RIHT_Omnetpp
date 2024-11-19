package RIHT;
// src/RIHTRouter.ned

simple RIHTRouter {
    parameters:
        int degree; // The number of upstream interfaces (D(Ri))
        int hashTableSize; // The size of the hash table
    gates:
        inout ethg[];
        
}
