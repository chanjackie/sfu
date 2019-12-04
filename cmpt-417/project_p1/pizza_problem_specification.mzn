% Pizza Problem

int: n; % num pizzas
int: m; % num coupons
int: k; % cost bound
set of int: pizzas = 1..n;
set of int: coupons = 1..m;

array[pizzas] of var int: price;
array[coupons] of var int: buy;
array[coupons] of var int: free;

var set of pizzas: paid; % set of pizzas we pay for
var set of coupons: used; % set of coupons we use

array[coupons, pizzas] of var bool: justifies; % true where pizza is purchased to justify using coupon
array[coupons, pizzas] of var bool: usedFor; % true where pizza is free by using coupon

% Constraints from Pizza Problem notes
constraint forall(p in pizzas) ((p in paid) <-> not exists(c in coupons) (usedFor[c, p]));
constraint forall(c in coupons) ((c in used) <-> exists(p in pizzas) (usedFor[c, p]));
constraint forall(c in coupons) ((c in used) <-> sum(p in pizzas)(bool2int(justifies[c,p])) >= buy[c]);
constraint forall(c in coupons) (sum(p in pizzas)(bool2int(usedFor[c,p])) <= free[c]);
constraint forall(c in coupons) (forall(p1, p2 in pizzas where p1 != p2) ((usedFor[c,p1] /\ justifies[c,p2]) -> (price[p1] <= price[p2])));
constraint forall(p in pizzas) (forall(c in coupons) (justifies[c,p] -> (p in paid)));
var int: cost = sum(p in pizzas) (bool2int(p in paid) * price[p]);
constraint cost <= k;
constraint forall(c in coupons) (forall(p in pizzas) (justifies[c,p] -> ((c in 1..m) /\ (p in 1..n))));
constraint forall(c in coupons) (forall(p in pizzas) (usedFor[c,p] -> ((c in 1..m) /\ (p in 1..n))));

% Don't reuse coupons
constraint forall(c1, c2 in coupons) (forall(p in pizzas) ((justifies[c1,p] /\ justifies[c2,p]) -> c1 = c2));

solve minimize cost;

output ["cost(" ++ show(cost) ++ ")"];
