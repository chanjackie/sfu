import time

import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

from layers import DenseLayer, SigmoidLayer, L2LossLayer
from neural_network import NeuralNet


np.random.seed(0)


class SimpleNet(NeuralNet):
    def __init__(self):
        super().__init__()

    def build(self):
        l1 = DenseLayer(1, 4)
        sig1 = SigmoidLayer()
        l2 = DenseLayer(4, 1)
        self._layers = [l1, sig1, l2]

    def build_loss(self):
        self.loss = L2LossLayer()


def get_data(n=200):
    x = np.linspace(-1, 1, n)[:, None]  # [batch, 1]
    y = x ** 2 + np.random.normal(0., 0.1, (n, 1))  # [batch, 1]
    return x, y


def train():
    # Create training data
    x, y = get_data()
    indices = np.random.permutation(range(200))
    x, y = x[indices], y[indices]
    # Create neural network
    net = SimpleNet()
    net.build()
    net.build_loss()

    # Set hyper parameters
    batch_size = 64
    learning_rate = 0.001

    # Train for 1000 epochs
    for epoch in range(1000):
        for i in range(len(x)//batch_size):
            # Select i-th mini-batch
            mini_batch_indices = list(range(i*batch_size, min((i+1)*batch_size, len(x))))
            # Run compute_activation pass of the neural network on the selected mini-batch
            _, loss = net.compute_activations(x[mini_batch_indices], y[mini_batch_indices])
            # Propagate the gradients
            net.compute_gradients()
            # Update the weights according to the gradient and learning_rate (one step of SGD)
            net.update_weights(learning_rate=learning_rate)
            if epoch % 50 == 0:
                print('[Epoch {0}]: loss: {1}'.format(epoch, loss))

    # Validation
    x, y = get_data()
    o, loss = net.compute_activations(np.expand_dims(x, 0), np.expand_dims(y, 0))
    o = o.reshape(200, 1)

    # Draw the plot and save as image
    plt.scatter(x, y, s=20)
    plt.plot(x, o, c="red", lw=3)
    print('Validation Loss', np.mean(loss))
    plt.savefig('data_and_function.png')

    # Save network weights:
    net.save_weights('simple_net_weights_{}.pkl'.format(time.strftime("%Y%m%d-%H%M%S")))


if __name__ == '__main__':
    train()
