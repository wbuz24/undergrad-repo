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
 
 
