import numpy as np
import pickle


def accuracy(predictions, labels):
    """Compute the accuracy, given predictions and labels"""
    assert predictions.shape == labels.shape
    p, l = predictions.astype(np.int32), labels.astype(np.int32)
    return np.where(p == l, 1., 0.).mean() * 100


def load_prime_mnist():
    """
    Loads and processes MNIST dataset. First pixel values are normalized and then labels are
    created prime numbers have label = 1 and others have label = 0.
    The validation set is a held out set that could be used for validating the performance of the
    model.
    """
    with open("assignment4-mnist.pkl", 'rb') as f:
        mnist = pickle.load(f)

    (train_data, train_label) = (mnist["train"], mnist["train_labels"])
    (val, val_label) = (mnist["val"], mnist["val_labels"])

    # Normalize the pixel values to [0. 1.] interval
    train_data = train_data.reshape((-1, 28*28)) / 255.
    val = val.reshape((-1, 28*28)) / 255.

    # Set label of prime numbers to 1 and rest to 0
    label = np.isin(train_label, [2, 3, 5, 7])
    val_label = np.isin(val_label, [2, 3, 5, 7])

    return (train_data, label), (val, val_label)


def show(image):
    """
    Render a given numpy.uint8 2D array of pixel data.
    """
    from matplotlib import pyplot
    import matplotlib as mpl
    fig = pyplot.figure()
    ax = fig.add_subplot(1, 1, 1)
    imgplot = ax.imshow(image, cmap=mpl.cm.Greys)
    imgplot.set_interpolation('nearest')
    ax.xaxis.set_ticks_position('top')
    ax.yaxis.set_ticks_position('left')
    pyplot.show()

