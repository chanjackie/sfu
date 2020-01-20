import numpy as np

from layers import DenseLayer


def get_dense_layer():
    layer = DenseLayer(2, 1)
    layer.w = np.asarray([[1.], [2.]])
    layer.b = np.asarray([2.])
    layer._input_data = np.asarray([[-1, 2]])
    return layer


def test_dense_compute_activation():
    try:
        layer = get_dense_layer()
        x = layer.compute_activation(layer.get_input_data())
        answer = np.asarray([[5.]])
        np.testing.assert_equal(x, answer, '[Wrong activation]')
        return True
    except Exception as e:
        print('DenseLayer.compute_activation failed:{}\n\n-------------------\n\n'.format(e))
        return False


def test_dense_compute_gradient():
    try:
        layer = get_dense_layer()
        layer.set_output_error_gradient(np.asarray([[-5]]))
        layer.compute_gradient()
        np.testing.assert_equal(layer.dw, np.asarray([[5], [-10]]), '[Wrong dw]')
        np.testing.assert_equal(layer.db, np.asarray([[-5]]), '[Wrong db]')
        np.testing.assert_equal(layer.get_input_error_gradient(), np.asarray([[-5, -10]]),
                                '[Wrong input_error]')
        return True
    except Exception as e:
        print('DenseLayer.compute_gradient failed:{}\n\n-------------------\n\n'.format(e))
        return False


def test_dense_update_weights():
    try:
        layer = get_dense_layer()
        layer.dw = layer.w.copy()
        layer.db = layer.b.copy()
        layer.update_weights(learning_rate=2)
        np.testing.assert_equal(layer.w, -layer.dw, '[Wrong w]')
        np.testing.assert_equal(layer.b, -layer.db, '[Wrong b]')
        return True
    except Exception as e:
        print('DenseLayer.update_weights failed:{}\n\n-------------------\n\n'.format(e))
        return False


if __name__ == '__main__':
    test_dense_compute_activation()
    test_dense_compute_gradient()
    test_dense_update_weights()

