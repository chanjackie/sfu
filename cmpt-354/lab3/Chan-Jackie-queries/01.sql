/*For each product type, calculate the number of orders consisting only of products of that type. Return
the product type and the number of orders.*/

SELECT P1.ptype, COUNT(DISTINCT O1.ordid)
FROM Products P1, Orders O1, Details D1
WHERE D1.ordid = O1.ordid AND D1.pcode = P1.pcode 
AND NOT EXISTS (
	SELECT D2.ordid
	FROM Details D2, Products P2
	WHERE D2.ordid = O1.ordid AND D2.pcode = P2.pcode AND P2.ptype != P1.ptype
)
GROUP BY P1.ptype;
