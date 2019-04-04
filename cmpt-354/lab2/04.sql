SELECT T1.ptype, O.ocust, D.qty
		FROM
			(SELECT P.ptype, MAX(D.qty)
			FROM Details D, Products P
			WHERE D.pcode = P.pcode
			GROUP BY P.ptype) AS T1, Orders O, Details D
		WHERE D.qty = T1.max AND O.ordid = D.ordid)