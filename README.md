<div align = center> 
<h1> Neuro Flap </h1>
<p>  Neuro Flap is a project that applies a Feedforward Neural Network optimized with Genetic Alghoritms to the game </b><i> Flappy Bird</i>! </p>
</div>

<p align ="center"> 
<img width = "725" height = "600" src = "https://github.com/user-attachments/assets/74a5a591-e432-4f3f-8f92-d62f829b81b6"> 
</p>


<h1> Description </h1>
<p>
  <b> Neural Networks are models inspired by the human brain that are capable of machine learning and pattern recognition. </b> <br>
  
  Developed in C using Raylib, the project includes the implementation of a Feedforward Neural Network, the Genetic Algorithm training method, and an exploration of Activation Functions and Network Architectures. 
  The best solutions were subsequently analysed using different hidden layer sizes.
  
  The final result includes a WebAssembly website that allows users to play against the best-trained network. The project is also available at Hugging Face Spaces!
</p>



<h1> Feedforward Neural Network in C </h1>
<p>
<b>The Perceptron</b> is one of the fundamental models underpinning Neural Networks. In its simplest form, it consists of a single layer that connects the inputs to the output, using weights and biases.
The evolution of this model led to Neural Networks with multiple layers, typically organised into an <b>input layer</b>, <b>hidden layers</b> and an <b>output layer</b>. 

The introduction of Activation Functions was essential, enabling the modelling of non-linear relationships and significantly increasing the models capacity.

There are various optimisation methods for training Neural Networks. In this project, the Genetic Algorithm was used.

The <b> Genetic Algorithm </b> is based on the creation of populations composed of several individuals, where each individual represents a possible solution and possesses its own set of <i>genes</i>. 

At the end of each generation, the best individuals are selected based on their <i>fitness</i>.
These individuals are then used to generate a new population through processes such as reproduction (selecting genes from the best individuals) and mutation (introduces random variation, promoting diversity and preventing premature convergence).

In general, the Genetic Algorithm is inspired by the process of Human Natural Evolution. 

<b>In this project, up to 50 populations were used, with 250 individuals in each.</b>
</p>


<h1> Activation Functions </h1>
<p>
Activation functions play a key role in Neural Networks by introducing <b>non-linearity</b> into the learning process. <br>
Without these functions, the models would be reduced to linear combinations, regardless of the number of layers, significantly limiting their ability to represent complex patterns.

In this project, the following activation functions were analysed:

<ul>
  <li> Sigmoid </li>
  <li> ReLU </li>
  <li> Leaky ReLU </li>
  <li> Tanh </li>
</ul>
</p>


<h1> Number of Neurons in the Hidden Layer </h1>
<p>
Another aspect analysed in this project was the Number of Neurons in the Hidden Layer. <br>
This question proved particularly interesting: <b>is a model with more neurons in the Hidden Layer necessarily better?</b>

To investigate this hypothesis, the three architectures with the best performance were selected following a study of the activation functions. <br>
Subsequently, the number of neurons in the hidden layer of these architectures was doubled in order to assess the impact of this change on the model’s performance.
</p>


<h1> Winning Model </h1>
<p>  
Architecture:
<ul>
  <li> Input Layer -> 4 Normalized Inputs </li>
  <li> Hidden Layer -> 5 Neurons with Tanh Activation Function </li>
  <li> Output Layer -> 1 Neuron with Sigmoid Activation Function </li>
</ul>
 
<h3> <a href = "https://eliezer-carvalho.github.io/Neuro-Flap/" target = "_blank"> Do you think you can beat it ? :) </a> </h3>
</p>


<h1> Languages, Libraries and Environments </h1>

<p>
<a href = "https://en.wikipedia.org/wiki/C_(programming_language)" target = "_blank"> C </a> <br>
<a href = "https://github.com/raysan5/raylib" target = "_blank"> Raylib </a> <br> 
<a href = "https://www.linuxmint.com/" target = "_blank"> Linux Mint </a> <br>
<a href = "https://webassembly.org/" target = "_blank"> Web Assembly </a>


</p>









