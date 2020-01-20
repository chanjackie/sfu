from prime_classifier import PrimeNet
from utils import accuracy, load_prime_mnist
import numpy as np

np.random.seed(0)


def test_prime_classifier_accuracy():
    try:
        net = PrimeNet()
        net.build()
        net.build_loss()
        net.load_weights('prime_net_weights.pkl')
        _, (x, y) = load_prime_mnist()
        y= np.expand_dims(y, axis=1)
        predictions, loss = net.compute_activations(x, y)
        predictions = np.round(predictions)
        acc = accuracy(predictions > 0.5, y)
        np.testing.assert_array_less(97.0, acc, '[Low prime detection accuracy]')
        return True
    except Exception as e:
        print('Prime detector failed:{}\n\n-------------------\n\n'.format(e))
        return False


if __name__ == '__main__':
    test_prime_classifier_accuracy()
