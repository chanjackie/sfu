SELECT P.ptype, ROUND(AVG(D.qty), 2)
FROM Products P, Details D
WHERE D.pcode = P.pcode AND D.qty > 0
GROUP BY P.ptype;
