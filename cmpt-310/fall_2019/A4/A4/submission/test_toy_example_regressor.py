from toy_example_regressor import SimpleNet, get_data
import numpy as np

np.random.seed(0)


def test_regressor_accuracy():
    try:
        net = SimpleNet()
        net.build()
        net.build_loss()
        net.load_weights('simple_net_weights.pkl')
        x, y = get_data()
        _, loss = net.compute_activations(np.expand_dims(x, 0), np.expand_dims(y, 0))
        np.testing.assert_array_less(loss, [0.013])
        return True
    except Exception as e:
        print('Regressor failed:{}\n\n-------------------\n\n'.format(e))
        return False


if __name__ == '__main__':
    test_regressor_accuracy()
