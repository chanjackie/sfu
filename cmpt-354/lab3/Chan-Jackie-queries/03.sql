-- Find customers who spent less than 50 in music in the period 
-- between January and June 2016 (inclusive). Return the customer ID 
-- and the corresponding amount spent. Customers who have not bought
-- any music in the given period must be returned with 0.00 spend 
-- (precisely in this form).

SELECT DISTINCT C.custid, SUM(P.price)
FROM Orders O, Details D, Products P, Customers C
WHERE O.ordid = D.ordid AND O.odate BETWEEN '2016-01-01' AND '2016-06-30'
AND D.pcode = P.pcode AND P.ptype = 'MUSIC' AND O.ocust = C.custid
GROUP BY C.custid
HAVING SUM(P.price) < 40.0;