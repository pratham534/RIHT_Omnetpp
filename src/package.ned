package RIHT;

@license(LGPL);

import RIHT.RIHTRouter;
import RIHT.Sender;
import RIHT.Receiver;
import inet.examples.inet.ipv4hook.MyRouter;
import ned.IdealChannel;


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
            @display("p=341,256");
            gates:
                ethg[3];
        }
        router2: RIHTRouter {
            @display("p=228,183");
            gates:
                ethg[2];
        }
        router3: RIHTRouter {
            @display("p=228,307");
            gates:
                ethg[2];
        }
        victim: Receiver {
            @display("p=416,256");
            gates:
                ethg[1];  // Specify gate index for victim
        }
        attacker: Sender {
            @display("p=133,307");
            gates:
                ethg[1];  // Specify gate index for attacker
        }
        host: Sender {
            @display("p=133,183");
            gates:
                ethg[1];  // Specify gate index for host
        }
    connections:
        router2.ethg[1] <--> Link <--> router1.ethg[0];
        router1.ethg[1] <--> Link <--> victim.ethg[0];
        router3.ethg[1] <--> Link <--> router1.ethg[2];
        host.ethg[0] <--> Link <--> router2.ethg[0];
        attacker.ethg[0] <--> Link <--> router3.ethg[0];
}
