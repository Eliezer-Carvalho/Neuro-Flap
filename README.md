<div align = center> 
<h1> Neuro Flap </h1>
<h3>  Neuro Flap is a project that applies a Feedforward Neural Network optimized with Genetic Alghoritms to the game </b><i> Flappy Bird</i>! </h3>
<h3> <a href = "https://eliezer-carvalho.github.io/Neuro-Flap/" target = "_blank"> Do you think you can beat it ? :) </a> </h3>
</div>

<p align ="center">  <img width = "725" height = "600" src = "https://github.com/user-attachments/assets/74a5a591-e432-4f3f-8f92-d62f829b81b6">  </p>



<h1> Feedforward Neural Network in C </h1>
<p>
Although the contemporary Artificial Intelligence ecosystem is predominantly made up of high-level libraries such as Python, PyTorch and TensorFlow, the Neural Network was implemented in C, with the aim of maximising performance, portability and a comprehensive understanding of the system. <br>
The model in question is currently configured using a classic three-layer architecture, designed to strike a balance between computational complexity and learning capacity:
  <ul>
    <li> <b> Input Layer: </b> 4 Neurons </li>
    <li> <b> Hidden Layer: </b> 5 Neurons </li>
    <li> <b> Output Layer: </b> 1 Neuron</li>
  </ul>
The core of the Neural Network logic, is available for reference in the directory <b> /NeuroFlap</b>.
</p>



<h1> Neuroevolution - Genetic Algorithms in C </h1>
<p>
The scarcity of documentation and the lack of practical implementations of Genetic Algorithms applied to Neural Networks using the C programming language were among the key motivations behind this project. In this project, GA is used as a weight optimisation, allowing the network to evolve. <br> 
The implementation is carried out in accordance with the fundamental pillars of Neuroevolution:
  <ul>
    <li> <b> Populations and Generations: </b> Simultaneous management of multiple individuals (each individual represents a Neural Network) </li>
    <li> <b> Fitness Function: </b> An assessment of each individual’s performance to determine their survival </li>
    <li> <b> Selection: </b> Identifying the best individuals to pass on genetic material to the next generation </li>
    <li> <b> Crossover: </b> The combination of the genetic material of two parents to produce a individual with superior potential </li>
    <li> <b> Mutation: </b> Introducing random variations in weights to avoid local minimum values and promote genetic diversity </li>
  </ul>
The core of the Genetic Algorithm logic, is also available for reference in the directory <b> /NeuroFlap</b>.
</p>



<h1> Representation of Inputs </h1>
<p>
Defining the inputs — the variables that provide information to the model — is one of the most critical aspects of developing a Neural Network. In the case of NeuroFlap, the agent must be able to navigate a stochastic and dynamic environment. <br>
To enable the agent to make decisions in real time, the network processes four key variables:
  <ul>
    <li> <b> Flappy's Height: </b> The agent's current vertical position </li>
    <li> <b> Vertical Speed: </b> The agent’s speed is closely linked to decision-making </li>
    <li> <b> Position of the Gap Center: </b> The vertical ‘target’ between the pipes through which the agent must pass </li>
    <li> <b> Horizontal Distance: </b> The distance to the next obstacle, to help the agent to time the jump </li>
  </ul>
Max-Scale Normalization is applied in order to standardise the inputs.
</p>



<h1> Activation Functions </h1>
<p>  
Activation Functions introduce the non-linearity required for the model to learn complex patterns and make rapid decisions. <br>
As part of the NeuroFlap project, the four architectures most frequently cited in the literature were implemented, with a view to enabling tests to be carried out with different convergence behaviours:
  <ul>
    <li> <b> Sigmoid Function </b> </li>
    <li> <b> ReLU </b> </li>
    <li> <b> Leaky ReLU </b> </li>
    <li> <b> Tanh </b> </li>
  </ul>
</p>



<h1> Performance Analysis of Activation Functions and Hidden Layer Topology in Neuroevolutionary Networks </h1>
<p>
The project in question is not limited to mere implementation, but rather represents an in-depth study of the efficiency of hyperparameters in Neuro-Evolutionary environments. <br> 
Two detailed experimental studies were conducted with a view to optimising the NeuroFlap architecture.

<h3> Activation Function Synergy </h3>
The first objective was to identify which combinations of activation functions (Hidden Layer → Output Layer) produce the best results in a model with <b>31 parameters</b>. <br>
The combinations tested were: <br> <br> 
  <ul>
    <li> <b> ReLU → Sigmoid </b> </li>
    <li> <b> ReLU → Tanh </b> </li>
    <li> <b> Leaky ReLU → Sigmoid </b> </li>
    <li> <b> Leaky ReLU → Tanh </b> </li>
    <li> <b> Sigmoid → Tanh </b> </li>
    <li> <b> Tanh → Sigmoid </b> </li>
  </ul>
<b> The top three combinations have progressed to next test. </b>

<h3> Hidden Layer Scaling </h3>
In order to answer the question: <b> <i> “Are Networks with more Neurons always better ?"</i></b>, the hidden layer of the winning combinations was doubled, <b> increasing the number of parameters from 31 to 61</b>. <br>
The finalist architectural designs were: <br> <br>
  <ul>
    <li> <b> ReLU → Sigmoid </b> </li>
    <li> <b> Leaky ReLU → Tanh </b> </li>
    <li> <b> Tanh → Sigmoid </b> </li>
  </ul>
</p>
<hr> 
<b>[!NOTE]</b>  <br>
A full technical report (PDF) detailing the full analysis and discussion of the results is available in the repository (currently available in Portuguese only). <br>
The metrics assessed were <b> Average Fitness</b>, <b>Execution Time</b> and <b>Number of Winning Individuals</b>. <br>
To ensure the consistency of the results, each combination was run five times independently. In each iteration, the model was trained for up to 50 generations, with a population of 250 individuals per generation. <br>
The diagrams can be found in the /Architectures and /Architectures x10 folders.


<h1> WASM and Hugging Face </h1>
<p>
Following the completion of the experimental tests and a thorough analysis of the data, <b> one model clearly stood out for its consistency, speed of convergence and effectiveness in the Flappy Bird environment</b>: <br>
<table>
  <tr>
    <th> Architecture </th>
    <th> Weight Optimisation </th>
    <th> Method for Normalising Inputs </th>
    <th> Hidden Layer Activation Function </th>
    <th> Output Layer Activation Function </th>
    <th> Number of Parameters </th>
  </tr>
  <tr>
    <th> Feedforward Neural Network \ MultiLayer Perceptron </th>
    <th> Neuroevolution – Genetic Algorithm </th>
    <th> Max Scaling Normalization </th>
    <th> Tanh </th>
    <th> Sigmoid </th>
    <th> 31 Parameters </th>    
  </tr>
</table>

The portability of the C code has enabled compilation to WebAssembly, allowing the Neural Network to run directly in the browser via JavaScript with native performance. <br>
The project is also available on the Hugging Face Spaces platform, where the winning model can be tested in an interactive environment accessible to all users.
</p>

<h1> Languages, Libraries and Environments </h1>
<p>
<a href = "https://en.wikipedia.org/wiki/C_(programming_language)" target = "_blank"> C </a> <br>
<a href = "https://github.com/raysan5/raylib" target = "_blank"> Raylib </a> <br> 
<a href = "https://www.linuxmint.com/" target = "_blank"> Linux Mint </a> <br>
<a href = "https://webassembly.org/" target = "_blank"> Web Assembly </a> <br>
<a href = "https://emscripten.org/" target = "_blank"> Emscripten </a>


</p>









