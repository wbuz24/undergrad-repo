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
 
 
 ## Processor Tool
 ```
 pwd
 ```
/home/shartreuce/Documents/repos/undergrad/framework/cpp-apps
 ```
 make app=processor_tool proc=izhikevich
 ```
  - 
 ```
 echo "?" | bin/processor_tool_izhikevich
 ```
This is a processor tool program. The commands listed below are case-insensitive,
For commands that take a json either put a filename on the same line,
or the json can be multiple lines, starting on the next line.

Action commands --
MAKE/M proc_name proc_param_json    - Make a new processor with no network
LOAD/L network_json                 - Load a network on the processor
ML network_json                     - Make a new processor from the network & load the network.
AS node_id spike_time spike_val ... - Apply spikes to the network (note: node_id, not input_id)
RUN simulation_time                 - Run the network for "simulation_time" cycles
CLEAR-A/CA                          - Clear the network's internal state 
CLEAR/C                             - Remove the network from processor
VIZ T|F [extra_viz_argument] [...]  - Open network viz. T|F is to show viz's control panel

Output tracking info commands --
OLF [node_id] [...]                 - Output the last fire time for the given output or all outputs
OC [node_id] [...]                  - Output the spike count for the given output or all outputs
OT/OV [node_id] [...]               - Output the spike times for the given output or all outputs
TRACK_O [node_id] [...]             - Track output events for given outputs (empty=all)
UNTRACK_O [node_id] [...]           - Untrack output events for given output (empty=all)

Neuron tracking info commands --
NLF show_nonfiring(T/F)             - Last fire times for neurons.
NC show_nonfiring(T/F)              - Fire counts for neurons.
NT/NV show_nonfiring(T/F)           - All firing times for tracked neurons.
GSR show_hidden(T/F)                - Print spike raster info for tracked neurons.
NCH                                 - Print the charges (action potentials) of the neurons.
NLFJ                                - Print the neuron last fire json
NCJ                                 - Print the neuron count json
NVJ type(V/S)                       - Print the neuron vector json
NCHJ                                - Print the neuron charge json
TRACK_N [node_id] [...]             - Track neuron events for specified neurons (empty=all)
UNTRACK_N [node_id] [...]           - Untrack neuron events for specified neurons (empty=all)

Other info commands --
PARAMS [file]                       - Print the JSON that can recreate the processor
NP/PPACK                            - Print the PropertyPack that networks use with the processor.
NAME                                - Print the processor's name
EMPTYNET [file]                     - Create an empty network for this processor
PP                                  - Print processor's properties - (not a universal feature).
INFO                                - Print the network's node ids and output tracking info
PS                                  - Print the spikes we have applied
?                                   - Print commands
Q                                   - Quit
