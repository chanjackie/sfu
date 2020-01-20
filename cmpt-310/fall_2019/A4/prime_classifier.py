import time

import numpy as np
import matplotlib
matplotlib.use('Agg')

from layers import DenseLayer, SigmoidLayer, L2LossLayer
from neural_network import NeuralNet
import utils


np.random.seed(0)



class PrimeNet(NeuralNet):
    """A simple neural network for classifying prime numbers in MNIST"""
    def __init__(self):
        super().__init__()
        # First layer: a fully connected layer with shape = 784 x 20
        self.l1 = DenseLayer(28*28, 20, w_std=0.01)
        # Activation of the first layer: Sigmoid
        self.sig1 = SigmoidLayer()

        # Second layer: a fully connected layer with shape = 20 x 1
        self.l2 = DenseLayer(20, 1, w_std=0.01)
        # Activation of the second layer: Sigmoid
        self.sig2 = SigmoidLayer()

    def build(self):
        self._layers = [self.l1, self.sig1, self.l2, self.sig2]

    def build_loss(self):
        self.loss = L2LossLayer()


def train():
    # Create training data
    (train_data, train_label), (val, val_label) = utils.load_prime_mnist()
    val_label = np.expand_dims(val_label, axis=1)

    # Create neural network
    net = PrimeNet()
    net.build()
    net.build_loss()

    # Set hyper parameters
    batch_size = 64
    learning_rate = 0.003

    # Train for 50 epochs
    for epoch in range(50):
        for i in range(len(train_data)//batch_size):
            # Select i-th mini-batch
            indices = list(range(i*batch_size, min((i+1)*batch_size, len(train_data))))

            # Run compute_activation pass of the neural network on the selected mini-batch
            predictions, loss = net.compute_activations(train_data[indices], train_label[indices])
            # Propagate the gradients
            net.compute_gradients()
            # Update the weights according to the gradient and learning_rate (one step of SGD)
            net.update_weights(learning_rate=learning_rate)

        # Validating the performance of model
        predictions, loss = net.compute_activations(val, val_label)
        predictions = np.round(predictions)
        acc = utils.accuracy(predictions > 0.5, val_label)
        print('[Epoch {0}]:\tvalidation loss: {1:0.8f},\t validation accuracy: {2:.2f}%'.format(
            epoch, np.mean(loss), acc))

    # Save network weights:
    net.save_weights('prime_net_weights_{}.pkl'.format(time.strftime("%Y%m%d-%H%M%S")))


if __name__ == '__main__':
    train()
