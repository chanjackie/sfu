import numpy as np

from layers import BaseLayer
from neural_network import NeuralNet


class DummyLayer(BaseLayer):

    def __init__(self):
        super().__init__()
        self.w = np.asarray([[1]])
        self.t = np.asarray([[10]])
        self.loss = False
        self.lr = None

    def compute_activation(self, x, t=None):
        self._input_data = x
        self.t = t
        if self.t is not None:
            return self.t + x
        return x + 1

    def compute_gradient(self):
        if self.loss:
            self._input_error_gradient = self.t
        else:
            self._input_error_gradient = self._output_error_gradient - 1

    def update_weights(self, learning_rate):
        self.lr = learning_rate


class DummyNet(NeuralNet):

    def __init__(self):
        super().__init__()
        self.build_loss()
        self.build()

    def build(self):
        self._layers = [DummyLayer() for i in range(5)]

    def build_loss(self):
        self.loss = DummyLayer()
        self.loss.loss = True


def test_compute_activations():
    try:
        net = DummyNet()
        x, loss = net.compute_activations(np.asarray([[0]]), np.asarray([[7]]))
        np.testing.assert_equal(x, 5, '[Wrong network output]')
        np.testing.assert_equal(loss, 5+7, '[Wrong loss]')
        for i, layer in enumerate(net._layers):
            np.testing.assert_equal(layer.get_input_data(), i, '[Wrong layer input]')

        np.testing.assert_equal(net.loss.get_input_data(), 5, '[Wrong loss input]')
        np.testing.assert_equal(net.loss.t, 7, '[Wrong set target]')
        return True
    except Exception as e:
        print('NeuralNet.compute_activation failed:{}\n\n-------------------\n\n'.format(e))
        return False


def test_compute_gradients():
    try:
        net = DummyNet()
        net.compute_gradients()
        for i, layer in enumerate(net._layers):
            np.testing.assert_equal(layer.get_input_error_gradient(), 10 - (5-i), '[Wrong layer '
                                                                                  'gradient]')
        np.testing.assert_equal(net.loss.get_input_error_gradient(), 10, '[Wrong loss input]')
        return True
    except Exception as e:
        print('NeuralNet.compute_gradient failed:{}\n\n-------------------\n\n'.format(e))
        return False


def test_update_weights():
    try:
        net = DummyNet()
        net.update_weights(learning_rate=0.5)
        for i, layer in enumerate(net._layers):
            np.testing.assert_equal(layer.lr, 0.5, '[Wrong update]')
        return True
    except Exception as e:
        print('NeuralNet.update_weights failed:{}\n\n-------------------\n\n'.format(e))
        return False


if __name__ == '__main__':
    test_compute_activations()
    test_compute_gradients()
    test_update_weights()
