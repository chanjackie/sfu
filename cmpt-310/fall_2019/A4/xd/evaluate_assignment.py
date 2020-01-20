from test_layers import test_dense_compute_activation, test_dense_compute_gradient, test_dense_update_weights
from test_neural_network import test_update_weights, test_compute_activations, test_compute_gradients
from test_toy_example_regressor import test_regressor_accuracy
from test_prime_classifier import test_prime_classifier_accuracy


tests = {
    test_prime_classifier_accuracy: 20,
    test_regressor_accuracy: 10,
    test_dense_compute_activation: 15,
    test_dense_compute_gradient: 20,
    test_dense_update_weights: 10,
    test_compute_activations: 10,
    test_compute_gradients: 10,
    test_update_weights: 5
}

if __name__ == '__main__':
    total = 0
    count = 0
    for test, point in tests.items():
        count += 1
        print('[Test {}]'.format(count))
        if test():
            total += point
    print('Total Point: {}'.format(total))