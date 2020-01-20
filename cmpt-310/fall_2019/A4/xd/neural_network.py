import numpy as np
import pickle


class NeuralNet:
    def __init__(self):
        self._layers = []
        self.loss = None

    def build(self, *args, **kwargs):
        raise NotImplementedError

    def build_loss(self, *args, **kwargs):
        raise NotImplementedError

    def compute_activations(self, x, target):
        """
        Iterates over all the layers (self._layers) starting from the first layer and
        computes the activations of all layers by passing the output of one to the output 
        of the next one. 
        """

        # YOUR CODE STARTS HERE (1)
        nextAct = x

        for layer in self._layers:
            nextAct = layer.compute_activation(nextAct)

        output = nextAct #TODO output of the last layer
        #print(output)
        loss = self.loss.compute_activation(output, target) #TODO Compute the loss
        return (output, loss)

        # YOUR CODE ENDS HERE (1)

    def compute_gradients(self):
        """
        Computes the gradient of all weights with respect to the error. For each layer L, stores the gradient in L._input_error_gradient, 
        where L._error_input_gradient is the gradient of loss with respect to the input of layer L. Then passes that to the previous layer. 
        In other words, sets the previous layer's output gradient by the current layer's input gradient.

        Hint 1: First compute the gradient of loss, then use that to initialize backpropagation on the other layers.
        Hint 2: You can iterate through layers in reverse order using the for loop: for layer in reversed(self._layers)

        """
        

        # YOUR CODE STARTS HERE (2)
        self.loss.compute_gradient()
        prevLoss = self.loss.get_input_error_gradient()
        for layer in reversed(self._layers):
            #print(prevLoss)
            layer.set_output_error_gradient(prevLoss)
            layer.compute_gradient()
            prevLoss = layer.get_input_error_gradient()


        # YOUR CODE ENDS HERE (2)

        
       

    def update_weights(self, learning_rate):
        """
        Updates the weights given a specific update function (e.g. SGD).
        Iterates over all layers and update their weights.

        Hint: Every layer L has a L.update_weight() function.
        """
        
        # YOUR CODE STARTS HERE (3)
        for layer in self._layers:
            layer.update_weights(learning_rate)
        

        # YOUR CODE ENDS HERE (3)



    def save_weights(self, path):
        weights = []
        for layer in self._layers:
            weights.append(layer.get_weights())
        with open(path, "wb") as f:
            pickle.dump(weights, f)

    def load_weights(self, path):
        with open(path, "rb") as f:
            weights = pickle.load(f)
            for i, layer in enumerate(self._layers):
                layer.set_weights(weights[i])
