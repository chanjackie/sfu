-- Find “poor readers”: customers who have not purchased any books in 2016. Return the customer ID.

SELECT C.custid
FROM Customers C
WHERE NOT EXISTS (
	SELECT O.ordid
	FROM Details D, Orders O
	WHERE O.ordid = D.ordid AND O.ocust = C.custid
	AND O.odate BETWEEN '2016-01-01' AND '2016-09-30'
	AND EXISTS (
		SELECT D.ordid
		FROM Products P
		WHERE D.pcode = P.pcode AND P.ptype = 'BOOK'
	)
);