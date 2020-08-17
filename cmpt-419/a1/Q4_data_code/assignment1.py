"""Basic code for assignment 1."""

import numpy as np
import math
import pandas as pd
from scipy import nanmean

def load_unicef_data():
    """Loads Unicef data from CSV file.

    Retrieves a matrix of all rows and columns from Unicef child mortality
    dataset.

    Args:
      none

    Returns:
      Country names, feature names, and matrix of values as a tuple (countries, features, values).

      countries: vector of N country names
      features: vector of F feature names
      values: matrix N-by-F
    """
    fname = 'SOWC_combined_simple.csv'

    # Uses pandas to help with string-NaN-numeric data.
    data = pd.read_csv(fname, na_values='_', encoding='latin1')
    # Strip countries title from feature names.
    features = data.axes[1][1:]
    # Separate country names from feature values.
    countries = data.values[:,0]
    values = data.values[:,1:]
    # Convert to numpy matrix for real.
    values = np.asmatrix(values,dtype='float64')

    # Modify NaN values (missing values).
    mean_vals = nanmean(values, axis=0)
    inds = np.where(np.isnan(values))
    values[inds] = np.take(mean_vals, inds[1])
    return (countries, features, values)


def normalize_data(x):
    """Normalize each column of x to have mean 0 and variance 1.
    Note that a better way to normalize the data is to whiten the data (decorrelate dimensions).  This can be done using PCA.

    Args:
      input matrix of data to be normalized

    Returns:
      normalized version of input matrix with each column with 0 mean and unit variance

    """
    mvec = x.mean(0)
    stdvec = x.std(axis=0)
    
    return (x - mvec)/stdvec
    


def linear_regression(x, t, basis, reg_lambda=0, degree=0, mu=0, s=1, bias=0):
    """Perform linear regression on a training set with specified regularizer lambda and basis

    Args:
      x is training inputs
      t is training targets
      reg_lambda is lambda to use for regularization tradeoff hyperparameter
      basis is string, name of basis to use
      degree is degree of polynomial to use (only for polynomial basis)
      mu,s are parameters of Gaussian basis

    Returns:
      w vector of learned coefficients
      train_err RMS error on training set
      """

    # Construct the design matrix.
    # Pass the required parameters to this function
    # train_errs = []

    phi = design_matrix(x, degree, basis, mu, s, bias)
    phi_pinv = np.linalg.pinv(phi)
    # print(phi_pinv.shape)
    # print(phi.shape)
    # Learning Coefficients
    if reg_lambda > 0:
        # regularized regression
        train_err = 0
        min_val_err = float('Inf')
        w = []
        for n in range(10):
            train_t = np.vstack([t[:n*10], t[n*10+10:]])
            train_phi = np.vstack([phi[:n*10], phi[n*10+10:]])
            train_phi_pinv = np.linalg.pinv(train_phi)
            train_w = train_phi_pinv * train_t
            val_err = 0
            for i in range(train_phi.shape[0]):
                pred = bias + train_phi[i]*train_w
                val_err += (train_t[i] - pred)**2
            val_err = np.sqrt(val_err/train_phi.shape[0])
            reg_val = 0
            for i in range(train_w.shape[0]):
                reg_val += (reg_lambda*train_w[i])**2
            val_err += reg_val
            train_err += val_err
            # if reg_lambda == 0.1:
            #     print(val_err)
            if val_err < min_val_err:
                min_val_err = val_err
                w = train_w
        train_err = train_err/10
        # print(train_err)

    else:
        # no regularization
        w = phi_pinv * t
        # Measure root mean squared error on training data.
        train_err = 0

        for i in range(phi.shape[0]):
            pred = bias + phi[i]*w
            train_err += (t[i] - pred)**2

        train_err = np.sqrt(train_err/phi.shape[0])
    # print(train_err)

    return (w, np.asscalar(train_err))



def design_matrix(x, degree=0, basis=None, mu=0, s=1, bias=0):
    """ Compute a design matrix Phi from given input datapoints and basis.

    Args:
        ?????

    Returns:
      phi design matrix
    """

    if basis == 'polynomial':
        phi = x
        if (bias > 0):
            phi = np.hstack([np.ones((x.shape[0], 1)), phi])
        # phi = x
        for i in range(1, degree):
            phi = np.hstack([phi, np.power(x, i+1)])
    elif basis == 'sigmoid':
        phi = np.zeros(x.shape)
        n = 0
        for i in range(x.shape[0]):
            phi[i] = 1/(1+math.exp((mu-x[i])/s))
        phi = np.hstack([np.ones((phi.shape[0], 1)), phi])
        # print(phi)
    else: 
        assert(False), 'Unknown basis %s' % basis

    return phi


def evaluate_regression(w, x, t, basis, degree=0, mu=0, s=1, bias=0):
    """Evaluate linear regression on a dataset.

    Args:
      ?????

    Returns:
      t_est values of regression on inputs
      err RMS error on training set if t is not None
      """
    phi = design_matrix(x, degree, basis, mu, s, bias)
    t_est = []
    err = 0
    # print(phi.shape)
    for i in range(phi.shape[0]):
        t_est.append(np.asscalar(bias + phi[i]*w))
        err += (t[i] - t_est[i])**2

    err = np.sqrt(err/phi.shape[0])
    print(err)
    # print(t_est)
    return (t_est, np.asscalar(err))
