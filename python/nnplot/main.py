import numpy as np

import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

def plot(xs, ys, zs):
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    ax.plot_wireframe(xs, ys, zs)
    plt.show()

def linear(x):
    return x

def relu(x):
    if x > 0:
        return x
    else:
        return 0

class Layer(object):
    def __init__(self, shape, linear_activation=False):
        self._weights = np.random.rand(shape[0], shape[1]) * 2 - 1
        self._activation_function = np.vectorize(linear if linear_activation else relu)

    def run(self, x):
        weighted_sum = np.dot(self._weights, x)
        return self._activation_function(weighted_sum)

def run_network(x, layers):
    for layer in layers:
        x = layer.run(x)
    return x

def main():
    # Input = (2,)
    x = np.random.rand(2)
    print(x)
    print(f"Input shape: {x.shape}")

    # Output of first layer = 64
    layer_1 = Layer((64, 2))
    # Output of second layer = 64
    layer_2 = Layer((64, 64))
    # Output of third layer = 1
    layer_3 = Layer((1, 64), linear_activation=True)

    layers = [layer_1, layer_2, layer_3]
    run_network_np = np.vectorize(run_network, excluded=[1])

    x = y = np.linspace(1, 1.1, 50)
    X, Y = np.meshgrid(x, y)
    zs = np.array([run_network(np.array([x, y]), layers) for x, y in zip(np.ravel(X), np.ravel(Y))])
    Z = zs.reshape(X.shape)
    plot(X, Y, Z)

if __name__ == "__main__":
    # Make random numbers predictable
    # np.random.seed(0)
    main()
    # xs = np.linspace(-5, 5, 100)
    # ys = np.linspace(-5, 5, 100)
    # XS, YS = np.meshgrid(xs, ys)
    # zs = np.sqrt(XS**2, YS**2)

    # plot(XS, YS, zs)