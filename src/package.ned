package RIHT;

@license(LGPL);

import RIHT.RIHTRouter;
import RIHT.Sender;
import RIHT.Receiver;
import ned.IdealChannel;
import RIHT.MyRoutingProtocol;


network RIHTNetwork
{
    @display("bgb=601,440");
    types:
        channel Link extends ned.DatarateChannel
        {
            delay = 10s;
            datarate = 100Mbps;
        }
    submodules:
        router1: RIHTRouter {
            degree = 3;
            hashTableSize = 100;
            @display("p=421,256");
            gates:
                ethg[3];
        }
        router2: RIHTRouter {
            degree = 2;
            hashTableSize = 100;
            @display("p=308,183");
            gates:
                ethg[2];
        }
        router3: RIHTRouter {
            degree = 2;
            hashTableSize = 100;
            @display("p=177,183");
            gates:
                ethg[2];
        }
        router4: RIHTRouter {
            degree = 2;
            hashTableSize = 100;
            @display("p=308,307");
            gates:
                ethg[2];
        }
        router5: RIHTRouter {
            degree = 2;
            hashTableSize = 100;
            @display("p=177,307");
            gates:
                ethg[2];
        }
        victim: Receiver {
            @display("p=496,256");
            gates:
                ethg[1];  // Specify gate index for victim
        }
        attacker: Sender {
            @display("p=75,307");
            gates:
                ethg[1];  // Specify gate index for attacker
        }
        host: Sender {
            @display("p=75,183");
            gates:
                ethg[1];  // Specify gate index for host
        }
        routing: MyRoutingProtocol;
//    connections:
//        host.ethg[0] <--> Link <--> router3.ethg[0];
//        router3.ethg[1] <--> Link <--> router2.ethg[0];
//        router2.ethg[1] <--> Link <--> router1.ethg[0];
//        router1.ethg[1] <--> Link <--> victim.ethg[0];
//        attacker.ethg[0] <--> Link <--> router5.ethg[0];
//        router5.ethg[1] <--> Link <--> router4.ethg[0];
//        router4.ethg[1] <--> Link <--> router1.ethg[2];
    connections allowunconnected:
        host.ethg[0] <--> Link <--> router3.ethg[0];
        router3.ethg[1] <--> routing.lowerLayerIn[0];
    	routing.lowerLayerOut[0] <--> router2.ethg[1];
    	router2.ethg[1] <--> Link <--> router1.ethg[0];
        router1.ethg[1] <--> Link <--> victim.ethg[0];
        attacker.ethg[0] <--> Link <--> router5.ethg[0];
        router5.ethg[1] <--> Link <--> router4.ethg[0];
        router4.ethg[1] <--> Link <--> router1.ethg[2];
}
