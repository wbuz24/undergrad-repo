# Processors

These notes are derived from the [TENNLab](https://bitbucket.org/neuromorphic-utk/framework/src/master/markdown/framework_processor.md) and is intended to document the intricacies of the Izhikevich processor.
 
A processor

## Izhikevich
 
The Izhikevich neuron model was implemented by Thomas Neuefeind into the TENNLab framework and has been successful in recreating the graphs from both the 2003 and 2004 papers by Eugene M. Izhikevich. 

The processor was implemented using the RISP processor as a model for implementation with the framework, therefore, the run() function is currently 1 indexed. 

Graphs are written in c++ and utilizes [jgraph](http://web.eecs.utk.edu/~jplank/plank/jgraph/jgraph.html)

# processor.cpp

The process.cpp file is the heart of Izhikevich and is used to implement all methods from processor.hpp

## The events vector

The events vector is a 2D vector of neuron charge pairs that tracks the events on which neuron and it's respective charge value.
 - the index is the timestep (in other words, the vector's first dimension stores the timestep while the second stores the actual pair)


## Network::process_events

This method is a large portion of the work done by the processor and much of that work is done on the neuron stored in the events vector. This is initially extracted in a variable es which is the instance of the events vector we are interested in, then the neuron is inserted into the variable n which receives all of the work from the function. Primarily:
 - updating the parameters based on the differential equations outlined in the 2003/2004 Izhikevich papers.
 - checks to see if the neuron fires
 - resizes the events vector
 - keeps track of neuron fire times and counts
 - collects charges i.e. incoming spikes (spike threshold is 30 mV)

## network_builder.cpp

The intention of network_builder.cpp is to recreate the 2003 simulation of a network of 1000x1000 randomly weighted coupled spiking neurons with 1,000,000 synapses.

The spike raster takes 800 excitatory neurons and 200 inhibitory neurons and plots their spikes over 1000 ms. 

The spike raster utilizes both uniform and normal distribution random number generators.

The 2003 paper sought to model the firing of simple neurons and therefore utilizes nomenclature more 

## matlab version

Due to the inherent ability in matlab to do simulataneous operations on entire matrices, the matlab code is noticeably shorter and much of the math is done utilizing the "." and ":" operators allowing element-wise operations.


## c++ version

Since c++ does not share the same ability as matlab for matrix math, it must be done by manual element-wise operations.

Stepping through the c++ mimics the processor.cpp in many ways, implementing the differential equations outlined in the 2003 paper and implementing it with the TENNLab framework. A brief explanation of the c++ flow is as follows:
- the first 800 neurons are excitatory and the following 200 are inhibitory

A pointer to the current neuron is initialized and iterates 1000 timesteps and for each timestep:
- the input charge is updated in a vector
- if the given neuron fires, the current neuron's charge is written to a text file

