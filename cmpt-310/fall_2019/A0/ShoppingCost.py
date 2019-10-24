"""
To run this script:
	python shoppingCost.py

If you run the above script, a correct calculateShoppingCost function should return:

The final cost for our shopping cart is 35.58
"""

import csv

def calculateShoppingCost(productPrices, shoppingCart):
	finalCost = 0
	"*** Add your code in here ***"
	for i in shoppingCart:
		finalCost += float(productPrices[i]) * int(shoppingCart[i])
	return finalCost


def createPricesDict(filename):
	productPrice = {}
	"*** Add your code in here ***"
	with open(filename, mode='r') as csv_file:
		csv_reader = csv.reader(csv_file)
		for row in csv_reader:
			productPrice[row[0]] = row[1]
	return productPrice


if __name__ == '__main__':
	prices = createPricesDict("Grocery.csv")
	myCart = {"Bacon": 2,
		      "Homogenized milk": 1,
		      "Eggs": 5}
	print("The final cost for our shopping cart is {}".format(calculateShoppingCost(prices, myCart)))
