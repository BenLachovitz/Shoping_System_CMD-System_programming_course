#pragma once

#include "ShoppingItem.h"

typedef struct
{
	ShoppingItem**	itemArr;
	int				count;
}ShoppingCart;




void	initCart(ShoppingCart* pCart);
float	getTotalPrice(const ShoppingCart* pCart);
ShoppingItem*	getItemByBarocde(ShoppingCart* pCart, const char* barcode);
int		addItemToCart(ShoppingCart* pCart, const char* name, float price, int count);
float	printShoppingCart(const ShoppingCart* pCart);

void	freeShoppingCart(ShoppingCart* pCart);