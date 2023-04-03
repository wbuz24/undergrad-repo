# Processors

These notes are derived from the [TENNLab](https://bitbucket.org/neuromorphic-utk/framework/src/master/markdown/framework_processor.md) cpp-processors markdown file and was written to teach myself about how processors are implemented within the TENNLab framework, but will evolve to document the intricacies of the Izhikevich processor.

## Processor workflow

![processor_flowchart.png](processor_flowchart.png)

## Parameterization and customization

When creating an instance of a processor, you can set parameters by pasing a JSON string to the processor's constructor or 'make()' method

In many applications, the TENNLab framework will store a JSON used to create the processor in the "Associated_Data" of the network, under the key 'proc_params'. Then, when using the networl/processor combination in the application, you must:
 - Create an instance of the network from the network file.
 - Create an instance of the processor using the JSON stored in the netwrok file.
 - Load the network onto the processor
 - Go into the apply-spikes/run/read-output loop.
 
When a processor instance is created, it internally stores a Property_Pack. This defines the settable parameters used by neurons (nodes), synapses (edges) and networks. In a network, each node, each edge, and the entire network contains a vector of doubles called values, which is the setting of the parameters defined in the Property_Pack. These settings are stored in the network file.

So there's a real chicken-and-egg issue with networks and processors:

    Often you create an instance of a processor by reading its parameters from a network.
    You can't build a network until you have the processor define its Property_Pack.

To help disambuiguate this process, here's how it works:

    The training algorithm sets the initial parameters of the processor and creates an instance of the processor.
    It then creates networks, using the Property_Pack from the processor. That Property_Pack is stored in the network, along with the parameters that were used to create the processor.
    When the network is used, a new processor will be created using the parameters from the network.
 
 
 ## Izhikevich
 
The Izhikevich neuron model was implemented by Thomas Neuefeind into the TENNLab framework and has been successful in recreating the graphs from both the 2003 and 2004 papers by Eugene M. Izhikevich. 

The processor was implemented using the RISP processor as a model for implementing with the framework, therefore, the run() function is 1 indexed. 

## The events vector

The events vector is a 2D vector of neuron, charge pairs that tracks the events on which neuron and it's respective charge value.
 - the index is the timestep (in other words, the vector's first dimension stores the timestep while the second stores the actual pair)

## Network::process_events

This method is a large portion of the work done by the processor and much of that work is done on the neuron stored in the events vector. This is initially extracted in a variable es which is the instance of the events vector we are interested in, then the neuron is inserted into the variable n which receives all of the work from the function. Primarily:
 - updating the parameters based on the differential equations outlined in the 2003/2004 Izhikevich papers.
 - checks to see if the neuron fires
 - resizes the events vector
 - keeps track of neuron fire times and counts
 
