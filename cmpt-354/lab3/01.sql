/*For each product type, calculate the number of orders consisting only of products of that type. Return
the product type and the number of orders.*/

SELECT P.ptype, COUNT(O.ordid)
FROM Products P, Orders O, Details D
WHERE NOT EXISTS (
	SELECT P1.ptype, O.ordid
	FROM Products P1, Products P2, Orders O, Details D
	WHERE O.ordid = D.ordid AND D.pcode = P2.pcode AND P1.ptype != P2.ptype
)
GROUP BY P.ptype;