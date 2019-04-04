SELECT C.Country, COUNT(O.ordid)
FROM Customers C, Orders O
WHERE O.ocust = C.custid AND O.odate BETWEEN '2016-01-01' AND '2016-12-31'
GROUP BY C.country
UNION ALL
SELECT C.country, COUNT(O.ordid)
FROM Customers C, Orders O
WHERE NOT EXISTS 
	(SELECT C.country, COUNT(O.ordid)
	FROM Customers C, Orders O
	WHERE O.ocust = C.custid AND O.odate BETWEEN '2016-01-01' AND '2016-12-31'
	GROUP BY C.country)
GROUP BY C.country;
